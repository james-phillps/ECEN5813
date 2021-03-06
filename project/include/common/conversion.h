/**
 * @file conversion.h
 * @brief Function prototypes for conversion.c
 * Contains function prototypes for data conversion routines
 * @author James Phillips
 * @date 6/21/2017
 */
#include <stdint.h>
#include "./memory.h"
#include <stdlib.h>

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base);
int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base);
int8_t big_to_little32(uint32_t * data, uint32_t length);
int8_t little_to_big32(uint32_t * data, uint32_t length);
