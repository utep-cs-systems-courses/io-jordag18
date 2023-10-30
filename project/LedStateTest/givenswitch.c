#include <msp430.h>
#include "libTimer.h"
#include "led.h"

#define SW1 BIT3
#define SWITCHES SW1

int main(void) {
  configureClocks();
  
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;

  P1REN |= SWITCHES;
  P1IE |= SWITCHES;
  P1OUT |= SWITCHES;
  P1DIR &= ~SWITCHES;
  
  or_sr(0x18);
}

void switch_interrupt_handler(){
  char p1val = P1IN;

  P1IES |= (p1val & SWITCHES);
  P1IES &= (p1val | ~SWITCHES);

  if (p1val & SW1){
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
  } else {
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
  }
}

void __interrupt_vec(PORT1_VECTOR) Port_1(){
  if(P1IFG & SWITCHES) {
    P1IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}
