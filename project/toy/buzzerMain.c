#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
int blinks = 0;
int led = 0;

int main() {
    configureClocks();
 
    buzzer_init();
    switch_init();
    led_init();
    //	/* start buzzing!!! 2MHz/1000 = 2kHz*/
    //Buddy Holly notes:
    //9631, 5727, 6428, 7645, 9631, 8581, 7645, 8581, 9631, 11453, 12857  
    enableWDTInterrupts();
    or_sr(0x18);          // CPU off, GIE on
}
int halfNoteLength = 200;
int quarterNoteLength = 94;
int eighthNoteLength = 48;
int seconds = 0;
int notes[]= {1275, 637, 1431, 637, 536, 637, 851,
	      956, 536, 2863, 1072, 1136, 1431, 1607,
	      1703, 1912, 1072, 1431, 1072, 1275, 1072};
int noteLength[] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0};
int i = 0;
int playSkrillex = 0;
int led_seconds = 0;
int playCrab = 0;
int crab_notes[] = {6825, 2145, 2554, 2554, 6825, 6825, 2272, 5730, 5730, 6825, 6825};
int crabNoteLength[] = {1, 1, 1, 0, 1, 0, 1 ,1 ,0, 1, 0};
int crab_seconds = 0;

void __interrupt_vec(WDT_VECTOR) WDT()
{
  //if(i = 0){
  //buzzer_set_period(9361);
  //}
  if(playSkrillex)
    play_scaryMonster();
  else if (playCrab)
    play_crabRave();
  else
    buzzer_set_period(0);
  
  led_seconds++;
  if(led_seconds >= blinks){
    led_seconds = 0;
    if(led)
      toggle_green();
    else
      toggle_red();
  }  
}

void play_scaryMonster()
{
  seconds++;
  if(i > 20){
    i = 0;
    playSkrillex = 0;
  }
  if(noteLength[i]){
    if(!i)
      buzzer_set_period(notes[0]);
    if(seconds >= quarterNoteLength){
      seconds = 0;
      i++;
      buzzer_set_period(notes[i]);
    }
  }
  else{
    if(seconds >= eighthNoteLength){
      seconds = 0;
      i++;
      buzzer_set_period(notes[i]);
    }
  }
}

int j = 0;
void play_crabRave()
{
  crab_seconds++;
  if(j > 10){
    j = 0;
    playCrab = 0;
  }
  if(crabNoteLength[i]){
    if(!j)
      buzzer_set_period(crab_notes[0]);
    if(crab_seconds >= quarterNoteLength){
      crab_seconds = 0;
      j++;
      buzzer_set_period(crab_notes[j]);
    }
  }
  else{
    if(crab_seconds >= eighthNoteLength){
      crab_seconds = 0;
      j++;
      buzzer_set_period(crab_notes[j]);
    }
  }
}
