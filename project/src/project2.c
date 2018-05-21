/**
 * @file project2.c
 * @brief Routines to run project2
 * Holds project2() for processing and statistics dump using printf
 * @author James Phillips
 * @date 7/17/2017
 */

#include <stdio.h>
#include "../include/common/circbuf.h"
#include "../include/common/platform.h"
#include "../include/common/uart.h"
#include "../include/common/conversion.h"
#include "../include/common/project2.h"

CB_t *buf_struct = NULL;
uint16_t length = 256;
//Stats variables
uint32_t alpha = 0;
uint32_t numeral = 0;
uint32_t punct = 0;
uint32_t misc = 0;
uint8_t breakchar = 0x21; //0x21 is exclamtion mark
extern uint8_t char_rxd;

void project2(void){

  //Initialize buffer
  CB_init(&buf_struct, length);
  #ifdef KL25Z
  process_data_kl25z();
  dump_statistics_kl25z();
  #endif

  #ifdef VERBOSE
  process_data();
  dump_statistics();
  #endif

  return;
}

void dump_statistics(void){
  printf("Number of alphabetics characters: %d\n", alpha);
  printf("Number of numerical characters: %d\n", numeral);
  printf("Number of punctuation characters: %d\n", punct);
  printf("Number of miscellaneous characters: %d\n", misc);

  return;
}

void process_data(){
  uint8_t data = 0;
  uint8_t end = 0;

  printf("Start typing...\n");

  while(end == 0){
      scanf("%c", &data);

    if(data == breakchar){
      break;
    }
    else if(data < 0x20){
      misc++;
    }
    else if(data < 0x30){
      punct++;
    }
    else if(data < 0x3A){
      numeral++;
    }
    else if(data < 0x41){
      punct++;
    }
    else if(data < 0x5B){
      alpha++;
    }
    else if(data < 0x61){
      punct++;
    }
    else if(data < 0x7B){
      alpha++;
    }
    else if(data < 0x7E){
      punct++;
    }
    else{
      misc++;
    }
    CB_buffer_add_item(buf_struct, data);
  }

  return;
}

void process_data_kl25z(){
  #ifdef KL25Z
  uint8_t dat = 0;

  while (char_rxd == 0){
    if(buf_struct->count != 0){
      CB_buffer_remove_item(buf_struct, &dat);
      if(dat == breakchar){
        break;
      }
      else if(dat < 0x20){
        misc++;
      }
      else if(dat < 0x30){
        punct++;
      }
      else if(dat < 0x3A){
        numeral++;
      }
      else if(dat < 0x41){
        punct++;
      }
      else if(dat < 0x5B){
        alpha++;
      }
      else if(dat < 0x61){
        punct++;
      }
      else if(dat < 0x7B){
        alpha++;
      }
      else if(dat < 0x7E){
        punct++;
      }
      else{
        misc++;
      }

    }
  }
  #endif
  return;
}

void dump_statistics_kl25z(){
  #ifdef KL25Z
  uint8_t stralpha[13] = "Alphabetic: ";
  uint8_t strnumeric[12] = "Numerical: ";
  uint8_t strpunct[14] = "Punctuation: ";
  uint8_t strmisc[6] = "Misc: ";

  uint8_t stralpha_val[32];
  uint8_t strnum_val[32];
  uint8_t strpunct_val[32];
  uint8_t strmisc_val[32];

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
  #endif
  return;
}
