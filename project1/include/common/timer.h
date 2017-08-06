/**
 * @file timer.h
 * @Prototypes and function descriptions for timer functions
 * Prototypes for timer configuration enable/disable, and other settings
 * @author James Phillips
 * @date 7/25/2017
 */

 #include <stdint.h>
 #include "../kl25z/MKL25Z4.h"
 #include "../CMSIS/core_cm0plus.h"

volatile SysTick_Type *mySysTick = (SysTick_Type *)0xE000E010;



 /**@brief Initializes timer,
  * Initializes timer for compare
  *
  * @param
  * Inputs: None
  * @return None
  */

void timer_init(void);

/**@brief Enables timer interrupt
 * Initializes timer for compare
 *
 * @param
 * Inputs: None
 * @return None
 */
 void timer_set(uint32_t time);

 /**@brief Enables timer interrupt
  * Blinks red LED at 50 ms
  *
  * @param
  * Inputs: None
  * @return None
  */
 void timer_blink_red(void);

/**@brief Enables timer interrupt
 * Initializes timer for compare
 *
 * @param
 * Inputs: None
 * @return None
 */

void timer_enable(void);

/**@brief Disables timer interrupt
 * Initializes timer for compare
 *
 * @param
 * Inputs: None
 * @return None
 */
void timer_disable(void);

/**@brief Timer ISR
 * Handles Timer Interrupt
 *
 * @param
 * Inputs: None
 * @return Non
 */
void TPM2_IRQHandler();

/**@brief Measures latency in TPM2 ISR
 * Manually triggers in interupt in TPM2 and uses Systick to
 * measure the latency
 * @param
 * Inputs: None
 * @return Non
 */
uint32_t TPM_Latency_Periph(void);

/**@brief Measures latency in TPM2 ISR
 * Triggers TPM2 interrupt in NVIC and uses Systick to measure
 * the latency of the TPM2 ISR
 * @param
 * Inputs: None
 * @return Non
 */
uint32_t TPM_Latency_NVIC(void);

/**@brief Measures latency in TPM2 ISR
 * Triggers TPM2 interrupt in NVIC and uses Systick to measure
 * the latency of the TPM2 ISR
 * @param
 * Inputs: None
 * @return Non
 */
 void systick_set(void);

 /**@brief Measures latency in TPM2 ISR
  * Triggers TPM2 interrupt in NVIC and uses Systick to measure
  * the latency of the TPM2 ISR
  * @param
  * Inputs: None
  * @return Non
  */
uint32_t systick_read(void);
