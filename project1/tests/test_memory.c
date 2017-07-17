#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../include/common/memory.h"

void memmove_inv_ptrs(void **state)
{
  uint8_t *src = NULL;
  uint8_t *dst = NULL;
  uint8_t length = 4;
  uint8_t *dst_out = &length;

  dst_out = my_memmove(src, dst, length);
  assert_null(dst_out);

}

void memmove_no_ovrlp(void **state)
{
  uint8_t data_src[4] = {0xFF, 0xFF, 0xFF, 0xFF};
  uint8_t *src_ptr = data_src;
  uint8_t data_dst[4] = {0xAA, 0xAA, 0xAA, 0xAA};
  uint8_t *dst_ptr = data_dst;
  uint8_t length = 4;

  my_memmove(src_ptr, dst_ptr, length);
  assert_int_equal(data_dst[3], data_src[3]);

}

void memmove_src_in_dst(void **state)
{
  uint8_t data_src[4] = {0xAA, 0xBB, 0xCC, 0xDD};
  uint8_t *src_ptr = data_src;
  uint8_t length = 4;
  uint8_t *dst_ptr = src_ptr + length - 2;

  my_memmove(src_ptr, dst_ptr, length);
  assert_int_equal(data_src[3], 0xDD);
}

void memmove_dst_in_src(void **state)
{
  uint8_t data_src[4] = {0xAA, 0xBB, 0xCC, 0xDD};
  uint8_t *src_ptr = data_src;
  uint8_t length = 4;
  uint8_t *dst_ptr = src_ptr - length + 2;

  my_memmove(src_ptr, dst_ptr, length);
  assert_int_equal(data_src[0], 0xAA);
}

void memset_inv_ptrs(void **state)
{
  uint8_t *in_ptr = NULL;
  uint8_t length = 8;
  uint8_t *out_ptr = &length;
  uint8_t value = 0xAA;

  out_ptr = my_memset(in_ptr, length, value);
  assert_null(out_ptr);
}

void memset_checkset(void **state)
{
  uint8_t data[4] = {0xFF, 0xFF, 0xFF, 0xFF};
  uint8_t *dat_ptr = data;
  uint8_t length = 4;
  uint8_t value = 0xAA;

  my_memset(dat_ptr, length, value);
  assert_int_equal(data[3], value);
}

void memzero_inv_ptrs(void **state)
{
  uint8_t *in_ptr = NULL;
  uint8_t length = 8;
  uint8_t *out_ptr = &length;

  out_ptr = my_memzero(in_ptr, length);
  assert_int_equal(out_ptr, NULL);

}

void memzero_checkset(void **state)
{
  uint8_t data[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  uint8_t *dat_ptr = data;
  uint8_t length = 8;

  my_memzero(dat_ptr, length);
  assert_int_equal(data[7], 0);

}

void reverse_inv_ptrs(void **state)
{
  uint8_t *data_in = NULL;
  uint8_t length = 4;
  uint8_t *data_out = &length;

  data_out = my_reverse(data_in, length);
  assert_null(data_out);
}

void reverse_odd(void **state)
{
  uint8_t data[5] = {0xAA, 0xBB, 0xCC, 0xDD, 0xFF};
  uint8_t *dat_in = data;
  uint8_t length = 5;
  uint8_t *dat_out = NULL;

  dat_out = my_reverse(dat_in, length);
  assert_int_equal(*(dat_out), 0xFF);
}

void reverse_even(void **state)
{
  uint8_t data[4] = {0xAA, 0xBB, 0xCC, 0xDD};
  uint8_t *dat_in = data;
  uint8_t length = 4;
  uint8_t *dat_out = NULL;

  dat_out = my_reverse(dat_in, length);
  assert_int_equal(*(dat_out), 0xDD);
}

void reverse_char_check(void **state)
{
  uint8_t data[256];
  uint8_t *dat_in = data;
  uint16_t length = 256;
  uint8_t *dat_out = NULL;
  uint16_t i = 0;

  for (i = 0; i < length; i++){
    *(dat_in + i) = (uint8_t)i;
  }

  dat_out = my_reverse(dat_in, length);
  assert_int_equal(*(dat_out), 0xFF);

}

int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(memmove_inv_ptrs),
    cmocka_unit_test(memmove_no_ovrlp),
    cmocka_unit_test(memmove_src_in_dst),
    cmocka_unit_test(memmove_dst_in_src),
    cmocka_unit_test(memset_inv_ptrs),
    cmocka_unit_test(memset_checkset),
    cmocka_unit_test(memzero_inv_ptrs),
    cmocka_unit_test(memzero_checkset),
    cmocka_unit_test(reverse_inv_ptrs),
    cmocka_unit_test(reverse_odd),
    cmocka_unit_test(reverse_even),
    cmocka_unit_test(reverse_char_check)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
