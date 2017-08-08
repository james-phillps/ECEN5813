/**
 * @file logger.c
 * @brief Logger functions
 * Contains routines to configure and use the logger
 * @author James Phillips
 * @date 7/11/2017
 */

#include "../include/common/logger.h"

void log_data(uint8_t * p, size_t length){
   uint8_t i = 0;

   for (i = 0; i<length; i++){
     CB_buffer_add_item(log_buf, *(p + i));
   }

   return;
 }

void log_flush_kl25z(void){
  uint8_t data = 0;
  while(CB_is_empty(log_buf) != BuffEmpty){
    CB_buffer_remove_item(log_buf, &data);
    UART_send(&data);
    }
  return;
}

void log_string_kl25z(uint8_t *string){
  uint8_t i = 0;
  while(*(string + i) != 0x00){
    UART_send(string + i);
    i++;
  }
  return;
}

void log_integer_kl25z(int32_t integer){
  uint8_t myinteger[32];
  uint8_t length = 0;
  length = my_itoa(integer, myinteger, 10);
  UART_send_n(myinteger, length);

  return;
}

#ifdef BBB
void log_string_BBB(uint8_t *string){
  printf("%s \n", string);
  return;
}

void log_integer_BBB(int32_t integer){
  printf("%d ", integer);
  return;
}

void log_flush_BBB(void){
  uint8_t data = 0;
  while(CB_is_empty != BuffEmpty){
    CB_buffer_remove_item(log_buf, &data);
    printf("%d ", data);
  }
  return;
}
#endif
