/*
 * Author: Michal Fularz
 */

#include <stdio.h>
#include <xil_printf.h>
#include "platform/platform.h"

int main()
{
	init_platform();
		
	xil_printf("Hello World Zynq C++ bare metal application!\r\n");
	
	while(1)
	{
		asm("nop");
	}
	
	cleanup_platform();
	
	return 0;
}
