/**
 * @file circbuf.h
 * @brief Function prototypes for circbuf.c
 * Contains function protoypes for circular buffer routines
 * @author James Phillips
 * @date 6/28/2017
 */


 /**@brief Adds data to circular buffer
  *Given a pointer to buffer and data to add, adds data to buffere and returns
  *Success or Failure as an enum
  * @param
  * Inputs: Pointer to circular buffer, data to be added to the circular buffer
  * @return - Enum specifying success/failure
  */
<CB enum type> CB_buffer_add_item(<buffer to add to>, <data to add>);

  /**@brief Removes data from circular buffer
   *Given a pointer to buffer and data to add, adds data to buffere and returns
   *Success or Failure as an enum
   * @param
   * Inputs: Pointer to circular buffer from which to remove data item,
   * Variable to store and return the removed item from buffer
   * @return - Enum specifying success/failure
   */
<CB enum type> CB_buffer_remove_item(<buffer to remove from>, <variable to store data removed>);

/**@brief Checks if buffer is full
 *Checks if the buffer passed is full and returns status or error codes
 * @param
 * Inputs: Circular buffer to check
 * @return - Status of circular buffer or error codes
 */
<CB enum type> CB_is_full(<buffer to check>);

/**@brief Checks if buffer is empty
 *Checks if the buffer passed is empty and returns status or error codes
 * @param
 * Inputs: Circular buffer to check
 * @return - Status of circular buffer or error codes
 */
<CB enum type> CB_is_empty(<buffer to check>);

/**@brief Peeks into buffer
 *Peaks at head of circular buffer
 * @param
 * Inputs: Pointer to the circular buffer to peak into, and the position relative
 * to the head of the buffer
 * @return - Status of circular buffer or error codes
 */
<CB enum type> CB_peek(<buffer to peak into>, <position to peek>);

/**@brief Checks if buffer is full
 *Checks if the buffer passed is full and returns status or error codes
 * @param
 * Inputs: Pointer to the circluar buffer to check and the length to be reserved
 * in buffer
 * @return - Status of circular buffer or error codes
 */
<CB enum type> CB_init(<poionter of buffer type>, <length of buffer>);

/**@brief Checks if buffer is full
 *Checks if the buffer passed is full and returns status or error codes
 * @param
 * Inputs: Buffer to be destroyed
 * @return - Status of circular buffer or error codes
 */
<CB enum type> CB_destroy(<pointer of buffer type>);
