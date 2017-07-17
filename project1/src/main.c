#include <stdint.h>
#include "../include/common/project2.h"

int main(void){

#ifdef PROJECT2
  project2();
  dump_statistics();
#endif
}
