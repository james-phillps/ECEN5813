/**
 * @file timer.c
 * @Initialization, configuration, enable/disable of timer registers
 * Prototypes for timer configuration enable/disable, and other settings
 * @author James Phillips
 * @date 7/25/2017
 */

 #include "../include/common/timer.h"

 void timer_init(void){
   //Turns on clock to timer peripheral
   SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);   //MCGPLLCLK is TPM CLK source
   SIM_SCGC6 |= SIM_SCGC6_TPM2(1);        //TPM0 clock is enabled

   //Disable interrupts and counter (TPM0_SC (CMOD))
   TPM2_SC = 0;

   //Sets prescalar to divide clock (TPM0_SC (PS))
   TPM2_SC |= TPM_SC_PS(7);


   //Cofigures for compare mode

   return;
 }

 void timer_set(uint32_t time){
   //With OSCERCLK at 20971520 and the prescalar at 128
   //TMP0 clk is about 163840 Hz or 0.000006104 s
   //1 ms will require about 164 clk cycles

   //Takes time in milliseconds
   //Clear counter
   TPM2_CNT = TPM_CNT_COUNT(0);

   //Resets the modulo register to zero (TPM0_MOD)
   TPM2_MOD = TPM_MOD_MOD(0x0000FFFF&((uint32_t)(time*82)));

   //Enable CMOD and Interruptsj/
   TPM2_SC |= TPM_SC_TOIE(1) | TPM_SC_CMOD(1);

   return;
 }

void timer_blink_red(void){
  //Reconfigures LED port
  PORTB_PCR18 = (PORT_PCR_MUX(3));

  //Turn on clock to TPM2
  SIM_SOPT2 = SIM_SOPT2_TPMSRC(2);  //OSCERCLK is TPM CLK Source
  SIM_SCGC6 = SIM_SCGC6_TPM2(1);    //Enable clock gate for TMP2

  //Disable interrupts and counter for TPM2
  TPM2_SC = 0x00000000;

  //Sets prescalar to divide clock
  TPM2_SC |= 0x00000007;

  //Clears CNT register
  TPM2_CNT = 0x00000000;

  //Sets the modulo register for overflow
  TPM2_MOD = 0x00002008;
  TPM2_C0V = 0x00002008;

  //Enable channel interrupt, set to output compare, toggle pin
  TPM2_C0SC |= 0x0054;

  //Enable CMOD and interrupts, clear TOF flag
  TPM2_SC |= 0x00000080 | 0x00000040 | 0x00000008;


  return;
}

void TPM2_IRQHandler(void){

  /*if ((TPM2_STATUS&TPM_STATUS_TOF_MASK) == TPM_STATUS_TOF_MASK){
    //GPIOB_PTOR |= 0x00040000;
    //TPM2_STATUS |= TPM_STATUS_TOF_MASK; //Clear interrupt flag
  }*/

  return;
}

uint32_t TPM_Latency_Periph(void){
  uint32_t time = 0;

  //Manually trigger interrupt
  TPM2_CNT = TPM_CNT_COUNT(0);
  TPM2_MOD = TPM2_MOD = TPM_MOD_MOD(0x0000FFFF&((uint32_t)(50)));
  TPM2_CNT = TPM_CNT_COUNT(50);

  //Configure SysTick
  mySysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
  //Reset the counter by writing any value
  mySysTick->VAL = 0;
  //Configure the SysTick
  mySysTick->CTRL |= 0x00000004;

  //Enable SysTick
  mySysTick->CTRL |= 0x00000001;
  //Enable CMOD and Interrupts/
  TPM2_SC |= TPM_SC_TOIE(1) | TPM_SC_CMOD(1);

  time = 0x00FFFFFF - (mySysTick->VAL) & (0x00FFFFFF);
  //Disable SysTick
  mySysTick->CTRL &= ~0x00000001;
  return time;


}

uint32_t TPM_Latency_NVIC(void){
  uint32_t time = 0;

  //Configure SysTick
  //Set the counter to maximum value
  mySysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
  //Reset the counter by writing any value
  mySysTick->VAL = 0;
  //Configure the SysTick
  mySysTick->CTRL |= 0x00000004;
  //Enable SysTick
  mySysTick->CTRL |= 0x00000001;



  //Trigger interrupt
  NVIC_SetPendingIRQ(TPM2_IRQn);
  time = 0x00FFFFFF - (mySysTick->VAL) & (0x00FFFFFF);

  //Disable SysTick
  mySysTick->CTRL &= ~0x00000001;
  return time;

}
