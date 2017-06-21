/**
 * @file memory.c
 * @brief Memory manipulation routines
 * Contains routines to easily manipulate memory addresses
 * @author James Phillips
 * @date 6/18/2017
 */

#include "memory.h"

/**
 * @brief - Copies values from a source to a destination location
 *Copies values beginning at a source location and ending after a given length
 * @param
 * Inputs: two byte pointers and length of memory to copy
 * @return - pointer to destination address
 */
uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length){
  return dst;
}


/**
 * @brief - Copies values from a source to a destination location
 *Copies values beginning at a source location and ending after a given length
 * @param
 * Inputs: Pointer to memory source, pointer to memory destination, and length of
 * memory to copy
 * @return - pointer to destination address
 */
uint8_t * my_memcpy(uint8_t * src, uint8_t * dst, size_t length){
  return dst;
}

/**
 *  @brief - Sets all memory locations to a given value
 *  Given a source location, a length, and a value, memset sets all memory
 *  locations
 *  @param
 *  Inputs: Pointer to memory source, length of memory block, and value
 *  @return - pointer to source address
 */
int8_t * my_memset(uint8_t * src, size_t length, uint8_t value){
  return src;
}

/**
 * @brief - Sets all memory locationsd to zero
 * Assigns a zero value to a block of memory
 * @param
 * Inputs: Pointer to memory source, size of memory block
 * @return - pointer to source address
 */
uint8_t * my_memzero(uint8_t * src, size_t length){
  return src;
}

/**
 * @brief - Reverse order of memory values
 * Given a location and length, routine reverses the order of the values in
 * in memory.
 * @param
 * Inputs: Pointer to memory source, size of memory block
 * @return - pointer to source address
 */
uint8_t * my_reverse(uint8_t * src, size_t length){
  return src;
}

/**
 * @brief - Allocates memory, size in words
 * Routine allocates specified memory size (in words)
 * @param
 * Inputs: Size of memory block (in words)
 * @return - 0 if successful, 1 if not successful
 */
int32_t * reserve_words(size_t length){
  return 0;
}

/**
 * @brief - Deallocates memory
 * Given a source address, deallocates the memory at the address
 * @param
 * Inputs: Source memory address
 * @return 0 if successful, 1 if not successful
 */
void free_words(uint32_t * src){
  return;
}
