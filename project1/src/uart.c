/**
 * @file uart.c
 * @brief UART functions
 * Contains routines to configure and use the UART0
 * @author James Phillips
 * @date 7/11/2017
 */

 #include "../include/common/uart.h"
 #include "../include/kl25z/MKL25Z4.h"

 void UART_configure(){
   //Configure clocks
   OSC_Type->CR = 0x80; //Flip clock gate for OSCERCLK
   SIM_SOPT2 |= 0x04000000; //Selects OSCERCLK for UART0




   return;
 }

 void UART_send(uint8_t * data){
   UART0_D = *(data);
   //Needs to block on transmitting data
   return;
 }

 void UART_send_n(uint8_t * data, uint8_t length){
   int i = 0;
   for (i = 0; i < length; i++){
     UART_send(data+i);
   }
   //Should also block on transmitting data
   return;
 }

uint8_t * UART_receive(uint8_t * data){

  //While loop until RX flag is set in UART0
  //
  //Should block until a character has been received
  return data;
}

void UART_receive_n(uint8_t * data, uint8_t length){
  //Should block until all characters have been received
  //For loop to length of data with while loop watching RX flag
}

void UART0_IRQHandler(){
  

  return;
}
