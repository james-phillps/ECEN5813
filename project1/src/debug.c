
// #include
#include <stdio.h>
#include <stdint.h>
#include "../include/common/debug.h"

/*!
* @enable/disable debug printing with compile time switch
* if enabled, this takes a pointer to memory and prints the bytes given to a pointer location and the length of the bytes to print
* @Jordan Wachs
* @06-18-17
*/

void print_memory(uint8_t * start, uint32_t length){
uint8_t val = 0;
int8_t i = 0;
uint8_t *ptr;

ptr = start;

for (i = 0; i < (length); i++)
{
  val = *ptr;
  printf("bit value = %4x\n", val);
  ptr++;
}

}
