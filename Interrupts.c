
#include <SI_EFM8BB1_Register_Enums.h>
#include <intrins.h>


//extern uint8_t rotate(uint8_t r);
volatile unsigned char  retval=0xAA;

SI_SBIT(LED0, SFR_P1, 4);
extern volatile uint8_t trns[32];
uint8_t dscnr=0x11;

uint8_t rtt(uint8_t vlu){
  return vlu<<1;
}

SI_INTERRUPT(TIMER2_ISR, TIMER2_IRQn)
{
  static uint16_t cnt=0;
  TMR2CN0_TF2H= 0;
  //TMR2CN0_TF2L= 0;
  P1 = trns[cnt];
  P0 = dscnr;
  dscnr = _crol_(dscnr,1);
  cnt = (cnt+1) & 31;
}
