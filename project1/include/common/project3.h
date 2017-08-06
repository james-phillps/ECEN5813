#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "./memory.h"

#ifdef KL25Z
#include "./timer.h"
#include "./uart.h"
#include "./conversion.h"
#endif

#ifdef BBB
#include <time.h>
#include <stdio.h>
#define BBBCLK_PER_SEC  (1000000000)
#endif

void project3(void);

void profile_kl25z(void);

void profile_BBB(void);

double memtest_BBB_stdlib(uint16_t length);

double memtest_BBB_mymem(uint16_t length);

double memset_BBB_stdlib(uint16_t length);

double memset_BBB_mymem(uint16_t length);

uint32_t memtest_kl25z_stdlib(uint16_t length);

uint32_t memtest_kl25z_mymem(uint16_t length);

uint32_t memtest_kl25z_dma(uint16_t length, uint8_t tran_size);

uint32_t memset_kl25z_stdlib(uint16_t length);

uint32_t memset_kl25z_mymem(uint16_t length);

uint32_t memset_kl25z_dma(uint16_t length, uint8_t tran_size);
