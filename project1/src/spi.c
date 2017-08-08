/**
 * @file spi.c
 * @brief SPI functions
 * Contains routines to configure and use the UART0
 * @author James Phillips
 * @date 7/11/2017
 */

#include "../include/common/spi.h"
#define SS_HI GPIOD_PSOR |= 0x00000020;
#define SS_LO GPIOD_PCOR |= 0x00000020;

 void SPI_init(void){

   //Turn on clocks to SPI0
   SIM_SCGC4 |= SIM_SCGC4_SPI0(1);

   //TUrn on clock to Port D
   SIM_SCGC5 |= SIM_SCGC5_PORTD(1); //Clock ON
   //PORTD_PCR0 |= PORT_PCR_MUX(1);   //Configure for GPIO
   PORTD_PCR1 |= PORT_PCR_MUX(2);   //SPI0 CLK
   PORTD_PCR2 |= PORT_PCR_MUX(2);   //SPI0 MISO
   PORTD_PCR3 |= PORT_PCR_MUX(2);   //SPI0 MOSI

   //Set pin direction
   PORTD_PCR5 |= PORT_PCR_MUX(1);   //Chip Select, GPIO
   GPIOD_PDDR |= 0x00000020;  //Set pin as output
   GPIOD_PSOR |= 0x00000020;  //Set to logic high


   //Select SPI0 as Master
   SPI0_C1 |= SPI_C1_MSTR(1); //Set SPI as master

   //Configure slave Select
   SPI0_C1 |= SPI_C1_SSOE(1); //SPI0 chip select is GPIO

   //Clock idles low, edge select
   SPI0_C1 &= ~SPI_C1_CPOL(1);
   SPI0_C1 &= ~SPI_C1_CPHA(1);

   //Configure master mode-fault
   SPI0_C2 |= SPI_C2_MODFEN(0); //SPI0 chip select is GPIO

   //Configure Baud Rate Prescalers
   SPI0_BR |= SPI_BR_SPPR(4) | SPI_BR_SPR(4);

   //Enable the SPI
   SPI0_C1 |= SPI_C1_SPE(1);

   return;
 }

 void SPI_read_byte(uint8_t byte){
   uint8_t data = 0;
   SS_LO
   while((SPI0_S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);
   SPI0_D = byte;
   while((SPI0_S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);
   for(int i = 0; i < 250; i++){}
   SS_HI

   return;
 }

void SPI_write_byte(uint8_t byte){
  SS_LO
  while((SPI0_S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK); //Wait until TX buffer is empty
  SPI0_D = byte;
  while((SPI0_S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);
  for(int i = 0; i < 250; i++){}
  SS_HI

  return;
}

void SPI_send_packet(uint8_t *p, size_t length){
  uint16_t i = 0;

  SS_LO
  for(i = 0; i < length; i++){
    while((SPI0_S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);
    SPI0_D = *(p + i);
  }
  while((SPI0_S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);

  for(i = 0; i < 300; i++){}
  SS_HI

  return;
}

void SPI_flush(void){
  uint8_t data = 0;
  while(CB_is_empty(spi_buf_tx) != BuffEmpty){
    CB_buffer_remove_item(spi_buf_tx, &data);
    SPI_write_byte(data);
  }
  return;
}
