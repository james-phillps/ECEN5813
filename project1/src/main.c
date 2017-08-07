#include "../include/common/project3.h"
#include "../include/common/memory.h"
#include "../include/common/circbuf.h"

#ifdef KL25Z
#include "../include/CMSIS/core_cm0plus.h"
#include "../include/kl25z/MKL25Z4.h"
#include "../include/CMSIS/core_cmFunc.h"
#include "../include/common/LED.h"
#include "../include/common/uart.h"
#include "../include/common/timer.h"
#include "../include/common/spi.h"
volatile SysTick_Type *mySysTick = (SysTick_Type *)0xE000E010;
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

  uint8_t testbyte[8] = {0xAA, 0x55, 0xAA, 0x22, 0x22, 0x99, 0x33, 0xBB};
  led_config();
  set_off();
  set_red();
  UART_configure();
  timer_init();
  SPI_init();
  set_yel();
  SPI_write_byte(testbyte[3]);
  SPI_send_packet(testbyte, 8);
  set_grn();
#endif



/*#ifdef PROJECT3
  project3();
#endif*/

return 0;
}
