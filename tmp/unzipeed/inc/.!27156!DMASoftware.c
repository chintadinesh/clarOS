// DMASoftware.c
// Runs on LM4F120/TM4C123
// Software triggered memory block transfer
// Jonathan Valvano
// May 2, 2015

/* This example accompanies the book
   "Embedded Systems: Real Time Operating Systems for ARM Cortex M
 Microcontrollers", ISBN: 978-1466468863, Jonathan Valvano, copyright (c) 2015
   Section 6.4.5, Program 6.1

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
#include <stdint.h>

#include "../inc/tm4c123gh6pm.h"

// The control table used by the uDMA controller.  This table must be aligned to
// a 1024 byte boundary. each channel has source,destination,control,pad (pad
// word is ignored)
uint32_t ucControlTable[256] __attribute__((aligned(1024)));
// channel 30 is at indices 120,121,122 (primary source,destination,control) and
//               at indices 248,249,250 (alternate source,destination,control
//               not used)
#define CH30 (30 * 4)
#define BIT30 0x40000000
// ************DMA_Init*****************
// Initialize the memory to memory transfer
// This needs to be called once before requesting a transfer
// Inputs:  none
// Outputs: none
void DMA_Init(void) {
  int i;
  volatile uint32_t delay;
  for (i = 0; i < 256; i++) {
    ucControlTable[i] = 0;
  }
