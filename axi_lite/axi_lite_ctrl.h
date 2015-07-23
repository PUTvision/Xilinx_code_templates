/*
 * Author: Michal Fularz
 */

#ifndef _AXI_LITE_CTRL_H_
#define _AXI_LITE_CTRL_H_

#include <xil_types.h>				// for u32 type
#include <xil_io.h>						// for axilite writes and reads

/*****************************************************
 *
 * COMMON CODE PART
 *
 ****************************************************/
inline u32 COMMON_readRegister(u32 ipCoreAddress, u32 registerNumber)
{
	// registerNumber*4
	u32 registerAddressOffset = registerNumber << 2;

	u32 result = Xil_In32(ipCoreAddress + registerAddressOffset);

	return result;
}

inline void COMMON_writeRegister(u32 ipCoreAddress, u32 registerNumber, u32 valueToWrite)
{
	// registerNumber*4
	u32 registerAddressOffset = registerNumber << 2;

	Xil_Out32(ipCoreAddress + registerAddressOffset, valueToWrite);
}

#endif /* _AXI_LITE_CTRL_H_ */
