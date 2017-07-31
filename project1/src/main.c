#include "../include/common/project2.h"
#include "../include/CMSIS/core_cm0plus.h"
#include "../include/kl25z/MKL25Z4.h"
#include "../include/CMSIS/core_cmFunc.h"
#include "../include/common/LED.h"
#include "../include/common/uart.h"
#include "../include/common/timer.h"

//Flags
uint8_t TPM0_TOF = 0;


int main(void){
#ifdef KL25Z
  //Enable interrupts in CPU and NVIC
  __enable_irq(); //Enable CPU interrupt
  NVIC_ClearPendingIRQ(UART0_IRQn); //Clear any pending IRQ for UART0_IRQn
  NVIC_EnableIRQ(UART0_IRQn); //Enable UART0 interrupt in NVIC
  NVIC_ClearPendingIRQ(TPM2_IRQn);
  NVIC_EnableIRQ(TPM2_IRQn);
  uint32_t millsec = 50;

  led_config();
  set_off();
  //set_red();
  UART_configure();
  timer_blink_red();

#endif

while(1){
  if (TPM0_TOF == 1){
    GPIOB_PTOR |= 0x00040000;
    TPM0_TOF = 0;
  }
}




#ifdef PROJECT3
  project2();
#endif
}
