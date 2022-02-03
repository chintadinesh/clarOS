/* this is the test code for the functions
 */

#include "../../RTOS_Labs_common/Interpreter.h"

// copy paste all the libraries from the main file
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../RTOS_Labs_common/OS.h"
#include "../RTOS_Labs_common/ST7735.h"
#include "../RTOS_Labs_common/UART0int.h"
#include "../RTOS_Labs_common/eDisk.h"
#include "../RTOS_Labs_common/eFile.h"
#include "../inc/ADCSWTrigger.h"
#include "../inc/ADCT0ATrigger.h"

void test_Interpreter(void) { return; }

void test_clean_input(void) {
  shell_input = "   hello   ";
  clean_input(&shell_input);

  printf("%s\n", shell_input);
}

void execute_command() { execute_command(&shell_input); }
