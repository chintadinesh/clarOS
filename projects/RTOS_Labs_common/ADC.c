// *************ADC.c**************
// EE445M/EE380L.6 Labs 1, 2, Lab 3, and Lab 4
// mid-level ADC functions
// you are allowed to call functions in the low level ADCSWTrigger driver
//
// Runs on LM4F120/TM4C123
// Jonathan W. Valvano Jan 5, 2020, valvano@mail.utexas.edu
#include <stdint.h>

#include "../inc/ADCSWTrigger.h"

// channelNum (0 to 11) specifies which pin is sampled with sequencer 3
// software start
// return with error 1, if channelNum>11,
// otherwise initialize ADC and return 0 (success)
int ADC_Init(uint32_t channelNum) {
  // put your Lab 1 code here

  // copied from:
  // ../Tester_4C123/ADCSWTrigger.c

  if (channelNum > 11 || channelNum < 0) return 1;

  volatile unsigned long delay;
  // 1) activate clock for Port E
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
  delay = SYSCTL_RCGCGPIO_R;  // 2) allow time for clock to stabilize
  delay = SYSCTL_RCGCGPIO_R;
  delay = SYSCTL_RCGCGPIO_R;
  delay = SYSCTL_RCGCGPIO_R;
  GPIO_PORTE_DIR_R &= ~0x10;   // 3) make PE4 input
  GPIO_PORTE_AFSEL_R |= 0x10;  // 4) enable alternate function on PE4
  GPIO_PORTE_DEN_R &= ~0x10;   // 5) disable digital I/O on PE4
                              // 5a) configure PE4 as ?? (skip this line because
                              // PCTL is for digital only)
  //  GPIO_PORTE_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFF0FFFF)+0x00000000;
  GPIO_PORTE_AMSEL_R |= 0x10;    // 6) enable analog functionality on PE4
  SYSCTL_RCGC0_R |= 0x00010000;  // 7) activate ADC0 (legacy code)
  //  SYSCTL_RCGCADC_R |= 0x00000001; // 7) activate ADC0 (actually doesn't
  //  work) SYSCTL_RCGC0_R &= ~0x00000300;  // 8) configure for 125K (legacy
  //  code)
  ADC0_PC_R &= ~0xF;            // 8) clear max sample rate field
  ADC0_PC_R |= 0x1;             //    configure for 125K samples/sec
  ADC0_SSPRI_R = 0x3210;        // 9) Sequencer 3 is lowest priority
  ADC0_ACTSS_R &= ~0x0008;      // 10) disable sample sequencer 3
  ADC0_EMUX_R &= ~0xF000;       // 11) seq3 is software trigger
  ADC0_SSMUX3_R &= ~0x000F;     // 12) clear SS3 field
  ADC0_SSMUX3_R += channelNum;  //    set channel
  ADC0_SSCTL3_R = 0x0006;       // 13) no TS0 D0, yes IE0 END0
  ADC0_IM_R &= ~0x0008;         // 14) disable SS3 interrupts
  ADC0_ACTSS_R |= 0x0008;       // 15) enable sample sequencer 3

  return 0;
}
// software start sequencer 3 and return 12 bit ADC result
uint32_t ADC_In(void) {
  // put your Lab 1 code here

  // copied from:
  // ../Tester_4C123/ADCSWTrigger.c

  uint32_t result;
  ADC0_PSSI_R = 0x0008;  // 1) initiate SS3
  while ((ADC0_RIS_R & 0x08) == 0) {
  };                                // 2) wait for conversion done
  result = ADC0_SSFIFO3_R & 0xFFF;  // 3) read result
  ADC0_ISC_R = 0x0008;              // 4) acknowledge completion
  return result;

  // return 1;
}
