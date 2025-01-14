//*****************************************************************************
//
// ptpdlib.c - ptpd Library Abstraction Layer.
//
// Copyright (c) 2008-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.1.0.12573 of the Tiva Utility Library.
//
//*****************************************************************************

//*****************************************************************************
//
// Include the necessary system header files.
//
//*****************************************************************************
#include <limits.h>

//*****************************************************************************
//
// Include the library source code header files next.
//
//*****************************************************************************
#include "utils/ptpdlib.h"

//*****************************************************************************
//
// Include ptpd library code.
//
//*****************************************************************************
#include "ptpd-1.1.0/src/arith.c"
#include "ptpd-1.1.0/src/bmc.c"
#include "ptpd-1.1.0/src/protocol.c"

//*****************************************************************************
//
// Include ptpd porting layer code.
//
//*****************************************************************************
#include "ptpd-1.1.0/src/dep-tiva/ptpd_msg.c"
#include "ptpd-1.1.0/src/dep-tiva/ptpd_net.c"
#include "ptpd-1.1.0/src/dep-tiva/ptpd_servo.c"
#include "ptpd-1.1.0/src/dep-tiva/ptpd_timer.c"
