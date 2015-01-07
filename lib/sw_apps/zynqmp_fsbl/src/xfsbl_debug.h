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
*****************************************************************************/

/*****************************************************************************/
/**
*
* @file xfsbl_debug.h
*
* This file contains the debug verbose information for FSBL print functionality
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver	Who	Date		Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a kc	11/05/13 Initial release
*
* </pre>
*
* @note
*
******************************************************************************/

#ifndef XFSBL_DEBUG_H
#define XFSBL_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xil_printf.h"
#include "xfsbl_config.h"
#include "xil_types.h"
/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/**
 * Debug levels for FSBL
 */
#define DEBUG_GENERAL	(0x00000001U)    /* general debug  messages */
#define DEBUG_INFO	(0x00000002U)    /* More debug information */
#define DEBUG_DETAILED	(0x00000004U)    /* More debug information */

#if defined (FSBL_DEBUG_DETAILED)
#define XFsblDbgCurrentTypes ((DEBUG_DETAILED) | (DEBUG_INFO) | (DEBUG_GENERAL))
#elif defined (FSBL_DEBUG_INFO)
#define XFsblDbgCurrentTypes ((DEBUG_INFO) | (DEBUG_GENERAL))
#elif defined (FSBL_DEBUG)
#define XFsblDbgCurrentTypes (DEBUG_GENERAL)
#else
#define XFsblDbgCurrentTypes (0U)
#endif

#if 0
__inline void XFsbl_Printf(u32 DebugType,char *Format, ...);
#else
#define XFsbl_Printf(DebugType,...) \
		if (((DebugType) & XFsblDbgCurrentTypes) != 0U)  {xil_printf (__VA_ARGS__); }
#endif

#ifdef __cplusplus
}
#endif

#endif /* XFSBL_DEBUG_H */
