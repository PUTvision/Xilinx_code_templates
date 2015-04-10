/*
 * Author: Michal Fularz
 */

#include <stdio.h>
#include <xil_printf.h>
#include "platform/platform.h"

#include "zynq_ps7_timer/zynq_ps7_timer.h"
#include "zynq_ps7_timer/zynq_ps7_timer_cpp.h"

static void TEST_zynq_ps7_timer_c_style(void)
{
	// init the timer by calling the function and passing the timer ID
	TIMER_init(XPAR_PS7_SCUTIMER_0_DEVICE_ID);

	TIMER_start();

	// put code to measure its execution here
	xil_printf("Using C   style!\r\n");

	TIMER_stop();

	// get elapsed time (from start to stop) in microseconds
	float elapsedTime = TIMER_getTimeInUs();
	printf("xil_printf took: %f us to execute\r\n", elapsedTime);
}

static void TEST_zynq_ps7_timer_cpp_style(void)
{
	// init the timer by creating class object and passing timer ID to the constructor
	StopWatch sw(XPAR_PS7_SCUTIMER_0_DEVICE_ID);


	// this time starting is done by using method of the class
	sw.Start();

	// put code to measure its execution here
	xil_printf("Using C++ style!\r\n");

	sw.Stop();

	// get elapsed time (from start to stop) in microseconds
	float elapsedTime = sw.GetTimeInUs();
	printf("xil_printf took: %f us to execute\r\n", elapsedTime);
}

int main()
{
	init_platform();

	xil_printf("Zynq bare metal ps7 timer application!\r\n");

	for(int i=0; i<10; ++i)
	{
		TEST_zynq_ps7_timer_cpp_style();
		TEST_zynq_ps7_timer_c_style();
	}

	while(1)
	{
		asm("nop");
	}
	
	cleanup_platform();
	
	return 0;
}
