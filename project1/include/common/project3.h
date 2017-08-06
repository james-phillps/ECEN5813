#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "./timer.h"
#include "./uart.h"
#include "./memory.h"
#include "./conversion.h"

void project3(void);

void memtest_OS(void);

uint32_t memtest_kl25z_stdlib(uint16_t length);

uint32_t memtest_kl25z_mymem(uint16_t length);

uint32_t memtest_kl25z_dma(uint16_t length, uint8_t tran_size);

uint32_t memset_kl25z_stdlib(uint16_t length);

uint32_t memset_kl25z_mymem(uint16_t length);

uint32_t memset_kl25z_dma(uint16_t length, uint8_t tran_size);
