// *************Interpreter.c**************
// Students implement this as part of EE445M/EE380L.12 Lab 1,2,3,4
// High-level OS user interface
//
// Runs on LM4F120/TM4C123
// Jonathan W. Valvano 1/18/20, valvano@mail.utexas.edu
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

// Print jitter histogram
void Jitter(int32_t MaxJitter, uint32_t const JitterSize,
            uint32_t JitterHistogram[]) {
  // write this for Lab 3 (the latest)
}

void help() {
  printf("---Help---\n");
  printf("go        -  run prog");
}

/*
 * Parses the input shell string and removes the beginnign
 * and the ending white spaces
 */
void clean_input(char** shell_input) {
  bool starting_white_spaces_cleared = false;

  // first remove the empty spaces in the end;
  int len = strlen(*shell_input);
  while (len >= 0) {
    if (*(*shell_input + len - 1) == ' ')  // for space characters
      *(*shell_input + len - 1) = '\0';    // replace it with null
    else
      break;

    len--;
  }

  // start from the beginning and break when the first non space char is
  // encountered or the string reaches the end;
  while (!starting_white_spaces_cleared && *shell_input != NULL) {
    if (**shell_input == ' ')             // remove this space
      *shell_input = (*shell_input) + 1;  // update the address of start
                                          // of the array
    else
      break;  // non-whitespace is encountered
  }

  return;
}

/*
 * parse the input string and
 * execute the requested command.
 * if command is correct
 *      and input format is wrong,
 *      print the help
 * if the command is incorrect
 *      print an error in the console
 */
void execute_command(char* shell_input) {
  printf("Executing %s", shell_input);
  return;
}

// *********** Command line interpreter (shell) ************
void Interpreter(void) {
  // write this

  // store the input here
  char shell_input[MAX_INPUT_SIZE];

  // this is a shell. Hence, we shold never coume out of this
  for (int i = 0;; i++) {
    // print some shell identifier
    // Actually, this should go to the display
    printf(">")

        // read the input
        UART_InString(shell_input, MAX_INPUT_SIZE);

    // clean the input
    // remove the starting and the ending spaces
    // reference to array is passed because we need to change
    // the array starting address iteself
    clean_input(&shell_input);

    execute_command(&shell_input);
  }
}
