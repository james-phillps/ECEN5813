/**
 * @file logger_queue.h
 * @brief Logger queue routines
 * Functions for the non-blocking logger
 * @author James Phillips
 * @date 8/7/2017
 */

#include "../kl25z/MKL25Z4.h"
#include "./uart.h"

typedef enum {
  LOGGER_INITIALIZED = 0x01,
  GPIO_INITIALIZED = 0x02,
  SYSTEM_INITIALIZED = 0x03,
  SYSTEM_HALTED = 0x0F,
  INFO = 0x10,
  WARNING = 0x1D,
  ERROR = 0x1F,
  PROFILING_STARTED = 0x21,
  PROFILNG_RESULT = 0x22,
  PROFILING_COMPLETED = 0x23,
  DATA_RECEIVED = 0x31,
  DATA_ANALYSIS_STARTED = 0x32,
  DATA_ALPHA_COUNT = 0x33,
  DATA_NUMERIC_COUNT = 0x34,
  DATA_PUNCTUATION_COUNT = 0x35,
  DATA_MISC_COUNT = 0x36,
  DATA_ANAYLSIS_COMPLETED = 0x3A,
  HEARTBEAT = 0xAA
}log_event_t;

typedef struct{


} CB_Log_t;

void RTC_Init(void);

void log_item_kl25z(log_event_t event);

void RTC_Seconds_IRQHandler(void);
