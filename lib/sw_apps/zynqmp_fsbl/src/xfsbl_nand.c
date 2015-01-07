/******************************************************************************
*
* Copyright (C) 2015 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* XILINX CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xfsbl_nand.c
*
* This is the file which contains nand related code for the FSBL.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   04/21/14 Initial release
*
* </pre>
*
* @note
*
******************************************************************************/
/***************************** Include Files *********************************/
#include "xfsbl_hw.h"

#ifdef XFSBL_NAND

#include "xnandps8.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define NAND_DEVICE_ID          0

/************************** Function Prototypes ******************************/


/************************** Variable Definitions *****************************/
XNandPs8_Config *Config;
XNandPs8 NandInstance;                  /* XNand Instance */
XNandPs8 *NandInstPtr = &NandInstance;


/*****************************************************************************/
/**
 * This function is used to initialize the qspi controller and driver
 *
 * @param	None
 *
 * @return	None
 *
 *****************************************************************************/
u32 XFsbl_NandInit(void )
{
	u32 Status = XFSBL_SUCCESS;

	Config = XNandPs8_LookupConfig(NAND_DEVICE_ID);
        if (Config == NULL) {
                Status = XFSBL_ERROR_NAND_INIT;
		XFsbl_Printf(DEBUG_GENERAL,"XFSBL_ERROR_NAND_INIT\r\n");
                goto END;
        }
        /**
         * Initialize the NAND flash driver.
         */
        Status = (u32 )XNandPs8_CfgInitialize(NandInstPtr, Config,
                        Config->BaseAddress);
        if (Status != XST_SUCCESS) {
                Status = XFSBL_ERROR_NAND_INIT;
		XFsbl_Printf(DEBUG_GENERAL,"XFSBL_ERROR_NAND_INIT\r\n");
                goto END;
        }

	XFsbl_Printf(DEBUG_INFO,"Nand Init Success\r\n");
END:
	return Status;
}

/*****************************************************************************/
/**
 * This function is used to copy the data from NAND to destination
 * address
 *
 * @param SrcAddress is the address of the NAND flash where copy should
 * start from
 *
 * @param DestAddress is the address of the destination where it
 * should copy to
 *
 * @param Length Length of the bytes to be copied
 *
 * @return
 * 		- XFSBL_SUCCESS for successful copy
 * 		- errors as mentioned in xfsbl_error.h
 *
 *****************************************************************************/
u32 XFsbl_NandCopy(u32 SrcAddress, PTRSIZE DestAddress, u32 Length)
{
	u32 Status = XFSBL_SUCCESS;

	Status = (u32 )XNandPs8_Read(NandInstPtr, (u64)SrcAddress, (u64)Length,
                                               (u8 *) DestAddress);
	if (Status != XST_SUCCESS) {
		Status = XFSBL_ERROR_NAND_READ;
		XFsbl_Printf(DEBUG_GENERAL,"XFSBL_ERROR_NAND_READ\r\n");
                goto END;
        }
END:
	return Status;
}

/*****************************************************************************/
/**
 * This function is used to release the nand settings
 *
 * @param	None
 *
 * @return	None
 *
 *****************************************************************************/
u32 XFsbl_NandRelease(void )
{

	return XFSBL_SUCCESS;
}


#endif /*  end of #ifdef XFSBL_NAND */
