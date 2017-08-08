#include "../include/common/project3.h"
#include "../include/common/memory.h"
//#include "../include/common/circbuf.h"

#ifdef KL25Z
#include "../include/CMSIS/core_cm0plus.h"
#include "../include/kl25z/MKL25Z4.h"
#include "../include/CMSIS/core_cmFunc.h"
#include "../include/common/LED.h"
#include "../include/common/uart.h"
#include "../include/common/timer.h"
#include "../include/common/spi.h"
#include "../include/common/nordic.h"
volatile SysTick_Type *mySysTick = (SysTick_Type *)0xE000E010;
#endif

CB_t *log_buf = NULL;
uint16_t buf_length = 256;



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

  uint8_t status = 0xFF;
  led_config();
  set_off();
  set_red();
  UART_configure();
  timer_init();
  SPI_init();
  set_yel();
  //status = nrf_read_status();
  set_grn();
#endif
//Initialize logger buffer
CB_init(&log_buf, buf_length);



#ifdef PROJECT3
  project3();
#endif

return 0;
}
