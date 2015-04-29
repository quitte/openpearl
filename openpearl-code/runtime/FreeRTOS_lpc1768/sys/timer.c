/*
 * timer.c
 *
 *  Created on: 28.04.2015
 *      Author: quitte
 */
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
#include <time.h>
#include <sys/errno.h>
#include <stdio.h>


typedef unsigned int timerindex_t;
typedef unsigned char short_timer_t;//add macros to pick a fitting type.
//typedef struct{
//	TaskHandle_t				xTask;
//	void						*pvParameter;
//}FreeRTOS_TaskHook_t;

struct tableentry{
	short_timer_t				index;
	short_timer_t				next;
	short_timer_t				prev;
	struct sigevent *__restrict evp;	//actually a pointer to the FreeRTOS_TaskHook_T.
	struct itimerspec			value;
	struct itimerspec			*ovalue; //"return value that indicates what the timer didn't do"
};

static timer_t firstfree=0;
static timer_t first=0;

static struct tableentry table[8];//endof range is special and marks the end of things

static timer_t newtableentry(struct sigevent *__restrict evp, struct itimerspec value, struct itimerspec *ovalue){
	timer_t myindex;
	while(0){

	}
	return myindex;
}

static void deletetableentry(timer_t timerid){

}

extern int timer_create(clockid_t clock_id, struct sigevent *__restrict evp, timer_t *__restrict timerid){
	return ENOTSUP;
}

int timer_getoverrun(timer_t timerid){
	return ENOTSUP;
}

int timer_gettime(timer_t timerid, struct itimerspec *value){
	return ENOTSUP;
}

int timer_settime(timer_t timerid, int flags,
       const struct itimerspec *value,
       struct itimerspec *ovalue){
	if(flags!=TIMER_ABSTIME)
		;//value-=clock_gettime

	return ENOTSUP;
}
