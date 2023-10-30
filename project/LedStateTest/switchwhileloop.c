#include <msp430.h>
#include "libTimer.h"
#include "led.h"

#define SW1 BIT3
#define SWITCHES SW1

int main(void) {

  P1DIR |= BIT0;
  P1DIR |= BIT6;

  P1DIR &= ~BIT3;
  P1REN |= BIT3;
  P1OUT |= BIT3;

  while(1){
    if((P1IN & BIT3) == 0){
      P1OUT |= BIT0;
      P1OUT |= BIT6;
    }
    else {
      P1OUT &= ~BIT0;
      P1OUT &= ~BIT6;
    }
  }
  return 0;
}
