#include "dma_ctrl.h"

int DMA_init(u32 AXI_DMA_DEVICE_ID, XAxiDma* AxiDmaPtr)
{
	XAxiDma_Config *CfgPtr;
	int status;
	CfgPtr = XAxiDma_LookupConfig(AXI_DMA_DEVICE_ID);
	if(!CfgPtr){
		print("Error looking for AXI DMA config\n\r");
		return XST_FAILURE;
	}
	status = XAxiDma_CfgInitialize(AxiDmaPtr, CfgPtr);
	if(status != XST_SUCCESS){
		print("Error initializing DMA\n\r");
		return XST_FAILURE;
	}
	//check for scatter gather mode
	if(XAxiDma_HasSg(AxiDmaPtr)){
		print("Error DMA configured in SG mode\n\r");
		return XST_FAILURE;
	}
	//disable the interrupts from the DMA
	XAxiDma_IntrDisable(AxiDmaPtr, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(AxiDmaPtr, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);

	return XST_SUCCESS;
}
