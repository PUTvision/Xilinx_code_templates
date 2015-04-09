/*
 * Author: Michal Fularz
 */


#ifndef _ZYNQ_PS7_TIMER_HPP_
#define _ZYNQ_PS7_TIMER_HPP_

#include <xil_types.h>

#include <xscutimer.h>

class StopWatch
{
private:
	XScuTimer timer;							// Cortex A9 SCU Private Timer Instance
	XScuTimer *timerInstancePtr;

	u32 startTime;
	u32 stopTime;

	static const float TIMER_FREQ_IN_MHZ = 333.0F;

public:
	StopWatch(u16 deviceId);
	void Start(void);
	void Stop(void);
	u32 GetCurrentValue(void);
	float GetTimeStartToValueInUs(u32 timerValue);
	float GetTimeValueToStopInUs(u32 timerValue);
	float GetTimeInMs(void);
	float GetTimeInUs(void);

private:
	int Init(u16 deviceId);
	inline u32 GetTimeInClockCycles(void)
	{
		// the counter is counting down
		u32 timeInClockCycles = this->startTime - this->stopTime;

		return timeInClockCycles;
	}
};

#endif /* _ZYNQ_PS7_TIMER_HPP_ */
