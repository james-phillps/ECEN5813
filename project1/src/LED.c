#include "../include/kl25z/MKL25Z4.h"
#include "../include/common/LED.h"


void led_config(){
  //Configure LED
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;  //Clock gates Port B
  PORTB_PCR18 = (PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK);
  PORTB_PCR19 = (PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK);
  GPIOB_PDDR = 0x000C0000;
  GPIOB_PCOR |= 0x000C0000;
  set_off();

  return;
}

void set_red(){
  GPIOB_PSOR |= 0x000C0000;
  GPIOB_PCOR |= 0x00040000;
  return;
}

void set_grn(){
  GPIOB_PSOR |= 0x000C0000;
  GPIOB_PCOR |= 0x00080000;
  return;
}

void set_yel(){
  GPIOB_PSOR |= 0x000C0000;
  GPIOB_PCOR |= 0x000C0000;
  return;
}

void set_off(){
  GPIOB_PSOR |= 0x000C0000;
  return;
}

void led_blink(){
  return;
}
