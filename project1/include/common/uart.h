/**
 * @file uart.h
 * @brief Function prototypes for uart.c
 * Contains function protoypes for managing and configuring the UART
 * @author James Phillips
 * @date 6/28/2017
 */

 #include <stdint.h>

 /**@brief Configures UART Settings
  * Configures UART settings
  * @param
  * Inputs: None
  * @return
  */
void UART_configure(void);

/**@brief Sends data over UART
 * Sends a single byte over the UART
 * @param
 * Inputs: Single byte
 * @return
 */
void UART_send(uint8_t * data);

/**@brief Sends data over UART
 * Sends a single byte over the UART
 * @param
 * Inputs: pointer to a block of data, number of items to transmit
 * @return
 */
void UART_send_n(uint8_t * data, uint8_t length);

/**@brief Sends data over UART
 * Sends a single byte over the UART
 * @param
 * Inputs: Single byte
 * @return
 */
void UART_receive(uint8_t * data);

void UART_receive_n(uint8_t * data, uint8_t length);

void UART0_IRQHandler(void);
