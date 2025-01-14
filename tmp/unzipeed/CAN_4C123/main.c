// Main.c
// Runs on LM4F120/TM4C123
// Main program for the CAN example.  Initialize hardware and software for
// CAN transfers.  Repeatedly send the status of the built-in buttons over
// the CAN and light up the built-in LEDs according to the response.
// Daniel Valvano
// December 31, 2019

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
  Program 7.5, example 7.6

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

// MCP2551 Pin1 TXD  ---- CAN0Tx PE5 (8) O TTL CAN module 0 transmit
// MCP2551 Pin2 Vss  ---- ground
// MCP2551 Pin3 VDD  ---- +5V with 0.1uF cap to ground
// MCP2551 Pin4 RXD  ---- CAN0Rx PE4 (8) I TTL CAN module 0 receive
// MCP2551 Pin5 VREF ---- open (it will be 2.5V)
// MCP2551 Pin6 CANL ---- to other CANL on network
// MCP2551 Pin7 CANH ---- to other CANH on network
// MCP2551 Pin8 RS   ---- ground, Slope-Control Input (maximum slew rate)
// 120 ohm across CANH, CANL on both ends of network
#include <stdint.h>

#include "../inc/CortexM.h"
#include "../inc/LaunchPad.h"
#include "../inc/PLL.h"
#include "../inc/Timer3A.h"
#include "../inc/can0.h"
#include "../inc/tm4c123gh6pm.h"

// CAN IDs are set dynamically at time of CAN0_Open
// Reverse on other microcontroller
#define RCV_ID 2
#define XMT_ID 4

uint8_t XmtData[4];
uint8_t RcvData[4];
uint32_t RcvCount = 0;
uint8_t sequenceNum = 0;

void UserTask(void) {
  XmtData[0] = PF0 << 1;     // 0 or 2
  XmtData[1] = PF4 >> 2;     // 0 or 4
  XmtData[2] = 0;            // unassigned field
  XmtData[3] = sequenceNum;  // sequence count
  CAN0_SendData(XmtData);
  sequenceNum++;
}

int main(void) {
  PLL_Init(Bus80MHz);  // bus clock at 80 MHz
  LaunchPad_Init();
  CAN0_Open(RCV_ID, XMT_ID);

  Timer3A_Init(&UserTask, 80000000 / 10, 2);  // initialize timer3 (10 Hz)
  EnableInterrupts();

  while (1) {
    if (CAN0_GetMailNonBlock(RcvData)) {
      RcvCount++;
      PF1 = RcvData[0];
      PF2 = RcvData[1];
      PF3 = RcvCount;  // heartbeat
    }
  }
}
