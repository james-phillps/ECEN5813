/**
 * @file circbuf.c
 * @brief Circular buffer routines
 * Contains routines to manipulate and status circular buffer
 * @author James Phillips
 * @date 6/28/2017
 */

 #include "../include/common/circbuf.h"
 #include <stdlib.h>
 #include <stdint.h>


 CB_status_e CB_buffer_add_item(CB_t *buf_struct, uint8_t data){
   CB_status_e status = Success;
   //Check for null pointer
   if (buf_struct == 0){
     return status = NullError;
   }
   //Check if the buffer is full
   if ((buf_struct->count) == (buf_struct->size)){
     status = BuffFull;
     return status;
   }

   //Add item to buffer
   *(buf_struct->buff + buf_struct->head) = data;
   buf_struct->head++;
   buf_struct->count++;

   return status;
 }

 CB_status_e CB_buffer_remove_item(CB_t *buf_struct, uint8_t *data){
   CB_status_e status = Success;
   //Check for null pointers
   if ((buf_struct == 0) || (data == 0)){
     return status = NullError;
   }
   //Check if buffer is empty
   if ((buf_struct->count) == 0){
     status = BuffEmpty;
     return status;
   }

   //Remove item from buffer
   *data = *(buf_struct->buff + buf_struct->tail);
   buf_struct->tail++;
   buf_struct->count--;

   return status;
 }

 CB_status_e CB_is_full(CB_t *buf_struct){
   CB_status_e status = Success;
   //Check for null pointer
   if (buf_struct == 0){
     return status = NullError;
   }
   if ((buf_struct->count) == (buf_struct->size)){
     status = BuffFull;
   }

  return status;
 }

 CB_status_e CB_is_empty(CB_t *buf_struct){
   CB_status_e status = Success;
   //Check for null pointer
   if (buf_struct == 0){
     return status = NullError;
   }
   if ((buf_struct->count) == 0){
     status = BuffEmpty;
   }

   return status;
 }

 uint8_t CB_peek(CB_t *buf_struct, uint8_t Pos){
   //CB_status_e status = Success;   //Check for null pointer
   if (buf_struct == 0){
     return 0;
   }
   buf_struct->head += Pos;

   uint8_t peekdat = buf_struct->head;
   buf_struct->head -= Pos;


   return peekdat;
 }

 CB_status_e CB_init(CB_t **buf_struct, uint16_t length){
   CB_status_e status = Success;

   //Create the buffer structure
   *buf_struct = (CB_t *)malloc(sizeof(CB_t));

   //Structure point should no longer be NULL, should point to heap
   if(*buf_struct == NULL){
     return NullError;
   }

   //Initialize the structure
   (*buf_struct)->buff = malloc(sizeof(uint8_t)*length);
   (*buf_struct)->head = 0;
   (*buf_struct)->tail = 0;
   (*buf_struct)->size = length;
   (*buf_struct)->count = 0;

   //Check to see if buffer space was allocated on heap
   if ((*buf_struct)->buff == NULL){
     return NullError;
   }

   return status;
 }

 CB_status_e CB_destroy(CB_t *buf_struct){
   CB_status_e status =  Success;
   if (buf_struct == NULL){
     return NullError;
   }
   //Deallocate buffer space
   free((void*)buf_struct->buff);
   //Deallocate uffer structure
   free((void*)(buf_struct));

   return status;
 }

 void CB_Latency(void){
   #ifdef KL25Z
   uint32_t time = 0;
   CB_t *test_buf = NULL;
   uint16_t length = 0x00FF;
   uint8_t test_dat = 0;
   uint8_t *ptr = &test_dat;


   //Configure SysTick
   //Set the counter to maximum value
   mySysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
   //Reset the counter by writing any value
   mySysTick->VAL = 0;
   //Configure the SysTick
   mySysTick->CTRL |= 0x00000004;
   //Enable SysTick
   mySysTick->CTRL |= 0x00000001;

   //Call CB_Init()
   CB_init(&test_buf, length);
   latency[0] = 0x00FFFFFF - (mySysTick->VAL) & (0x00FFFFFF);

   //Disable SysTick
   mySysTick->CTRL &= ~0x00000001;
   //Reset SysTick
   mySysTick->VAL = 0;
   //Enable SysTick
   mySysTick->CTRL |= 0x00000001;
   CB_buffer_add_item(test_buf, 0xFF);
   latency[1] = 0x00FFFFFF - (mySysTick->VAL) & (0x00FFFFFF);

   //Disable SysTick
   mySysTick->CTRL &= ~0x00000001;
   //Reset
   mySysTick->VAL = 0;
   //Enable SysTick
   mySysTick->CTRL |= 0x00000001;
   CB_buffer_remove_item(test_buf, ptr);
   latency[2] = 0x00FFFFFF - (mySysTick->VAL) & (0x00FFFFFF);

   //Disable SysTick
   mySysTick->CTRL &= ~0x00000001;
   //Reset
   mySysTick->VAL = 0;
   //Enable SysTick
   mySysTick->CTRL |= 0x00000001;
   CB_is_full(test_buf);
   latency[3] = 0x00FFFFFF - (mySysTick->VAL) & (0x00FFFFFF);

   //Disable SysTick
   mySysTick->CTRL &= ~0x00000001;




   CB_destroy(test_buf);
   #endif
   return;
 }
