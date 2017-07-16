#include "../include/common/conversion.h"
#include "../include/common/debug.h"
#include "../include/common/memory.h"
#include "../include/common/project1.h"
#include "../include/CMSIS/core_cm0plus.h"
#include "../include/kl25z/MKL25Z4.h"
#include "../include/common/circbuf.h"
#include "../include/common/uart.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define SET_RED { \
  GPIOB_PSOR |= 0x000C0000; \
  GPIOB_PCOR |= 0x00040000; \
}

#define SET_GRN { \
  GPIOB_PSOR |= 0x000C0000; \
  GPIOB_PCOR |= 0x00080000; \
}

#define SET_YEL { \
  GPIOB_PSOR |= 0x000C0000; \
  GPIOB_PCOR |= 0x000C0000; \
}

#define SET_OFF { \
  GPIOB_PSOR |= 0x000C0000; \
}

uint8_t char_rxd = 0;
uint8_t dat = 0;
uint8_t *dat_ptr = &dat;

int main(void)
{
  __enable_irq(); //Enable CPU interrupte
  NVIC_ClearPendingIRQ(UART0_IRQn); //Clear any pending IRQ for UART0_IRQn
  NVIC_EnableIRQ(UART0_IRQn); //Enable UART0 interrupt in NVIC

  //Configure LED
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;  //Clock gates Port B
  PORTB_PCR18 = (PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK);
  PORTB_PCR19 = (PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK);
  GPIOB_PDDR = 0x000C0000;
  GPIOB_PCOR |= 0x000C0000;
  SET_OFF
  SET_RED


  CB_t mycircbuff;
  CB_t *buff_ptr = &mycircbuff;
  //CB_status_t mystatus;
  uint8_t length = 255;

	//CB_init(mycircbuff, length);
	SET_RED
	//*mycircbuff = (CB_t*)malloc(sizeof(CB_t));
	mycircbuff.buff = (uint8_t *)calloc(length, sizeof(uint8_t));
	mycircbuff.head = 0;
	mycircbuff.tail = 0;
	mycircbuff.size = length;
	mycircbuff.count = 0;

  //CB_init(mycircbuff, 1024);

  for(int i = 0; i < 10; i++){
    CB_buffer_add_item(buff_ptr, (uint8_t) i);
  }
  SET_GRN

  for(int i = 0; i < 10; i++){
    CB_buffer_remove_item(buff_ptr, dat_ptr);
    UART_send(dat_ptr);
  }
  SET_YEL


  #ifdef PROJECT2
  project2();
  #endif
  return 0;
}
