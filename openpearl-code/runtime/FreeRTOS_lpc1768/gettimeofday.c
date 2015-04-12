#include <sys/time.h>
#include <sys/errno.h>

int gettimeofday(struct timeval *__p, void *__tz){
	if(__tz)
		return ENOSYS;
	static time_t unixstamp = 1428607908;
	__p->tv_usec=0;//The type suseconds_t is a signed integral type capable of storing values at least in the range [-1, 1,000,00
	__p->tv_sec=unixstamp;
	unixstamp+=60;
	return 0;
}


