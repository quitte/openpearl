#include <time.h>
#include <sys/time.h>
#include <sys/errno.h>
#include "chip.h"
#include "systeminit.h"
#include <stdio.h>

extern void systeminit_ClockRTC();

static int rtc_clock_gettime_cb(clockid_t clock_id, struct timespec *tp);
int (*clock_gettime_cb)(clockid_t clock_id, struct timespec *tp) = &rtc_clock_gettime_cb;

static void rtc_to_structtm(RTC_TIME_T * rtc_tm, struct tm * tm){
	tm->tm_sec=rtc_tm->time[RTC_TIMETYPE_SECOND];
	tm->tm_min=rtc_tm->time[RTC_TIMETYPE_MINUTE];
	tm->tm_hour=rtc_tm->time[RTC_TIMETYPE_HOUR];
	tm->tm_mday=rtc_tm->time[RTC_TIMETYPE_DAYOFMONTH];
	tm->tm_mon=rtc_tm->time[RTC_TIMETYPE_MONTH];
	tm->tm_year=rtc_tm->time[RTC_TIMETYPE_YEAR]-1900;
	tm->tm_wday=rtc_tm->time[RTC_TIMETYPE_DAYOFWEEK];
	tm->tm_yday=rtc_tm->time[RTC_TIMETYPE_DAYOFYEAR];
}
static void structtm_to_rtc(struct tm * tm, RTC_TIME_T * rtc_tm){
	rtc_tm->time[RTC_TIMETYPE_SECOND]=tm->tm_sec;
	rtc_tm->time[RTC_TIMETYPE_MINUTE]=tm->tm_min;
	rtc_tm->time[RTC_TIMETYPE_HOUR]=tm->tm_hour;
	rtc_tm->time[RTC_TIMETYPE_DAYOFMONTH]=tm->tm_mday;
	rtc_tm->time[RTC_TIMETYPE_MONTH]=tm->tm_mon;
	rtc_tm->time[RTC_TIMETYPE_YEAR]=tm->tm_year+1900;
	rtc_tm->time[RTC_TIMETYPE_DAYOFWEEK]=tm->tm_wday;
	rtc_tm->time[RTC_TIMETYPE_DAYOFYEAR]=tm->tm_yday;
}
static int check_rtc(RTC_TIME_T * rtctime, unsigned int fallbackstamp){
	struct tm tm={0};
	struct tm tmgood={0};
	time_t timestamp=0;
	rtc_to_structtm(rtctime,&tm);
	timestamp = mktime(&tm);
	gmtime_r(&timestamp,&tmgood);
	if(!(tm.tm_mday==tmgood.tm_mday))
			return 1;
	if(!(tm.tm_wday==tmgood.tm_wday))
		return 1;
	if(!(tm.tm_yday==tmgood.tm_yday))
			return 1;
	if(timestamp<fallbackstamp){
		return 1;
	}
	return 0;
}

static void rtc_setunixtime(time_t time){
	RTC_TIME_T rtc_time;
	struct tm tm;
	gmtime_r(&time, &tm);
	structtm_to_rtc(&tm,&rtc_time);
	Chip_RTC_SetFullTime(LPC_RTC,&rtc_time);
}

void systeminit_rtc_settime(unsigned int fallbackstamp){
	RTC_TIME_T time;
	Chip_RTC_GetFullTime(LPC_RTC, &time);
	if(check_rtc(&time, fallbackstamp))
		rtc_setunixtime(fallbackstamp);
}

static time_t rtc_getunixtime(){
	RTC_TIME_T time;
	struct tm tm;
	Chip_RTC_GetFullTime(LPC_RTC, &time);
	rtc_to_structtm(&time,&tm);
	return mktime(&tm);
}

struct tm *localtime(const time_t *_time){
	//always assume localtime was UTC
	return gmtime(_time);
}

static int rtc_clock_gettime_cb(clockid_t clock_id, struct timespec *tp){
	tp->tv_nsec=0;
	tp->tv_sec=rtc_getunixtime();
	return 0;
}

extern int clock_gettime(clockid_t clock_id, struct timespec *tp){
	return (*clock_gettime_cb)(clock_id, tp);
}

int gettimeofday(struct timeval *__p, void *__tz){
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	if(__tz)
		return ENOSYS;
	__p->tv_usec=ts.tv_nsec/1000;
	__p->tv_sec=ts.tv_sec;
	return 0;
}
