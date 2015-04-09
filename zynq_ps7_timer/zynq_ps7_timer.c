/*
 * zynq_ps7_timer.c
 *
 * Created on: 18-06-2013
 * Author: Michal Fularz
 */

#include "zynq_ps7_timer.h"

#include <xscutimer.h>

// timer for measurements
static XScuTimer Timer;							// Cortex A9 SCU Private Timer Instance
static XScuTimer *TimerInstancePtr = &Timer;

static volatile u32 startTime = 0;
static volatile u32 stopTime = 0;

static const float TIMER_FREQ_IN_MHZ = 333.0F;

int TIMER_init(u16 deviceId)
{
	/*
	 * Initialize the Scu Private Timer so that it is ready to use.
	 */
	 XScuTimer_Config *ConfigPtr = XScuTimer_LookupConfig(deviceId);
	/*
	 * This is where the virtual address would be used, this example uses physical address.
	 */
	int status = XScuTimer_CfgInitialize(TimerInstancePtr, ConfigPtr, ConfigPtr->BaseAddr);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	u8 val;
	val = XScuTimer_GetPrescaler(TimerInstancePtr);

	/*
	 * Load the timer counter register.
	 */
	XScuTimer_LoadTimer(TimerInstancePtr, 0xFFFFFFFF);

	return XST_SUCCESS;
}

void TIMER_start(void)
{
	/*
	 * Get a snapshot of the timer counter value before it's started
	 * to compare against later.
	 */
	startTime = XScuTimer_GetCounterValue(TimerInstancePtr);
	/*
	 * Start the Scu Private Timer device.
	 */
	XScuTimer_Start(TimerInstancePtr);
}

void TIMER_stop(void)
{
	 /*
	 * Stop the Scu Private Timer device.
	 */
	stopTime = XScuTimer_GetCounterValue(TimerInstancePtr);
	XScuTimer_Stop(TimerInstancePtr);
}

u32 TIMER_getCurrentValue(void)
{
	return XScuTimer_GetCounterValue(TimerInstancePtr);
}

float TIMER_getTimeStartToValueInUs(u32 timerValue)
{
	// the counter is counting down
	u32 timeInClockCycles = startTime - timerValue;

	float timeInUs = (float)timeInClockCycles * (1.0F / TIMER_FREQ_IN_MHZ);

	return timeInUs;
}

float TIMER_getTimeValueToStopInUs(u32 timerValue)
{
	// the counter is counting down
	u32 timeInClockCycles = timerValue - stopTime;

	float timeInUs = (float)timeInClockCycles * (1.0F / TIMER_FREQ_IN_MHZ);

	return timeInUs;
}

float TIMER_getTimeInMs(void)
{
	float timeInMs = TIMER_getTimeInUs() * (1.0F / 1000.0F);

	return timeInMs;
}

float TIMER_getTimeInUs(void)
{
	// the counter is counting down
	u32 timeInClockCycles = startTime - stopTime;

	float timeInUs = (float)timeInClockCycles * (1.0F / TIMER_FREQ_IN_MHZ);

	return timeInUs;
}

u32 TIMER_getTimeInClockCycles(void)
{
	// the counter is counting down
	u32 timeInClockCycles = startTime - stopTime;

	return timeInClockCycles;
}
