// DMATimer.c
// Runs on LM4F120
// Periodic timer triggered DMA transfer
// Uses Timer5A to trigger the DMA, read from an 8-bit PORT, and then write to a
// memory Buffer There is a Timer5A interrupt after the buffer is full Jonathan
// Valvano May 2, 2015

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
// a 1024 byte boundary.
uint32_t ucControlTable[256] __attribute__((aligned(1024)));
// Timer5A uses uDMA channel 8 encoding 3
#define CH8 (8 * 4)
#define BIT8 0x00000100

// ***************** Timer5A_Init ****************
// Activate Timer5A trigger DMA periodically
// Inputs:  period in usec
// Outputs: none
void Timer5A_Init(uint16_t period) {
  volatile uint32_t Delay;
  SYSCTL_RCGCTIMER_R |= 0x20;   // 0) activate timer5
  Delay = 0;                    // wait for completion
  TIMER5_CTL_R &= ~0x00000001;  // 1) disable timer5A during setup
  TIMER5_CFG_R = 0x00000004;    // 2) configure for 16-bit timer mode
  TIMER5_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default
                                // down-count settings
  TIMER5_TAILR_R = period - 1;  // 4) reload value
  TIMER5_TAPR_R = 49;           // 5) 1us timer5A
  TIMER5_ICR_R = 0x00000001;    // 6) clear timer5A timeout flag
  TIMER5_IMR_R |= 0x00000001;   // 7) arm timeout interrupt
  NVIC_PRI23_R = (NVIC_PRI23_R & 0xFFFFFF00) | 0x00000040;  // 8) priority 2
  NVIC_EN2_R = 0x10000000;  // 9) enable interrupt 19 in NVIC
  // vector number 108, interrupt number 92
  TIMER5_CTL_R |= 0x00000001;  // 10) enable timer5A
  // interrupts enabled in the main program after all devices initialized
}
uint32_t Count = 0;
void Timer5A_Handler(void) {  // interrupts after each block is transferred
  TIMER5_ICR_R = TIMER_ICR_TATOCINT;  // acknowledge timer5A timeout
  Count++;
}
// ************DMA_Init*****************
// Initialize the PortF to memory transfer, triggered by timer 5A
// This needs to be called once before requesting a transfer
// The source address is fixed, destination address incremented each byte
// Inputs:  period in usec
// Outputs: none
void DMA_Init(uint16_t period) {
  int i;
  volatile uint32_t delay;
  for (i = 0; i < 256; i++) {
    ucControlTable[i] = 0;
  }
