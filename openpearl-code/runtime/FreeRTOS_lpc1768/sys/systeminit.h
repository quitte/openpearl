/*
 * systeminit.h
 *
 *  Created on: 21.04.2015
 *      Author: quitte
 */

#ifndef SYS_SYSTEMINIT_H_
#define SYS_SYSTEMINIT_H_

#ifdef __cplusplus
extern "C" {
#endif

enum systeminit{
	CpuClock,
	ClockRTC,
	ClockMonotonicRealtime
};

void systeminit(enum systeminit);

#ifdef __cplusplus
}
#endif

#endif /* SYS_SYSTEMINIT_H_ */
