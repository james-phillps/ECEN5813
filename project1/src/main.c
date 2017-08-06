#include "../include/common/project3.h"
#include "../include/common/memory.h"
#include "../include/common/circbuf.h"

#ifdef KL15Z
#include "../include/CMSIS/core_cm0plus.h"
#include "../include/kl25z/MKL25Z4.h"
#include "../include/CMSIS/core_cmFunc.h"
#include "../include/common/LED.h"
#include "../include/common/uart.h"
#include "../include/common/timer.h"
#endif


int main(void){
#ifdef KL25Z
  //Enable interrupts in CPU and NVIC
  __enable_irq(); //Enable CPU interrupt
  NVIC_ClearPendingIRQ(UART0_IRQn); //Clear any pending IRQ for UART0_IRQn
  NVIC_EnableIRQ(UART0_IRQn); //Enable UART0 interrupt in NVIC
  NVIC_ClearPendingIRQ(TPM2_IRQn);
  NVIC_EnableIRQ(TPM2_IRQn);
  NVIC_ClearPendingIRQ(DMA0_IRQn);
  NVIC_EnableIRQ(DMA0_IRQn);

  led_config();
  set_off();
  set_red();
  UART_configure();
  timer_init();
#endif

#ifdef PROJECT3
  project3();
#endif

return 0;
}
