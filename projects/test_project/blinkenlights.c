/* blinkenlights.c */

#include <stdint.h>

#include "LED.h"
#include "PLL.h"
#include "SysTick.h"
#include "UART.h"

static const uint32_t DELAY = 50;  // =0.50 seconds
static const char *MSG_RED = "red\r\n";
static const char *MSG_GREEN = "green\r\n";
static const char *MSG_BLUE = "blue\r\n";

static void toggle(int i) {
  // cycle smoothly through the colors
  switch (i & 3) {
    case 0:
      LED_RedToggle();
      UART_OutString((char *)MSG_RED);
      break;
    case 1:
      LED_GreenToggle();
      UART_OutString((char *)MSG_GREEN);
      break;
    case 2:
      LED_RedToggle();
      UART_OutString((char *)MSG_RED);
      break;
    case 3:
      LED_BlueToggle();
      UART_OutString((char *)MSG_BLUE);
      break;
    default:
      break;
  }
}

int main(void) {
  PLL_Init(Bus80MHz);
  LED_Init();
  SysTick_Init();
  UART_Init();
  for (int i = 0; /*infinite loop*/; i++) {
    toggle(i);
    LED_RedToggle();
    SysTick_Wait10ms(DELAY);
    LED_GreenToggle();
    SysTick_Wait10ms(DELAY);
    LED_RedToggle();
    SysTick_Wait10ms(DELAY);
    LED_BlueToggle();
    SysTick_Wait10ms(DELAY);

    /*
    LED_BlueToggle();
    SysTick_Wait10ms(DELAY);
    LED_BlueToggle();
    SysTick_Wait10ms(DELAY);
    LED_BlueToggle();
    SysTick_Wait10ms(DELAY);



    LED_BlueToggle();
    SysTick_Wait10ms(DELAY);
    LED_BlueToggle();
    SysTick_Wait10ms(DELAY);
    LED_BlueToggle();
    SysTick_Wait10ms(DELAY);
    */
  }
}
