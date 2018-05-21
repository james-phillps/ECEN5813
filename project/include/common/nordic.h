/**
 * @file nordic.h
 * @brief Nordic functions
 * Contains routines to configure and use the nordic chip
 * @author James Phillips
 * @date 8/7/2017
 */

#include "./spi.h"
#include <stdint.h>

#define CONFIG_ADDR 0x00
#define EN_AA_ADDR  0x01
#define EN_RX_ADDR  0x02
#define SETUP_AW_ADDR 0x03
#define SETUP_RETR_ADDR 0x04
#define RF_CH_ADDR  0x05
#define RF_SETUP_ADDR 0x06
#define STATUS_ADDR 0x07
#define OBSERVE_TX_ADDR 0x08
#define RPD_ADDR  0x09
#define RX_P0_ADDR  0x0A
#define RX_P1_ADDR  0x0B
#define RX_P2_ADDR  0x0C
#define RX_P3_ADDR  0x0D
#define RX_P4_ADDR  0x0E
#define RX_P5_ADDR  0x0F
#define TX_ADDR 0x10
#define RX_PW_P0_ADDR 0x11
#define RX_PW_P1_ADDR  0x12
#define RX_PW_P2_ADDR 0x13
#define RX_PW_P3_ADDR 0x14
#define RX_PW_P4_ADDR 0x15
#define RX_PW_P5_ADDR 0x16
#define FIFO_STATUS_ADDR  0x17
#define DYNPD_ADDR  0x1C
#define FEATURE_ADDR 0x1D

#define FLUSH_TX 0xE1
#define FLUSH_RX 0xE2


uint8_t nrf_read_register(uint8_t reg);

void nrf_write_register(uint8_t reg, uint8_t value);

uint8_t nrf_read_status(void);

void nrf_write_config(uint8_t config);

uint8_t nrf_read_config(void);

uint8_t nrf_read_rf_setup(void);

void nrf_write_rf_setup(uint8_t config);

uint8_t nrf_read_rf_ch(void);

void nrf_write_rf_ch(uint8_t channel);

void nrf_read_TX_ADDR(uint8_t * address);

void nrf_write_TX_ADDR(uint8_t * tx_addr);

uint8_t nrf_read_fifo_status(void);

void nrf_flush_tx_fifo(void);

void nrf_flush_rx_fifo(void);
