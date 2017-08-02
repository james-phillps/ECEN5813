/**
 * @file memory.c
 * @brief Memory manipulation routines
 * Contains routines to easily manipulate memory addresses
 * @author James Phillips
 * @date 6/18/2017
 */

#include "../include/common/memory.h"
#include "../include/kl25z/MKL25Z4.h"
#include <stdlib.h>

uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length){
  //Check for null pointers
  if ((src == NULL) || (dst == NULL)){
    return NULL;
  }

  if (src == dst){
    return dst;
  }

  uint8_t i = 0;
  ptrdiff_t diff = dst - src;

  if (abs(diff) < length){     //src and dst overlap
    if (diff < 0){        //end of dst writes on beginning of src
      dst = dst - (length - diff);
    }
    else if (diff > 0){   //beginning of dst writes on end of src
      dst = dst + (length - diff);
    }
  }

  for (i = 0; i<length; i++){
    *(dst + i) = *(src + i);
  }

  return dst;
}

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

uint8_t * my_memset(uint8_t * src, size_t length, uint8_t value){
  //Check for null pointer
  if (src == 0){
    return src;
  }

  int8_t i = 0;

  for (i = 0; i < length; i++)
  {
    *(src + i) = value;
  }
  /* This is odd that you pass the pointer as unsigned, but pass it back as signed */
  return src;
}

uint8_t * my_memzero(uint8_t * src, size_t length){
//Check for null pointer
  if(src == 0){
    return src;
  }

  uint8_t i = 0;
  for (i = 0; i<length; i++) /* cycle through memory of specified length */
  {
    *(src + i) = 0;
  }

  return src;
}

uint8_t * my_reverse(uint8_t * src, size_t length){
  //Check for null pointers
  if (src == NULL){
    return NULL;
  }
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

int32_t * reserve_words(size_t length){
  int32_t * ptr;
  ptr = (int32_t *)malloc(sizeof(int)*length);
  return ptr;
}

void free_words(uint32_t * src){

  free((void *)src);
  return;
}

uint8_t * memmove_dma(uint8_t * src, uint8_t * dst, size_t length, uint8_t tran_size){
  //Set clocks for DMA
  SIM_SCGC6 |= SIM_SCGC6_DMAMUX(1);
  SIM_SCGC7 |= SIM_SCGC7_DMA(1);

  //Set the source address
  DMA_SAR0 = (uint32_t)src;

  //Set the destination address
  DMA_DAR0 = (uint32_t)dst;

  //Configure the length
  DMA_DSR_BCR0 = (0x000FFFFF)&length;

  //Set the DCR
  if (tran_size == 32){
    DMA_DCR0 |= DMA_DCR_DSIZE(0) | DMA_DCR_SSIZE(0);
  }
  else if (tran_size == 16){
    DMA_DCR0 |= DMA_DCR_DSIZE(2) | DMA_DCR_SSIZE(2);
  }
  else{
    DMA_DCR0 |= DMA_DCR_DSIZE(1) | DMA_DCR_SSIZE(1);
  }

  DMA_DCR0 |= DMA_DCR_SINC(1) | DMA_DCR_DINC(1);
  DMA_DCR0 |= DMA_DCR_D_REQ(1);

  //Start the transfer
  DMA_DCR0 |= DMA_DCR_START(1);




   return dst;
}

uint8_t * memset_dma(uint8_t * src, size_t length, uint8_t value){
  //Set clocks for DMA
  SIM_SCGC6 |= SIM_SCGC6_DMAMUX(1);
  SIM_SCGC7 |= SIM_SCGC7_DMA(1);

  //Set the source address
  DMA_SAR1 = (uint32_t)&value;

  //Set the destination address
  DMA_DAR1 = (uint32_t)src;

  //Configure the length
  DMA_DSR_BCR1 = (0x000FFFFF)&length;

  DMA_DCR1 |= DMA_DCR_DINC(1) | DMA_DCR_DSIZE(1) | DMA_DCR_SSIZE(1);
  DMA_DCR1 |= DMA_DCR_D_REQ(1);

  //Start the transfer
  DMA_DCR1 |= DMA_DCR_START(1);

   return src;
}
