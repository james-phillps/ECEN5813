#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/common/circbuf.h"

void allocate_free(void **state){
  CB_t *buf_struct = NULL;
  uint16_t length = 256;
  CB_status_e status;

  status = CB_init(&buf_struct, length);
  assert_int_equal(status, 0);
  assert_non_null(buf_struct);
  assert_non_null(buf_struct->buff);
  //printf("Buf Struct is at 0x%p.\n", buf_struct);
  //printf("Circ buff starts at 0x%p.\n", buf_struct->buff);
  CB_destroy(buf_struct);
  //assert_null(buf_struct);
}

void inv_ptrs(void **state){
  CB_t *buf_struct = NULL;
  uint16_t length = 256;
  CB_status_e status;

  status = CB_init(&buf_struct, length);
  assert_int_equal(status, 0);
  assert_non_null(buf_struct);
  CB_destroy(buf_struct);
}

void non_init_buff(void **state){
  CB_t *buf_struct = NULL;
  uint16_t length = 256;

  CB_init(&buf_struct, length);
  assert_non_null(buf_struct->buff);
  CB_destroy(buf_struct);
}

void add_remove(void **state){
  CB_t *buf_struct = NULL;
  uint16_t length = 256;
  uint8_t dat = 0;
  uint8_t *dat_ptr = &dat;
  uint16_t i = 0;

  CB_init(&buf_struct, length);

  for(i = 0; i < length; i++){
    CB_buffer_add_item(buf_struct, (uint8_t) i);
  }

  for (i = 0; i < length; i++){
    CB_buffer_remove_item(buf_struct, dat_ptr);
    assert_int_equal(dat, (uint8_t) i);
  }
  CB_destroy(buf_struct);
}

void buff_full(void **state){
  CB_t *buf_struct = NULL;
  uint16_t length = 256;
  CB_status_e status;
  uint16_t i = 0;

  CB_init(&buf_struct, length);
  for (i = 0; i < length; i++){
    CB_buffer_add_item(buf_struct, (uint8_t) i);
  }
  status = CB_is_full(buf_struct);
  assert_int_equal(status, 1);

}

void buff_empty(void **state){
  CB_t *buf_struct = NULL;
  uint16_t length = 256;
  CB_status_e status;

  CB_init(&buf_struct, length);
  status = CB_is_empty(buf_struct);
  assert_int_equal(status, 2);
}

void wrap_add(void **state){
  CB_t *buf_struct = NULL;
  uint16_t length = 256;
  //CB_status_e status;
  uint16_t i = 0;
  uint8_t dat = 0;
  uint8_t *dat_ptr = &dat;

  CB_init(&buf_struct, length);

  //Populate buffer with data
  for (i = 0; i < length; i++){
    CB_buffer_add_item(buf_struct, (uint8_t) i);
  }
  //Buffer is now full
  assert_int_equal(buf_struct->head, 0); //head index should wrapped (next address to write to)
  assert_int_equal(buf_struct->tail, 0);
  assert_int_equal(buf_struct->count, 256);

  //Remove items from the beginning to avoid overfill
  for (i = 0 ; i < length; i++){
    CB_buffer_remove_item(buf_struct, dat_ptr);
  }
  assert_int_equal(buf_struct->head, 0);
  assert_int_equal(buf_struct->tail, 0);
  assert_int_equal(buf_struct->count, 0);

  //Add another item
  CB_buffer_add_item(buf_struct, 0xAA);
  assert_int_equal(buf_struct->head, 1);  //Confirm the index wraps
  assert_int_equal(buf_struct->tail, 0);
  assert_int_equal(buf_struct->count, 1);

  //Check the first buffer location, tail is still there
  assert_int_equal(*(buf_struct->buff + buf_struct->tail), 0xAA);
}

void wrap_remove(void **state){
  CB_t *buf_struct = NULL;
  uint16_t length = 256;
  //CB_status_e status;
  uint16_t i = 0;
  uint8_t dat = 3;
  uint8_t *dat_ptr = &dat;

  CB_init(&buf_struct, length);
  //Populate buffer so it's about to wrap
  for (i = 0; i < length -1; i++){
    CB_buffer_add_item(buf_struct, (uint8_t) i);
  }
  //Buffer is full, last value in the buffer should be 255

  assert_int_equal(buf_struct->head, 255); //head index will have wrapped
  assert_int_equal(buf_struct->count, 255);
  assert_int_equal(buf_struct->tail, 0);

  //Remove all data but 1 so that, the next remove should wrap the tail index
  for(i = 0; i < length -1; i++){
    CB_buffer_remove_item(buf_struct, dat_ptr);
  }
  assert_int_equal(buf_struct->head, 255);
  assert_int_equal(buf_struct->tail, 255);
  assert_int_equal(buf_struct->count, 0);

  //Add another value to wrap forward
  CB_buffer_add_item(buf_struct, 0xAA);
  assert_int_equal(buf_struct->head, 0);
  assert_int_equal(buf_struct->tail, 255);
  assert_int_equal(buf_struct->count, 1);
  assert_int_equal(*(buf_struct->buff + buf_struct->tail), 0xAA);

  //Remove item just assigned to wrap tail index
  CB_buffer_remove_item(buf_struct, dat_ptr);

  assert_int_equal(dat, 0xAA);
}

void overfill(void **state){
  CB_t *buf_struct = NULL;
  uint16_t length = 256;
  uint16_t i = 0;
  CB_status_e status;

  CB_init(&buf_struct, length);
  for (i = 0; i < length; i++){
    CB_buffer_add_item(buf_struct, (uint8_t) i);
  }
  //Buffer is full, last value in the buffer should be 255
  //Try to add another value

  status = CB_buffer_add_item(buf_struct, 0xAA);
  assert_int_equal(status, 1);

  //Check to make sure no new values were added
  assert_int_equal(*(buf_struct->buff), 0x00);
}

void overempty(void **state){
  CB_t *buf_struct = NULL;
  CB_status_e status;
  uint16_t length = 256;
  uint8_t dat = 0xAA;
  uint8_t *dat_ptr = &dat;

  CB_init(&buf_struct, length);
  //Buffer is empty right after initialization
  status = CB_buffer_remove_item(buf_struct, dat_ptr);
  assert_int_equal(status, 2);
}

int main(int argc, char **argv){
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(allocate_free),
    cmocka_unit_test(inv_ptrs),
    cmocka_unit_test(non_init_buff),
    cmocka_unit_test(add_remove),
    cmocka_unit_test(buff_full),
    cmocka_unit_test(buff_empty),
    cmocka_unit_test(wrap_add),
    cmocka_unit_test(wrap_remove),
    cmocka_unit_test(overfill),
    cmocka_unit_test(overempty)
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
