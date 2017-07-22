#include "../include/common/project2.h"
#include "../include/CMSIS/core_cm0plus.h"
#include "../include/kl25z/MKL25Z4.h"
#include "../include/CMSIS/core_cmFunc.h"
#include "../include/common/LED.h"
#include "../include/common/uart.h"



int main(void){
#ifdef KL25Z
  //Enable interrupts in CPU and NVIC
  __enable_irq(); //Enable CPU interrupt
  NVIC_ClearPendingIRQ(UART0_IRQn); //Clear any pending IRQ for UART0_IRQn
  NVIC_EnableIRQ(UART0_IRQn); //Enable UART0 interrupt in NVIC

  led_config();
  set_red();
  UART_configure();
#endif


#ifdef PROJECT2
  project2();
#endif
}
