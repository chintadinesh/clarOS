// ADCSWTrigger.h
// Runs on LM4F120/TM4C123
// Provide functions that sample ADC inputs PD1, PD2, and
// PD3 using SS2 to be triggered by software and trigger
// three conversions, wait for them to finish, and run a
// user function with the results as parameters.
// Provide functions that sample ADC input PD0 using SS3
// to be triggered by software and trigger
// one conversion, wait for it to finish, and run a
// user function with the result as a parameter.
// Daniel Valvano
// August 18, 2014

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014

 Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
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

// There are many choices to make when using the ADC, and many
// different combinations of settings will all do basically the
// same thing.  For simplicity, this function makes some choices
// for you.  When calling this function, be sure that it does
// not conflict with any other software that may be running on
// the microcontroller.  Particularly, ADC0 sample sequencer 2
// is used here because it takes up to four samples, and three
// samples are needed.  Sample sequencer 2 generates a raw
// interrupt when the third conversion is complete, but it is
// not promoted to a controller interrupt.  Software triggers
// the ADC0 conversion and waits for the conversion to finish.
// If somewhat precise periodic measurements are required, the
// software trigger can occur in a periodic interrupt.  This
// approach has the advantage of being simple.  However, it does
// not guarantee real-time.
//
// A better approach would be to use a hardware timer to trigger
// the ADC conversion independently from software and generate
// an interrupt when the conversion is finished.  Then, the
// software can transfer the conversion result to memory and
// process it after all measurements are complete.
//
// This initialization function sets up the ADC according to the
// following parameters.  Any parameters not explicitly listed
// below are not modified:
// Max sample rate: <=125,000 samples/second
// Sequencer 0 priority: 1st (highest)
// Sequencer 1 priority: 2nd
// Sequencer 2 priority: 3rd
// Sequencer 3 priority: 4th (lowest)
// SS2 triggering event: software trigger, busy-wait sampling
// SS2 1st sample source: AIN6 (PD1)
// SS2 2nd sample source: AIN5 (PD2)
// SS2 3rd sample source: AIN4 (PD3)
// SS2 interrupts: enabled after 3rd sample but not promoted to controller
// 'task' is a pointer to a user function called after SS2 finishes
// the user function has three parameters that get the x-, y-, and
// z-values from the accelerometer passed by value
void ADC0_InitSWTriggerSeq2(void (*task)(uint32_t x, uint32_t y, uint32_t z));

//------------ADC0_InSeq2------------
// Busy-wait Analog to digital conversion initiates SS2 and
// calls the user function provided in the initialization with
// the results of the conversion in the parameters.
// UserTask2(AIN6, AIN5, AIN4);
// Input: none
// Output: none
// Samples ADC6, ADC5, and ADC4
// 125k max sampling
// software trigger, busy-wait sampling
void ADC0_InSeq2(void);

// This initialization function sets up the ADC according to the
// following parameters.  Any parameters not explicitly listed
// below are not modified:
// Max sample rate: <=125,000 samples/second
// Sequencer 0 priority: 1st (highest)
// Sequencer 1 priority: 2nd
// Sequencer 2 priority: 3rd
// Sequencer 3 priority: 4th (lowest)
// SS3 triggering event: software trigger, busy-wait sampling
// SS3 1st sample source: AIN7 (PD0)
// SS3 interrupts: enabled after 1st sample but not promoted to controller
// 'task' is a pointer to a user function called after SS3 finishes
// the user function has one parameter that gets the microphone
// sample passed by value
void ADC0_InitSWTriggerSeq3(void (*task)(uint32_t microphone));

//------------ADC0_InSeq3------------
// Busy-wait Analog to digital conversion initiates SS3 and
// calls the user function provided in the initialization with
// the results of the conversion in the parameters.
// UserTask3(AIN7);
// Input: none
// Output: none
// Samples ADC7
// 125k max sampling
// software trigger, busy-wait sampling
void ADC0_InSeq3(void);
