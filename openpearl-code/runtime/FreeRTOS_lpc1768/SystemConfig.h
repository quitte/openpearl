/*
 [The "BSD license"]
 Copyright (c) 2015 Jonas Meyer
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
 3. The name of the author may not be used to endorse or promote products
    derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <stdint.h>

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
}

#endif /* SYSTEMCONFIG_H_ */
