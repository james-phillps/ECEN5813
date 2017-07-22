#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/common/circbuf.h"

void demo_test(void **state){
  CB_t *buf_struct = NULL;
  uint16_t length = 5;
  CB_status_e status;
  uint8_t i = 0;
  uint8_t data = 0;

  status = CB_init(&buf_struct, length);
  assert_int_equal(status, Success);
  assert_non_null(buf_struct);
  assert_non_null(buf_struct->buff);

  for(i = 0; i < 5; i++){
    CB_buffer_add_item(buf_struct, (uint8_t) i);
  }
  assert_int_equal(buf_struct->count, 5);
  for(i = 0; i < 5; i++){
    CB_buffer_remove_item(buf_struct, &data);
    assert_int_equal(data, (uint8_t) i);
  }

  status = CB_is_empty(buf_struct);
  assert_int_equal(status, BuffEmpty);

  status = CB_destroy(buf_struct);
  assert_int_equal(status, Success);
}

int main(int argc, char **argv){
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(demo_test),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
