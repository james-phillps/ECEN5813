/**
 * @file uart.h
 * @brief Function prototypes for uart.c
 * Contains function protoypes for managing and configuring the UART
 * @author James Phillips
 * @date 6/28/2017
 */

 /**@brief Configures UART Settings
  * Configures UART settings
  * @param
  * Inputs: None
  * @return
  */
<type> UART_configure();

/**@brief Sends data over UART
 * Sends a single byte over the UART
 * @param
 * Inputs: Single byte
 * @return
 */
<type> UART_send(uint8_t * byte);

/**@brief Sends data over UART
 * Sends a single byte over the UART
 * @param
 * Inputs: pointer to a block of data, number of items to transmit
 * @return
 */
<type> UART_send_n(uint8_t * byte, size_t length);

/**@brief Sends data over UART
 * Sends a single byte over the UART
 * @param
 * Inputs: Single byte
 * @return
 */
<type> UART_receive(uint8_t * byte, size_t length);
