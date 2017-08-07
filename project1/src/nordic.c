/**
 * @file nordic.c
 * @brief Nordic functions
 * Contains routines to configure and use the nordic chip
 * @author James Phillips
 * @date 8/7/2017
 */

#include "../include/common/nordic.h"

uint8_t nrf_read_register(uint8_t reg){
  uint8_t cmd = 0;
  uint8_t reply = 0;
  cmd |= (0x1F&reg);
  SPI_read_byte(cmd);
  reply = SPI0_D;

  return reply;
}

void nrf_write_register(uint8_t reg, uint8_t value){
  uint8_t cmd = 0x20;
  cmd |= (0x1F&reg);
  return;
}

uint8_t nrf_read_status(void){
  uint8_t cmd = 0xFF;
  uint8_t reply = 0;
  SPI_read_byte(cmd);
  return reply = SPI0_D;
}

void nrf_write_config(uint8_t config){
  return;
}

uint8_t nrf_read_config(void){
  return 0;
}

uint8_t nrf_read_rf_setup(void){
  return 0;
}

void nrf_write_rf_setup(uint8_t config){
  return;
}

uint8_t nrf_read_rf_ch(void){
  return 0;
}

void nrf_write_rf_ch(uint8_t channel){
  return;
}

void nrf_read_TX_ADDR(uint8_t * address){
  return;
}

void nrf_write_TX_ADDR(uint8_t * tx_addr){
  return;
}

uint8_t nrf_read_fifo_status(void){
  return 0;
}

void nrf_flush_rx_fifo(void){
  return;
}

void nrf_flush_tx_fifo(void){
  return;
}
