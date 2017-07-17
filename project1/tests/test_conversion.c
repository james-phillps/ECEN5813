#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../include/common/conversion.h"

void big2lit_inv_ptr(void **state){
  uint32_t *src = NULL;
  uint32_t length = 4;
  uint8_t result = 0;

  result = big_to_little32(src, length);
  assert_int_equal(result, 1);
}

void big2lit_val_convert(void **state){
  uint32_t input[2] = {0xDEADBEEF, 0xAABBCCDD};
  uint32_t *ptr_in = input;
  uint32_t length = 2;

  big_to_little32(ptr_in, length);
  assert_int_equal(input[1], 0xDDCCBBAA);


}

void lit2big_inv_ptr(void **state){
  uint32_t *src = NULL;
  uint32_t length = 4;
  uint8_t result = 0;

  result = little_to_big32(src, length);
  assert_int_equal(result, 1);

}

void lit2big_val_convert(void **state){
  uint32_t input[2] = {0xDEADBEEF, 0xDDCCBBAA};
  uint32_t *ptr_in = input;
  uint32_t length = 2;

  little_to_big32(ptr_in, length);
  assert_int_equal(input[1], 0xAABBCCDD);
}

int main(int argc, char **argv){
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(big2lit_inv_ptr),
    cmocka_unit_test(big2lit_val_convert),
    cmocka_unit_test(lit2big_inv_ptr),
    cmocka_unit_test(lit2big_val_convert)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
