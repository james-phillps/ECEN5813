/**
 * @file logger_queue.c
 * @brief Logger queue routines
 * Functions for the non-blocking logger
 * @author James Phillips
 * @date 8/7/2017
 */

#include "../include/common/logger_queue.h"

void RTC_Init(void){

  //Configure pins for 32KHz clocks
  SIM_SCGC5 |= SIM_SCGC5_PORTC(1);  //RTCLKIN is on PTC1, MUX(1);

  PORTC_PCR1 = PORT_PCR_MUX(1); //RTCLKIN, MUX(1)
  PORTC_PCR3 = PORT_PCR_MUX(1); //RTCLKOUT, MUX(1)

  //Configure the internal clock
  MCG_C1 |= MCG_C1_IRCLKEN_MASK;
  MCG_C2 &= ~MCG_C2_IRCS_MASK;

  uint32_t i = 0;
  //Select oscillator
  SIM_SOPT1 &= ~SIM_SOPT1_OSC32KSEL(3);
  //PORTC_PCR1 = PORT_PCR_MUX(1);

  //Enable clock gate
  SIM_SCGC6 |= SIM_SCGC6_RTC(1);

  //Disable RTC
  RTC_SR &= ~RTC_SR_TCE(1);
  RTC_CR |= RTC_CR_SUP(1);  //Allow non supervisor write accesses, just in case

  //Enable the oscillator
  RTC_CR |= RTC_CR_OSCE(1);

  //Wait until clock is stable (10 ms to 1 sec?)
  for(i = 0; i < 0x00010000; i++);

  //Zero TPR
  RTC_TPR = 0x00000001;

  //Zero TSR
  RTC_TSR = 0x00000001;

  //Enable times second interrupt
  RTC_IER |= RTC_IER_TSIE(1);

  //Enable RTC
  RTC_SR |= RTC_SR_TCE(1);

  return;
}

void RTC_Seconds_IRQHandler(void){
  //Log item HEARTBEAT
  uint8_t data = 0xAA;

  UART_send(&data);
  return;
}
