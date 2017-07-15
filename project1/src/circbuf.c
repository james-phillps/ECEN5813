/**
 * @file circbuf.c
 * @brief Circular buffer routines
 * Contains routines to manipulate and status circular buffer
 * @author James Phillips
 * @date 6/28/2017
 */

 CB_status_t CB_buffer_add_item(CB_t *buffer, uint8_t data){
   CB_status status = Success;
   //Check for null pointer
   if (buffer == 0){
     return status = NullError;
   }
   //Check if the buffer is full
   if ((buffer->count) == (buffer->size)){
     status = BuffFull;
     return status;
   }

   //Add item to buffer
   *(buffer->buff + buffer->head) = data;
   buffer->head++;
   //Account for roll over condition in buffer
   if ((buffer->head & (0x03FF)) == 0x0000){
     buffer->head = 0;
   }
   buffer->count++;

   return status;
 }

 CB_status_t CB_buffer_remove_item(CB_t *buffer, uint8_t *data){
   CB_status status = Success;
   //Check for null pointers
   if ((buffer = 0) || (data = 0)){
     return status = NullError;
   }
   //Check if buffer is empty
   if ((buffer->count) == 0){
     status = BuffEmpty;
     return status;
   }

   //Remove item from buffer
   *data = *(buffer->buff + buffer->tail);
   buffer->tail++;
   //Account for rollover condition
   if ((buffer->tail & (0x03FF)) == 0x0000){
     buffer->tail = 0;
   }
   buffer->count--;

   return status;
 }

 CB_status_t CB_is_full(CB_t *buffer){
   CB_status status = Success;
   //Check for null pointer
   if (buffer == 0){
     return status = NullError;
   }
   if ((buffer->count) == (buffer->size)){
     status = BuffFull;
   }

  return status;
 }

 CB_status_t CB_is_empty(CB_t *buffer){
   CB_status status = Success;
   //Check for null pointer
   if (buffer == 0){
     return status = NullError;
   }
   if ((buffer->count) == 0){
     status = BuffEmpty;
   }

   return status;
 }

 uint8_t CB_peek(CB_t *buffer, uint16_t Pos){
   CB_status status = Success;
   //Check for null pointer
   if (buffer == 0){
     return 0;
   }


   return *(buffer->head + Pos);
 }

 CB_status_t CB_init(CB_t *buffer, uint16_t length{
   CB_status status = Success;

   if (buffer == 0){
     return NullError;
   }

   buffer->buff = (uint8_t *)malloc(length);
   buffer->head = 0;
   buffer->tail = 0;
   buffer->size = length;
   buffer->count = 0;

   return status;
 }

 CB_status_t CB_destroy(CB_t *buffer){
   CB_status status =  Success;
   if (buffer == 0){
     return NullError;
   }
   free((void*)(mycircbuff->buff));

   return status;
 }
