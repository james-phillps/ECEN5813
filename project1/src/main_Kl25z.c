/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "../include/kl25z/MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>

#include "../include/common/conversion.h"
#include "../include/common/memory.h"
#include "../include/CMSIS/core_cm0plus.h"
//#include "../Includes/MKL25Z4.h"
#include "../include/common/uart.h"
#include "../include/common/circbuf.h"

void dump_statistics(void);
void process_data(void);

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

uint8_t data = 0;
uint8_t *data_ptr = &data;

static int i = 0;
uint32_t alpha = 0;
uint32_t numeral = 0;
uint32_t punct = 0;
uint32_t misc = 0;

//Configure circular buffer
  uint16_t length = 256;
  CB_t *buf_struct;
  CB_status_e mystatus;

int main(void)
{

  __enable_irq(); //Enable CPU interrupt
  NVIC_ClearPendingIRQ(UART0_IRQn); //Clear any pending IRQ for UART0_IRQn
  NVIC_EnableIRQ(UART0_IRQn); //Enable UART0 interrupt in NVIC

  //Configure LED
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;  //Clock gates Port B
  PORTB_PCR18 = (PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK);
  PORTB_PCR19 = (PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK);
  GPIOB_PDDR = 0x000C0000;
  GPIOB_PCOR |= 0x000C0000;
  SET_OFF
  SET_GRN

  UART_configure();


  CB_init(&buf_struct, length);
  SET_RED

  while(1)
  {
	  if (char_rxd == 1){
		  break;
	  }
	  if(buf_struct->count != 0){
		  process_data();
	  }
  }
  SET_GRN
  char_rxd = 0;

  dump_statistics();

	//Destroy buffer
	CB_destroy(buf_struct);



  SET_YEL

    /* This for loop should be replaced. By default this loop allows a single stepping. */
    for (;;) {
        i++;
    }
    /* Never leave main */
    return 0;
}

void process_data(){
	uint8_t testdat;
	while(buf_struct->count != 0){
		CB_buffer_remove_item(buf_struct, &testdat);
		if(testdat < 0x20){
			misc++;
		}
		else if(testdat < 0x30){
			punct++;
		}
		else if(testdat < 0x3A){
			numeral++;
		}
		else if(testdat < 0x41){
			punct++;
		}
		else if(testdat < 0x5B){
			alpha++;
		}
		else if(testdat < 0x61){
			punct++;
		}
		else if(testdat < 0x7B){
			alpha++;
		}
		else if(testdat < 0x7E){
			punct++;
		}
		else{
			misc++;
		}
	}
	return;
}

void dump_statistics(){
	char stralpha[13] = "Alphabetic: ";
	char strnumeric[12] = "Numerical: ";
	char strpunct[14] = "Punctuation: ";
	char strmisc[6] = "Misc: ";

	char stralpha_val[32];
	char strnum_val[32];
	char strpunct_val[32];
	char strmisc_val[32];

	uint8_t alpha_val_len = 0;
	uint8_t num_val_len = 0;
	uint8_t punct_val_len = 0;
	uint8_t misc_val_len = 0;

	uint8_t car_return = 0x0D;
	uint8_t *CR = &car_return;

	uint8_t linefeed = 0x0A;
	uint8_t *LF = &linefeed;


	alpha_val_len = my_itoa(alpha, stralpha_val, 10);
	num_val_len = my_itoa(numeral, strnum_val, 10);
	punct_val_len = my_itoa(punct, strpunct_val, 10);
	misc_val_len = my_itoa(misc, strmisc_val, 10);

	/*for (int i = 0; i < alpha_val_len; i++){
		UART_send(stralpha_val + i);
		for (int j = 0; j < 10000; j++){}
	}
	UART_send(CR);
	UART_send(LF);*/

	UART_send_n(stralpha, 13);
	UART_send_n(stralpha_val, alpha_val_len);
	UART_send(CR);
	UART_send(LF);

	UART_send_n(strnumeric, 12);
	UART_send_n(strnum_val, num_val_len);
	UART_send(CR);
	UART_send(LF);

	UART_send_n(strpunct, 14);
	UART_send_n(strpunct_val, punct_val_len);
	UART_send(CR);
	UART_send(LF);

	UART_send_n(strmisc, 6);
	UART_send_n(strmisc_val, misc_val_len);
	UART_send(CR);
	UART_send(LF);


	return;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
