/*
 * Author: Michal Fularz
 */

#ifndef _DMA_CTRL_H_
#define _DMA_CTRL_H_

#include <xil_types.h>				// for u32 type
#include <xaxidma.h>					// for axidma operations

int DMA_init(u32 AXI_DMA_DEVICE_ID, XAxiDma* AxiDmaPtr);

#endif
