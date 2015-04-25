/*
 * SystemConfig.h
 *
 *  Created on: 20.04.2015
 *      Author: quitte
 */
#include <stdint.h>
#include "systeminit.h"

#ifndef SYSTEMCONFIG_H_
#define SYSTEMCONFIG_H_

/* This is used as a worst case time to initialize the RTC with, if it doesn't
 * have a more recent, correct time */
#ifndef UNIXSTAMP
	#define UNIXSTAMP 1429364280 //Sat Apr 18 13:38:00 2015
#endif

/* System oscillator rate and RTC oscillator rate
 * lpc library needs those to calculate various clocks
 * */
const uint32_t OscRateIn = 12000000;
const uint32_t RTCOscRateIn = 32768;

/* SystemInit is called on startup. Needed due to the linkerscript, but dependencies
 * are probably preferrable */
/* Variables used in here will get overwritten before main() is started!!!
 * with newlib hjardware_init_hook and software_init hook make more sense*/
void SystemInit() {
//	systeminit(CpuClock);
//	systeminit(ClockMonotonicRealtime);
//	ClockInit();
//	SystemCoreClockUpdate();
}

#endif /* SYSTEMCONFIG_H_ */
