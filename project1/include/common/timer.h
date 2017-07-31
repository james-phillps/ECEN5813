/**
 * @file timer.h
 * @Prototypes and function descriptions for timer functions
 * Prototypes for timer configuration enable/disable, and other settings
 * @author James Phillips
 * @date 7/25/2017
 */

 #include <stdint.h>
 #include "../kl25z/MKL25Z4.h"

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
