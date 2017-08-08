/**
 * @file spi.h
 * @brief SPI functions
 * Contains routines to configure and use the UART0
 * @author James Phillips
 * @date 7/11/2017
 */
#ifndef SPI_H
#define SPI_H

#include "../kl25z/MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>
#include "./timer.h"
#include "./circbuf.h"

extern CB_t *spi_buf_tx;

void SPI_init(void);

void SPI_read_byte(uint8_t byte);

void SPI_write_byte(uint8_t byte);

void SPI_send_packet(uint8_t *p, size_t length);

void SPI_flush(void);

#endif
