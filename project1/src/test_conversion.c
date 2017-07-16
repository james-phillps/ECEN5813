#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../include/common/conversion.h"

void big2lit_inv_ptr(void **state){
  (void) state;
}

void big2lit_val_convert(void **state){
  (void) state;
}

void lit2big_inv_ptr(void **state){
  (void) state;
}

void lit2big_val_convert(void **state){
  (void) state;
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
