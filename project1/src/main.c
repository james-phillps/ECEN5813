#include <stdint.h>
#include "../include/common/project2.h"
#include "../include/common/platform.h"

int main(void){

#ifdef PROJECT2
  project2();
  dump_statistics();
#endif
}
