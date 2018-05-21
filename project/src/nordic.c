/**
 * @file nordic.c
 * @brief Nordic functions
 * Contains routines to configure and use the nordic chip
 * @author James Phillips
 * @date 8/7/2017
 */

#include "../include/common/nordic.h"

uint8_t nrf_read_register(uint8_t reg){
  uint8_t cmd[2] = {0x00, 0xFF};
  uint8_t reply = 0;
  cmd[0] |= (0x1F&reg);
  SPI_send_packet(cmd, 2);
  reply = SPI_read_byte();
  reply = SPI_read_byte();

  return reply;
}

void nrf_write_register(uint8_t reg, uint8_t value){
    uint8_t cmd[2] = {0x20, 0x00};
    cmd[0] |= (0x1F&reg);
    cmd[1] = value;
    SPI_send_packet(cmd, 2);

  return;
}

uint8_t nrf_read_status(void){
  uint8_t cmd = 0xFF;
  uint8_t reply = 0;
  SPI_write_byte(cmd);
  reply = SPI_read_byte();
  return reply;
}

void nrf_write_config(uint8_t config){
  nrf_write_register(CONFIG_ADDR, config);
  return;
}

uint8_t nrf_read_config(void){
  return nrf_read_register(CONFIG_ADDR);
}

uint8_t nrf_read_rf_setup(void){
  return nrf_read_register(RF_SETUP_ADDR);
}

void nrf_write_rf_setup(uint8_t config){
  nrf_write_register(RF_SETUP_ADDR, config);
  return;
}

uint8_t nrf_read_rf_ch(void){
  return nrf_read_register(RF_CH_ADDR);
}

void nrf_write_rf_ch(uint8_t channel){
  nrf_write_register(RF_CH_ADDR, channel);
  return;
}

void nrf_read_TX_ADDR(uint8_t * address){
  uint8_t cmd[6] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  uint8_t i = 0;
  uint8_t status = 0;

  cmd[0] |= (0x1F&TX_ADDR);
  SPI_send_packet(cmd, 6);
  status = SPI0_D;
  for (i = 0; i < 5; i++){
    *(address + i) = SPI0_D;
  }

  return;
}

void nrf_write_TX_ADDR(uint8_t * tx_addr){
  uint8_t cmd[6] = {0x20, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t i = 0;

  cmd[0] |= (0x1F&TX_ADDR);
  for(i = 1; i < 6; i++){
    cmd[i] = *(tx_addr + i - 1);
  }
  SPI_send_packet(cmd, 6);

  return;
}

uint8_t nrf_read_fifo_status(void){
  return nrf_read_register(FIFO_STATUS_ADDR);
}

void nrf_flush_rx_fifo(void){
  SPI_write_byte(FLUSH_RX);
  return;
}

void nrf_flush_tx_fifo(void){
  SPI_write_byte(FLUSH_TX);
  return;
}
