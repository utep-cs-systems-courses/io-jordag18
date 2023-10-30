#include <msp430.h>
#include "libTimer.h"

void configureClocks(){
  WDTCTL = WDTPW + WDTHOLD;
  BCSCTL1 = CALBC1_16MHZ;
  DCOCTL = CALDCO_16MHZ;

  BCSCTL2 &= ~(SELS);
  BCSCTL2 |= DIVS_3;
}

void enableWDTInterrupts(){
  WDTCTL = WDTPW |
    WDTTMSEL |
    WDTCNTCL |
    1;
  IE1 |= WDTIE;
}

void timerAUpmode(){
  TA0CCR0 = 0;
  TA0CCR1 = 0;
  TA0CCTL1 = OUTMOD_3;

  TACTL = TASSEL_2 + MC_1;
}
