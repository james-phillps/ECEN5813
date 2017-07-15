#include "../include/common/conversion.h"
#include "../include/common/debug.h"
#include "../include/common/memory.h"
#include "../include/common/project1.h"
#include "..include/CMSIS/core_cm0plus.h"
#include "../include/kl25z/KL25Z4.h"

#include <stdio.h>
#include <stdint.h>

#define SET_RED{ \
  GPIOB_PSOR |= 0x000C0000; \
  GPIOB_PCOR |= 0x00040000; \
}

#define SET_GRN{ \
  GPIOB_PSOR |= 0x000C0000; \
  GPIOB_PCOR |= 0x00080000; \
}

#define SET_YEL{ \
  GPIOB_PSOR |= 0x000C0000; \
  GPIOB_PCOR |= 0x000C0000; \
}

#define SET_OFF{ \
  GPIOB_PSOR |= 0x000C0000; \
}

uint8_t char_rxd = 0;
uint8_t dat = 0;
uint8_t *dat_prt = &dat;

int main(void)
{
  __enable_irq(); //Enable CPU interrupte
  NVIC_ClearPendingIRQ(UART0_IRQn); //Clear any pending IRQ for UART0_IRQn
  NVIC_EnableIRQ(UART0_IRQn); //Enable UART0 interrupt in NVIC

  //Configure LED
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;  //Clock gates Port B
  PORTB_PCR18 = (PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK);
  PORTB_PCR19 = (PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK);
  GPIO_PDDR = 0x000C0000;
  GPIOB_PCOR |= 0x000C0000;
  SET_OFF
  SET_RED


  CB_t *mycircbuff;
  CB_status_t mystatus;

  CB_init(mycircbuff, 1024);

  for(int i = 0; i < 10; i++){
    CB_buffer_add_item(mycircbuff, (uint8_t) i);
    print_cb_status(mycircbuff);
  }
  SET_GRN

  for(int i = 0; i < 10; i++){
    CB_buffer_remove_item(mycircbuff, dat_ptr);
    UART_send(*dat_ptr);
  }
  SET_YEL


  #ifdef PROJECT2
  project2();
  #endif
  return 0;
}
