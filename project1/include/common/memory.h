/**
 * @file memory.h
 * @brief Function prototypes for memory.c
 * Contains function protoypes for memory manipulation routines
 * @author James Phillips
 * @date 6/18/2017
 */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#ifdef KL25Z
#include "../include/kl25z/MKL25Z4.h"
#endif


/**@brief source to a destination location
 *Copies values beginning at a source location and ending after a given length
 * @param
 * Inputs: two byte pointers and length of memory to copy
 * @return - pointer to destination address
 */
uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length);

/**
 * @brief - Copies values from allocated source to a destination location
 * Copies values beginning at a source location and ending after a given length
 * @param
 * Inputs: Pointer to memory source, pointer to memory destination, and length of
 * memory to copy
 * @return - pointer to destination address
 */
uint8_t * my_memcpy(uint8_t * src, uint8_t * dst, size_t length);

/**
 *  @brief - Sets all memory locations to a given value
 *  Given a source location, a length, and a value, memset sets all memory
 *  locations
 *  @param
 *  Inputs: Pointer to memory source, length of memory block, and value
 *  @return - pointer to source address
 */
uint8_t * my_memset(uint8_t * src, size_t length, uint8_t value);

/**
 * @brief - Sets all memory locations to zero
 * Assigns a zero value to a block of memory
 * @param
 * Inputs: Pointer to memory source, size of memory block
 * @return - pointer to source address
 */
uint8_t * my_memzero(uint8_t * src, size_t length);

/**
 * @brief - Reverse order of memory values
 * Given a location and length, routine reverses the order of the values in
 * in memory.
 * @param
 * Inputs: Pointer to memory source, size of memory block
 * @return - pointer to source address
 */
uint8_t * my_reverse(uint8_t * src, size_t length);

/**
 * @brief - Allocates memory, size in words
 * Routine allocates specified memory size (in words)
 * @param
 * Inputs: Size of memory block (in words)
 * @return - 0 if successful, 1 if not successful
 */

int32_t * reserve_words(size_t length);


 /**
  * @brief - Deallocates memory
  * Given a source address, deallocates the memory at the address
  * @param
  * Inputs: Source memory address
  * @return 0 if successful, 1 if not successful
  */
void free_words(uint32_t * src);


 /**
  * @brief - Moves data in memory using the DMA
  * Moves data in memory by using the DMA
  * @param
  * Inputs: Pointer to memory source, pointer to memory destination, length to move
  * @return: Pointer to destination address
  */
uint8_t * memmove_dma(uint8_t * src, uint8_t * dst, size_t length, uint8_t tran_size);

/**
 *  @brief - Sets all memory locations to a given value
 *  Given a source location, a length, and a value, memset sets all memory
 *  locations using the DMA
 *  @param
 *  Inputs: Pointer to memory source, length of memory block, and value
 *  @return - pointer to source address
 */
 uint8_t * memset_dma(uint8_t * src, size_t length, uint8_t value, uint8_t tran_size);

 void DMA0_IRQHandler(void);
