/**
 * @file memory.c
 * @brief Memory manipulation routines
 * Contains routines to easily manipulate memory addresses
 * @author James Phillips
 * @date 6/18/2017
 */

#include "../include/common/memory.h"
#include <stdlib.h>

/**9oa source to a destination location
 *Copies values beginning at a source location and ending after a given length
 * @param
 * Inputs: two byte pointers and length of memory to copy
 * @return - pointer to destination address
 */

uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length){
/* copy data located at src, with length 'length'.
Store data into dst.
Free memory at src.
Assumes memory already allocated at dst. */

uint8_t i = 0;
int32_t * tempptr;

tempptr = (int32_t *)malloc(sizeof(int)*length);
for (i = 0; i < length; i++)
{
  *(tempptr + i) = *(src +i);
}

for (i = 0; i < length; i++)
{
  *(dst + i) = *(tempptr + i);
}

free((void *)tempptr);


return dst;
}


/**
 * @brief - Copies values from allocated source to a destination location
 * Copies values beginning at a source location and ending after a given length
 * @param
 * Inputs: Pointer to memory source, pointer to memory destination, and length of
 * memory to copy
 * @return - pointer to destination address
 */

uint8_t * my_memcpy(uint8_t * src, uint8_t * dst, size_t length){
/* read data located at src, with length 'length'.
  copy data to ocation at dst
  Assumes memory already allocated at dst. */

  int8_t i = 0;

  for (i = 0; i < length; i++)
  {
    *(dst + i) = *(src + i);
  }

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
  int8_t i = 0;

  for (i = 0; i < length; i++)
  {
    *(src + i) = value;
  }
  /* This is odd that you pass the pointer as unsigned, but pass it back as signed */
  return src;
}

/**
 * @brief - Sets all memory locations to zero
 * Assigns a zero value to a block of memory
 * @param
 * Inputs: Pointer to memory source, size of memory block
 * @return - pointer to source address
 */
uint8_t * my_memzero(uint8_t * src, size_t length){

  uint8_t i = 0;
  for (i = 0; i<length; i++) /* cycle through memory of specified length */
  {
    *(src + i) = 0;
  }

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
  uint8_t temp = 0;
  int8_t i = 0;

  for (i = 0; i<length/2; i++)
  {
    temp = *(src + i);
    *(src + i) = *(src + length - 1 - i);
    *(src + length - 1 - i) = temp;
  }
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
  int32_t * ptr;
  ptr = (int32_t *)malloc(sizeof(int)*length);
  return ptr;
}

/**
 * @brief - Deallocates memory
 * Given a source address, deallocates the memory at the address
 * @param
 * Inputs: Source memory address
 * @return 0 if successful, 1 if not successful
 */
void free_words(uint32_t * src){

  free((void *)src);
  return;
}
