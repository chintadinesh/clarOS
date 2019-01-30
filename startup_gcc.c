//*****************************************************************************
//
// startup_gcc.c - Startup code for use with GNU tools.
//
// Copyright (c) 2013-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 2.1.4.178 of the Tiva Firmware Development Package.
//
//*****************************************************************************

#include <stdint.h>
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"

//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************

static void DefaultISR(void);
void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void MPUFault_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVCall_Handler(void);
void Debug_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void GPIOPortA_Handler(void);
void GPIOPortB_Handler(void);
void GPIOPortC_Handler(void);
void GPIOPortD_Handler(void);
void GPIOPortE_Handler(void);
void UART0_Handler(void);
void UART1_Handler(void);
void SSI0_Handler(void);
void I2C0_Handler(void);
void PWM0Fault_Handler(void);
void PWM00_Handler(void);
void PWM01_Handler(void);
void PWM02_Handler(void);
void QEI0_Handler(void);
void ADC0Seq0_Handler(void);
void ADC0Seq1_Handler(void);
void ADC0Seq2_Handler(void);
void ADC0Seq3_Handler(void);
void Watchdog_Handler(void);
void Timer0A_Handler(void);
void Timer0B_Handler(void);
void Timer1A_Handler(void);
void Timer1B_Handler(void);
void Timer2A_Handler(void);
void Timer2B_Handler(void);
void Comp0_Handler(void);
void Comp1_Handler(void);
void SysCtl_Handler(void);
void Flash_Handler(void);
void GPIOPortF_Handler(void);
void UART2_Handler(void);
void SSI1_Handler(void);
void Timer3A_Handler(void);
void Timer3B_Handler(void);
void I2C1_Handler(void);
void QEI1_Handler(void);
void CAN0_Handler(void);
void CAN1_Handler(void);
void Hibernate_Handler(void);
void USB0_Handler(void);
void PWM03_Handler(void);
void UDMA_Handler(void);
void UDMAError_Handler(void);
void ADC1Seq0_Handler(void);
void ADC1Seq1_Handler(void);
void ADC1Seq2_Handler(void);
void ADC1Seq3_Handler(void);
void SSI2_Handler(void);
void SSI3_Handler(void);
void UART3_Handler(void);
void UART4_Handler(void);
void UART5_Handler(void);
void UART6_Handler(void);
void UART7_Handler(void);
void I2C2_Handler(void);
void I2C3_Handler(void);
void Timer4A_Handler(void);
void Timer4B_Handler(void);
void Timer5A_Handler(void);
void Timer5B_Handler(void);
void WTimer0A_Handler(void);
void WTimer0B_Handler(void);
void WTimer1A_Handler(void);
void WTimer1B_Handler(void);
void WTimer2A_Handler(void);
void WTimer2B_Handler(void);
void WTimer3A_Handler(void);
void WTimer3B_Handler(void);
void WTimer4A_Handler(void);
void WTimer4B_Handler(void);
void WTimer5A_Handler(void);
void WTimer5B_Handler(void);
void SysExc_Handler(void);
void PWM10_Handler(void);
void PWM11_Handler(void);
void PWM12_Handler(void);
void PWM13_Handler(void);
void PWM1Fault_Handler(void);

//*****************************************************************************
//
// The entry point for the application.
//
//*****************************************************************************
extern int main(void);

//*****************************************************************************
//
// Reserve space for the system stack and define the initial stack pointer.
//
//*****************************************************************************
static uint32_t pui32Stack[64];
#define STACK_TOP ((uint32_t)pui32Stack + sizeof(pui32Stack))

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000.
//
//*****************************************************************************
__attribute__((section(".isr_vector")))
void (*const g_pfnVectors[])(void) = {
  (void (*)(void)) STACK_TOP,
  Reset_Handler,
  DefaultISR, // NMI_Handler,
  DefaultISR, // HardFault_Handler,
  DefaultISR, // MPUFault_Handler,
  DefaultISR, // BusFault_Handler,
  DefaultISR, // UsageFault_Handler,
  0,
  0,
  0,
  0,
  DefaultISR, // SVCall_Handler,
  DefaultISR, // Debug_Handler,
  0,
  DefaultISR, // PendSV_Handler,
  DefaultISR, // SysTick_Handler,
  DefaultISR, // GPIOPortA_Handler,
  DefaultISR, // GPIOPortB_Handler,
  DefaultISR, // GPIOPortC_Handler,
  DefaultISR, // GPIOPortD_Handler,
  DefaultISR, // GPIOPortE_Handler,
  DefaultISR, // UART0_Handler,
  DefaultISR, // UART1_Handler,
  DefaultISR, // SSI0_Handler,
  DefaultISR, // I2C0_Handler,
  DefaultISR, // PWM0Fault_Handler,
  DefaultISR, // PWM00_Handler,
  DefaultISR, // PWM01_Handler,
  DefaultISR, // PWM02_Handler,
  DefaultISR, // QEI0_Handler,
  DefaultISR, // ADC0Seq0_Handler,
  DefaultISR, // ADC0Seq1_Handler,
  DefaultISR, // ADC0Seq2_Handler,
  DefaultISR, // ADC0Seq3_Handler,
  DefaultISR, // Watchdog_Handler,
  DefaultISR, // Timer0A_Handler,
  DefaultISR, // Timer0B_Handler,
  DefaultISR, // Timer1A_Handler,
  DefaultISR, // Timer1B_Handler,
  DefaultISR, // Timer2A_Handler,
  DefaultISR, // Timer2B_Handler,
  DefaultISR, // Comp0_Handler,
  DefaultISR, // Comp1_Handler,
  0,
  DefaultISR, // SysCtl_Handler,
  DefaultISR, // Flash_Handler,
  DefaultISR, // GPIOPortF_Handler,
  0,
  0,
  DefaultISR, // UART2_Handler,
  DefaultISR, // SSI1_Handler,
  DefaultISR, // Timer3A_Handler,
  DefaultISR, // Timer3B_Handler,
  DefaultISR, // I2C1_Handler,
  DefaultISR, // QEI1_Handler,
  DefaultISR, // CAN0_Handler,
  DefaultISR, // CAN1_Handler,
  0,
  0,
  DefaultISR, // Hibernate_Handler,
  DefaultISR, // USB0_Handler,
  DefaultISR, // PWM03_Handler,
  DefaultISR, // UDMA_Handler,
  DefaultISR, // UDMAError_Handler,
  DefaultISR, // ADC1Seq0_Handler,
  DefaultISR, // ADC1Seq1_Handler,
  DefaultISR, // ADC1Seq2_Handler,
  DefaultISR, // ADC1Seq3_Handler,
  0,
  0,
  0,
  0,
  0,
  DefaultISR, // SSI2_Handler,
  DefaultISR, // SSI3_Handler,
  DefaultISR, // UART3_Handler,
  DefaultISR, // UART4_Handler,
  DefaultISR, // UART5_Handler,
  DefaultISR, // UART6_Handler,
  DefaultISR, // UART7_Handler,
  0,
  0,
  0,
  0,
  DefaultISR, // I2C2_Handler,
  DefaultISR, // I2C3_Handler,
  DefaultISR, // Timer4A_Handler,
  DefaultISR, // Timer4B_Handler,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  DefaultISR, // Timer5A_Handler,
  DefaultISR, // Timer5B_Handler,
  DefaultISR, // WTimer0A_Handler,
  DefaultISR, // WTimer0B_Handler,
  DefaultISR, // WTimer1A_Handler,
  DefaultISR, // WTimer1B_Handler,
  DefaultISR, // WTimer2A_Handler,
  DefaultISR, // WTimer2B_Handler,
  DefaultISR, // WTimer3A_Handler,
  DefaultISR, // WTimer3B_Handler,
  DefaultISR, // WTimer4A_Handler,
  DefaultISR, // WTimer4B_Handler,
  DefaultISR, // WTimer5A_Handler,
  DefaultISR, // WTimer5B_Handler,
  DefaultISR, // SysExc_Handler,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  DefaultISR, // PWM10_Handler,
  DefaultISR, // PWM11_Handler,
  DefaultISR, // PWM12_Handler,
  DefaultISR, // PWM13_Handler,
  DefaultISR  // PWM1Fault_Handler
};

//*****************************************************************************
//
// The following are constructs created by the linker, indicating where the
// the "data" and "bss" segments reside in memory.  The initializers for the
// for the "data" segment resides immediately following the "text" segment.
//
//*****************************************************************************
extern uint32_t _ldata;
extern uint32_t _data;
extern uint32_t _edata;
extern uint32_t _bss;
extern uint32_t _ebss;

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
void Reset_Handler(void) {
  uint32_t *pui32Src, *pui32Dest;

  //
  // Copy the data segment initializers from flash to SRAM.
  //
  pui32Src = &_ldata;
  for (pui32Dest = &_data; pui32Dest < &_edata;) {
    *pui32Dest++ = *pui32Src++;
  }

  //
  // Zero fill the bss segment.
  //
  __asm(
      "    ldr     r0, =_bss\n"
      "    ldr     r1, =_ebss\n"
      "    mov     r2, #0\n"
      "    .thumb_func\n"
      "zero_loop:\n"
      "        cmp     r0, r1\n"
      "        it      lt\n"
      "        strlt   r2, [r0], #4\n"
      "        blt     zero_loop");

/*
  //
  // Enable the floating-point unit.  This must be done here to handle the
  // case where main() uses floating-point and the function prologue saves
  // floating-point registers (which will fault if floating-point is not
  // enabled).  Any configuration of the floating-point unit using DriverLib
  // APIs must be done here prior to the floating-point unit being enabled.
  //
  // Note that this does not use DriverLib since it might not be included in
  // this project.
  //
  HWREG(NVIC_CPAC) =
      ((HWREG(NVIC_CPAC) & ~(NVIC_CPAC_CP10_M | NVIC_CPAC_CP11_M)) |
       NVIC_CPAC_CP10_FULL | NVIC_CPAC_CP11_FULL);
*/
  //
  // Call the application's entry point.
  //
  main();
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void DefaultISR(void) {
  //
  // Go into an infinite loop.
  //
  while (1) {
  }
}
