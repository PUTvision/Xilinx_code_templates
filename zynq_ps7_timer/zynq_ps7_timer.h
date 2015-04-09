/*
 * zynq_ps7_timer.h
 *
 * Created on: 18-06-2013
 * Author: Michal Fularz
 */

#ifndef _ZYNQ_PS7_TIMER_H_
#define _ZYNQ_PS7_TIMER_H_

#include <xil_types.h>

#ifdef __cplusplus
extern "C" {
#endif

int TIMER_init(u16 deviceId);

void TIMER_start(void);

void TIMER_stop(void);

u32 TIMER_getCurrentValue(void);

float TIMER_getTimeStartToValueInUs(u32 timerValue);

float TIMER_getTimeValueToStopInUs(u32 timerValue);

float TIMER_getTimeInMs(void);

float TIMER_getTimeInUs(void);

u32 TIMER_getTimeInClockCycles(void);

#ifdef __cplusplus
}
#endif

#endif /* _ZYNQ_PS7_TIMER_H_ */
