#include "../include/common/project3.h"
#include "../include/CMSIS/core_cm0plus.h"
#include "../include/kl25z/MKL25Z4.h"
#include "../include/CMSIS/core_cmFunc.h"
#include "../include/common/LED.h"
#include "../include/common/uart.h"
#include "../include/common/timer.h"
#include "../include/common/memory.h"
#include "../include/common/circbuf.h"

//Flags
uint8_t TPM0_TOF = 0;
volatile SysTick_Type *mySysTick = (SysTick_Type *)0xE000E010;
uint32_t latency[4] = {0, 0, 0, 0};

extern uint32_t __BUFFER_START;
uint8_t *ptr = (uint8_t *)&__BUFFER_START;


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
  uint32_t millsec = 50;
  uint32_t periph_time = 0;
  uint32_t NVIC_time = 0;

  led_config();
  set_off();
  set_red();
  UART_configure();
  timer_init();

  //timer_set(millsec);


  /*uint8_t data[4] = {0xAA, 0xBB, 0xCC, 0xDD};
  uint8_t data1[4] = {0x11, 0x22, 0x33, 0x44};
  uint8_t *src = data;
  uint8_t *dst = data1;
  size_t length = 4;
  uint8_t tran_size = 8;
  uint8_t value = 0xFF;

  memmove_dma(src, dst, length, tran_size);
  memset_dma(src, length, value);*/


  //periph_time = TPM_Latency_Periph();
  //NVIC_time = TPM_Latency_NVIC();

  //CB_Latency();


#endif

#ifdef PROJECT3
  project3();
#endif


}
