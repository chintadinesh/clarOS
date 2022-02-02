// SSD2119.c
// Steven Prickett (steven.prickett@gmail.com)
//
// Runs on LM4F120/TM4C123
// Driver for the SSD2119 interface on a Kentec 320x240x16 BoosterPack
// - Uses all 8 bits on PortB for writing data to LCD
//   and bits 4-7 on Port A for control signals
// - Adapted from original Kentec320x240x16_ssd2119_8bit.c driver by TI
//
// TODO:
// - bitmap drawing
// - touch support
// - insert copyright stuff
//
//  Data pin assignments:
//  PB0-7   LCD parallel data input
//
//  Control pin assignments:
//  PA4     RD  Read control signal             -------------------------
//  PA5     WR  Write control signal            | PA7 | PA6 | PA5 | PA4 |
//  PA6     RS  Register/Data select signal     | CS  | RS  | WR  | RD  |
//  PA7     CS  Chip select signal              -------------------------
//
//  Touchpad pin assignments:
//  PA2     Y-                                  -------------  -------------
//  PA3     X-                                  | PA3 | PA2 |  | PE5 | PE4 |
//  PE4     X+    AIN9                          | X-  | Y-  |  | Y+  | X+  |
//  PE5     Y+    AIN8                          -------------  -------------
//
//  Touchscreen resistance measurements:
//  -------------------
//  |1               2|                XN->YP       XP->YN
//  |                 |         1       1150         1400
//  |                 |         2       640           800
//  |        5        |         3       1400         1100
//  |                 |         4       870           580
//  |3               4|         5       1000          960
//  -------------------
//
//  XP->XN = 651
#include <stdint.h>

#include "../inc/SSD2119.h"
#include "../inc/tm4c123gh6pm.h"

// 4 bit Color 	 red,green,blue to 16 bit color
// bits 15-11 5 bit red
// bits 10-5  6-bit green
// bits  4-0  5-bit blue
unsigned short const Color4[16] = {
