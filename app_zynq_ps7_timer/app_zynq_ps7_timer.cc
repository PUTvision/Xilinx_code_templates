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
	TIMER_init(XPAR_PS7_SCUTIMER_0_DEVICE_ID);

	TIMER_start();

	xil_printf("Using C   style!\r\n");

	TIMER_stop();

	float elapsedTime = TIMER_getTimeInUs();
	printf("xil_printf took: %f us to execute\r\n", elapsedTime);
}

static void TEST_zynq_ps7_timer_cpp_style(void)
{
	StopWatch sw(XPAR_PS7_SCUTIMER_0_DEVICE_ID);

	sw.Start();

	xil_printf("Using C++ style!\r\n");

	sw.Stop();

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
