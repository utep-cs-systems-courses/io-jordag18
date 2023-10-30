#include <msp430.h>
#include "libTimer.h"
#include "led.h"

#define SW1 BIT3
#define SWITCHES SW1

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;
  
  configureClocks();
  enableWDTInterrupts();
  
  or_sr(0x18);
}

int blinkLimit = 5;
int blinkCount = 0;
int secondCount = 0;

void __interrupt_vec(WDT_VECTOR) WDT(){
  if (blinkCount == blinkLimit)
    blinkCount = 0;

  secondCount++;
  if (blinkCount <= 10)
    goto blink1;
  else{
    goto blink2;
  }
  
 blink1:
  if (secondCount >= 250){
    secondCount = 0;
    blinkCount++;
    P1OUT ^= LED_RED;
    P1OUT ^= LED_GREEN;
  }

 blink2:
  if (blinkCount >= 30)
    blinkCount = 0;
  if (secondCount >= 50){
    secondCount = 0;
    blinkCount++;
    P1OUT ^= LED_RED;
    P1OUT ^= LED_GREEN;
  }
}
