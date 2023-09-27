//-----------------------------------------------------------------------------
// EFM8BB1_Blinky.c
//-----------------------------------------------------------------------------
// Copyright 2014 Silicon Laboratories, Inc.
// http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
//
// Program Description:
//
// This program flashes the LED on the EFM8BB1 LCK board about
// five times a second using the interrupt handler for Timer2.
//
// Resources:
//   SYSCLK - 24.5 MHz HFOSC / 8
//   Timer2 - 5 Hz interrupt
//   P1.4   - LED
//
//-----------------------------------------------------------------------------
// How To Test: EFM8BB1 LCK
//-----------------------------------------------------------------------------
// 1) Connect the EFM8BB1 LCK board to a PC using a micro USB cable.
// 2) Compile and download code to the EFM8BB1 LCK board.
//    In Simplicity Studio IDE, select Run -> Debug from the menu bar,
//    click the Debug button in the quick menu, or press F11.
// 3) Run the code.
//    In Simplicity Studio IDE, select Run -> Resume from the menu bar,
//    click the Resume button in the quick menu, or press F8.
// 4) The LED should blink at approximately 5 Hz.
//
// Target:         EFM8BB1
// Tool chain:     Generic
//
// Release 0.1 (MW, ST)
//    - Initial Revision
//    - 10 OCT 2014
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB1_Register_Enums.h>
#include <InitDevice.h>
#include <intrins.h>

volatile uint8_t trns[32]={0};
//pgfedcba
const  uint8_t charTable[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00};
SI_SBIT(LED0, SFR_P1, 4);

//*******************************************************************************************
void SiLabs_Startup (void)
{
  // Disable the watchdog here
}


void doPrint(float ds , uint8_t dp)
{
  uint8_t i,j,d,m,dc,dat[7],dg[4];
  d=ds/1000;
  for(i=0;i<7;i++){
    dat[i] = d;
    ds = ds - d*1000;
    ds = ds * 10;
    d = ds/1000;
  }
  i=0;
  while(i<3 & dat[i]==0) {dat[i]=10; i++;}
  if((i-dp)<=0) m=0; else m=i-dp;
  dc=3-i+m; if(dc==3) dc=5;
  for(d=0;d<4;d++) dg[d] = dat[d+i-m];//
  m =0x01;
//  for( j=0;j<4;j++){
//      trns[j] = charTable[dg[j]];
//  }
  m=0x01;
  d=0;
  for( i=0;i<8;i++){
      m = _crol_(m,1);//10100101--->11010010  00000001
      for( j=0;j<4;j++) {
          trns[d++] = ~(charTable[dg[j]] & m);
      }

  }
}
 
//-----------------------------------------------------------------------------
// Main Routine
//-----------------------------------------------------------------------------
void main (void)
{
   enter_DefaultMode_from_RESET();


   IE_EA = 1;                          // Enable global interrupts

   while (1) {
       doPrint(5237 , 5);
   }
}
