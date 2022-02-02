// SDCTestMain.c
// Runs on TM4C123/LM4F120
// Test Secure Digital Card read/write interface by writing test
// data, reading them back, and verifying that they match as
// expected.  Running the unformatted file tests will destroy
// any formatting already on the disk.
// Valvano
// March 28, 2016

/* This example accompanies the books
   Embedded Systems: Real-Time Operating Systems for ARM Cortex-M
 Microcontrollers, Volume 3, ISBN: 978-1466468863, Jonathan Valvano, copyright
 (c) 2016

   Volume 3, Program 6.3, section 6.6   "Embedded Systems: Real Time Interfacing
 to Arm Cortex M Microcontrollers", ISBN: 978-1463590154, Jonathan Valvano,
 copyright (c) 2016

 Copyright 2016 by Jonathan W. Valvano, valvano@mail.utexas.edu
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
// there is a #define in eDisk.c to select SDC CS as PD7 or PB0
// hardware connections
// **********ST7735 TFT and SDC*******************
// ST7735
// Backlight (pin 10) connected to +3.3 V
// MISO (pin 9) connected to PA4 (SSI0Rx)
// SCK (pin 8) connected to PA2 (SSI0Clk)
// MOSI (pin 7) connected to PA5 (SSI0Tx)
// TFT_CS (pin 6) connected to PA3 (SSI0Fss) <- GPIO high to disable TFT
// CARD_CS (pin 5) connected to PD7/PB0 GPIO output
// Data/Command (pin 4) connected to PA6 (GPIO)<- GPIO low not using TFT
// RESET (pin 3) connected to PA7 (GPIO)<- GPIO high to disable TFT
// VCC (pin 2) connected to +3.3 V
// Gnd (pin 1) connected to ground

// **********wide.hk ST7735R*******************
// Silkscreen Label (SDC side up; LCD side down) - Connection
// VCC  - +3.3 V
// GND  - Ground
// !SCL - PA2 Sclk SPI clock from microcontroller to TFT or SDC
// !SDA - PA5 MOSI SPI data from microcontroller to TFT or SDC
// DC   - PA6 TFT data/command
// RES  - PA7 TFT reset
// CS   - PA3 TFT_CS, active low to enable TFT
// *CS  - PD7/PB0 SDC_CS, active low to enable SDC
// MISO - PA4 MISO SPI data from SDC to microcontroller
