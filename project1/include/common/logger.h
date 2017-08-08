/**
 * @file logger.c
 * @brief Logger functions
 * Contains routines to configure and use the logger
 * @author James Phillips
 * @date 7/11/2017
 */

#include <stdint.h>
#include <stdlib.h>
#include "./circbuf.h"

#ifdef KL25Z
#include "./uart.h"
#include "./conversion.h"
#define LOG_RAW_STRING(string_ptr) log_string_kl25z(string_ptr)
#define LOG_RAW_INTEGER(integer) log_integer_kl25z(integer)
#define LOG_RAW_FLUSH() log_flush_kl25z()
#endif

#ifdef BBB
#include <stdio.h>
#define LOG_RAW_STRING(string_ptr) log_string_BBB(string_ptr)
#define LOG_RAW_INTEGER(integer) log_integer_BBB(integer)
#define LOG_RAW_FLUSH() log_flush_BBB()
#endif

void log_data(uint8_t * p, size_t length);

void log_flush_kl25z(void);

void log_string_kl25z(uint8_t *string);

void log_string_BBB(uint8_t *string);

void log_integer_kl25z(int32_t integer);

void log_integer_BBB(int32_t integer);

void log_flush_BBB(void);
