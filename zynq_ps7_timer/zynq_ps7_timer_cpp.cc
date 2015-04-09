/*
 * Author: Michal Fularz
 */

#include "zynq_ps7_timer_cpp.h"

StopWatch::StopWatch(u16 deviceId)
{
	this->timerInstancePtr = &this->timer;
	this->startTime = 0;
	this->stopTime = 0;

	this->Init(deviceId);
}

void StopWatch::Start(void)
{
	/*
	 * Get a snapshot of the timer counter value before it's started
	 * to compare against later.
	 */
	this->startTime = XScuTimer_GetCounterValue(this->timerInstancePtr);
	/*
	 * Start the Scu Private Timer device.
	 */
	XScuTimer_Start(this->timerInstancePtr);
}

void StopWatch::Stop(void)
{
	 /*
	 * Stop the Scu Private Timer device.
	 */
	this->stopTime = XScuTimer_GetCounterValue(this->timerInstancePtr);
	XScuTimer_Stop(this->timerInstancePtr);
}

int StopWatch::Init(u16 deviceId)
{
	/*
	 * Initialize the Scu Private Timer so that it is ready to use.
	 */
	 XScuTimer_Config *ConfigPtr = XScuTimer_LookupConfig(deviceId);
	/*
	 * This is where the virtual address would be used, this example uses physical address.
	 */
	int status = XScuTimer_CfgInitialize(this->timerInstancePtr, ConfigPtr, ConfigPtr->BaseAddr);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	u8 val;
	val = XScuTimer_GetPrescaler(this->timerInstancePtr);

	/*
	 * Load the timer counter register.
	 */
	XScuTimer_LoadTimer(this->timerInstancePtr, 0xFFFFFFFF);

	return XST_SUCCESS;
}

u32 StopWatch::GetCurrentValue(void)
{
	return XScuTimer_GetCounterValue(this->timerInstancePtr);
}

float StopWatch::GetTimeStartToValueInUs(u32 timerValue)
{
	// the counter is counting down
	u32 timeInClockCycles = this->startTime - timerValue;

	float timeInUs = (float)timeInClockCycles * (1.0F / this->TIMER_FREQ_IN_MHZ);

	return timeInUs;
}

float StopWatch::GetTimeValueToStopInUs(u32 timerValue)
{
	// the counter is counting down
	u32 timeInClockCycles = timerValue - this->stopTime;

	float timeInUs = (float)timeInClockCycles * (1.0F / this->TIMER_FREQ_IN_MHZ);

	return timeInUs;
}

float StopWatch::GetTimeInMs(void)
{
	float timeInMs = this->GetTimeInUs() * (1.0F / 1000.0F);

	return timeInMs;
}

float StopWatch::GetTimeInUs(void)
{
	float timeInUs = this->GetTimeInClockCycles() * (1.0F / TIMER_FREQ_IN_MHZ);

	return timeInUs;
}
