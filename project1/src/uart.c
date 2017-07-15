/**
 * @file uart.c
 * @brief UART functions
 * Contains routines to configure and use the UART0
 * @author James Phillips
 * @date 7/11/2017
 */

 #include "../include/common/uart.h"
 #include "../include/kl25z/MKL25Z4.h"
 volatile UART0_Type *UARTPC = (UART0_Type *)0x4006A000;
 volatile OSC_Type *myOSC = (OSC_Type *)0x40065000;

 extern uint8_t char_rxd;

 void UART_configure(){
   //Configure clocks
   OSC_Type->CR = 0x80; //Flip clock gate for OSCERCLK
   SIM_SOPT2 |= 0x04000000; //Selects OSCERCLK for UART0
   SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK: //Turns on clock for Port A
   SIM_SCGC4 |= 0x00000400; //Enable the UART clock
   UART0_Type.BDH = 0x00; //Configure SBR
   UART0_Type.BDL = 0x0D;
   UART0_C4 = 0x0D; //Configure OSR

   //Configure GPIO pins
   PORTA_PCR1 = (PORT_PCR_MUX(2));
   PORTA_PCR2 = (PORT_PCR_MUX(2));
   PTA_BASE_PTR->PDDR |= (uint32_t)(1<<2);

   //Configure registers
   UART0_C2 = 0;
   UART0_C1 = 0;
   UART0_C3 = 0;
   UART0_S2 = 0;

   //Enable Interrupts
   UART0_C2 |= (uint32_t)(UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK);
   UART0_C2 |= (uint32_t)(UARTLP_C2_RIE_MASK);

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
     while(!(UART0_S1 & 0x40)){}
   }
   //Should also block on transmitting data
   return;
 }

uint8_t * UART_receive(uint8_t * data){

  //While loop until RX flag is set in UART0
  //
  //Should block until a character has been received
  *data = (uint8_t)UART0_D;
  return data;
}

void UART_receive_n(uint8_t * data, uint8_t length){
  //Should block until all characters have been received
  //For loop to length of data with while loop watching RX flag
}

void UART0_IRQHandler(void){
  if((UART0_S1 & UART_S1_RDRF_MASK)==UART_S1_RDRF_MASK){
		//data = (uint8_t)UART0_D;
		char_rxd = 1;
	}
  else if ((UART0_S1 & 0x80) == 0x80){
    while ((UART0_S1 & 0xC0) != 0x00){}
  }

  return;
}
