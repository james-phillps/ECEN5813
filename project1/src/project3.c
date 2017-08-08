#include "../include/common/project3.h"





void project3(void){

  #ifdef KL25Z
  uint8_t data[6] = {0xAA, 0xBB, 0xCC, 0xDD, 0xFF, 0x55};
  uint8_t histr[7] = "Hello!";
  int32_t integer = 10000;

  //SPI_write_byte(0xAA);
  //log_data(data, 6);
  //LOG_RAW_FLUSH();

  //LOG_RAW_STRING(histr);
  //LOG_RAW_FLUSH();

  //LOG_RAW_INTEGER(integer);
  //LOG_RAW_FLUSH();
  profile_kl25z();
  test_nordic();
  #endif

  #ifdef BBB
    profile_BBB();
  #endif
}

void test_nordic(void){
  #ifdef KL25Z
  uint8_t addr_set[5] = {0xFF, 0xEE, 0xDD, 0xCC, 0xBB};
  uint8_t addr_read[5] = {0xFF, 0xEE, 0xDD, 0xCC, 0xBB};
  uint8_t reply = 0x00;
  uint8_t config_write = 0x0A;
  uint8_t rf_setup = 0x06;
  uint8_t rf_ch = 0xAA;
  uint8_t config_label[15] = "CONFIG Reply: ";
  uint8_t status_label[9] = "STATUS: ";
  uint8_t tx_addr_label[9] = "TX ADDR: ";
  uint8_t setup_label[10] = "RF_SETUP: ";
  uint8_t ch_label[7] = "RF CH: ";
  uint8_t fifo_label[13] = "FIFO STATUS: ";
  uint8_t value[32];
  uint8_t value_len = 0;
  uint8_t CRLF[2] = {0x0D, 0x0A};

  //Test config
  reply = nordic_test_config(config_write);
  value_len = my_itoa(reply, value, 10);
  UART_send_n(config_label, 15);
  UART_send_n(value, value_len);
  UART_send_n(CRLF, 2);

  reply = nordic_test_status();
  value_len = my_itoa(reply, value, 10);
  UART_send_n(status_label, 9);
  UART_send_n(value, value_len);
  UART_send_n(CRLF, 2);

  //nordic_test_TX_ADDR(addr_set);
  //reply = nordic_test_rf_setup(rf_setup);
  //reply = nordic_test_rf_ch(rf_ch);
  //reply = nordic_test_fifo_status();

  #endif
  return;
}

uint8_t nordic_test_config(uint8_t config){
  uint8_t config_reply = 0x00;

  nrf_write_config(config);
  config_reply = nrf_read_config();
  return config_reply;
}

uint8_t nordic_test_status(void){
  uint8_t status = 0;
  status = nrf_read_status();
  return status;
}

void nordic_test_TX_ADDR(uint8_t *addr){
  uint8_t addr_post[5];

  nrf_read_TX_ADDR(addr_post);
  nrf_write_TX_ADDR(addr);
  nrf_read_TX_ADDR(addr_post);


  return;
}

uint8_t nordic_test_rf_setup(uint8_t rf_setup){
  uint8_t setup = 0;
  setup = nrf_read_rf_setup();
  nrf_write_rf_setup(0x06);
  setup = nrf_read_rf_setup();

  return setup;
}

uint8_t nordic_test_rf_ch(uint8_t rf_ch){
  uint8_t rf_ch_reply = 0;
  rf_ch_reply = nrf_read_rf_ch();
  nrf_write_rf_ch(rf_ch);
  rf_ch_reply = nrf_read_rf_ch();
  return rf_ch_reply;
}

uint8_t nordic_test_fifo_status(void){
  uint8_t status = 0;
  status = nrf_read_fifo_status();
  return status;
}

void profile_kl25z(void){
  #ifdef KL25Z
  uint16_t len_array[4] = {10, 100, 1000, 5000};
  uint32_t time_array[4] = {0, 0, 0, 0};
  uint8_t i = 0;
  uint8_t strcycles[32];
  uint8_t cycles_len = 0;
  uint8_t CRLF[2] = {0x0D, 0x0A};
  uint8_t tran_size = 8;
  uint8_t label1[6] = "STDLIB";
  uint8_t label2[14] = "NON-DMA CUSTOM";
  uint8_t label3[10] = "DMA 1 BYTE";
  uint8_t label4[10] = "DMA 2 BYTE";
  uint8_t label5[10] = "DMA 4 BYTE";
  uint8_t label6[7] = " MEMSET";

  UART_send_n(label1, 6);
  UART_send_n(CRLF, 2);

  for (i = 0; i < 4; i++){
    time_array[i] = memtest_kl25z_stdlib(len_array[i]);
  }

  for (i = 0; i < 4; i++){
    cycles_len = my_itoa(time_array[i], strcycles, 10);
    UART_send_n(strcycles, cycles_len);
    UART_send_n(CRLF, 2);
  }

  UART_send_n(CRLF, 2);

  for (i = 0; i < 4; i++){
    time_array[i] = memtest_kl25z_mymem(len_array[i]);
  }

  UART_send_n(label2, 14);
  UART_send_n(CRLF, 2);
  for (i = 0; i < 4; i++){
    cycles_len = my_itoa(time_array[i], strcycles, 10);
    UART_send_n(strcycles, cycles_len);
    UART_send_n(CRLF, 2);
  }

  UART_send_n(CRLF, 2);

  UART_send_n(label3, 10);
  UART_send_n(CRLF, 2);
  for (i = 0; i < 4; i++){
    time_array[i] = memtest_kl25z_dma(len_array[i], tran_size);
  }

  for (i = 0; i < 4; i++){
    cycles_len = my_itoa(time_array[i], strcycles, 10);
    UART_send_n(strcycles, cycles_len);
    UART_send_n(CRLF, 2);
  }

  UART_send_n(CRLF, 2);
  UART_send_n(label4, 10);
  UART_send_n(CRLF, 2);
  tran_size = 16;
  for (i = 0; i < 4; i++){
    time_array[i] = memtest_kl25z_dma(len_array[i], tran_size);
  }

  for (i = 0; i < 4; i++){
    cycles_len = my_itoa(time_array[i], strcycles, 10);
    UART_send_n(strcycles, cycles_len);
    UART_send_n(CRLF, 2);
  }

  UART_send_n(CRLF, 2);
  UART_send_n(label5, 10);
  UART_send_n(CRLF, 2);
  tran_size = 32;
  for (i = 0; i < 4; i++){
    time_array[i] = memtest_kl25z_dma(len_array[i], tran_size);
  }

  for (i = 0; i < 4; i++){
    cycles_len = my_itoa(time_array[i], strcycles, 10);
    UART_send_n(strcycles, cycles_len);
    UART_send_n(CRLF, 2);
  }

  UART_send_n(label1, 6);
  UART_send_n(label6, 7);
  UART_send_n(CRLF, 2);

  for (i = 0; i < 4; i++){
    time_array[i] = memset_kl25z_stdlib(len_array[i]);
  }

  for (i = 0; i < 4; i++){
    cycles_len = my_itoa(time_array[i], strcycles, 10);
    UART_send_n(strcycles, cycles_len);
    UART_send_n(CRLF, 2);
  }

  UART_send_n(CRLF, 2);

  for (i = 0; i < 4; i++){
    time_array[i] = memset_kl25z_mymem(len_array[i]);
  }

  UART_send_n(label2, 14);
  UART_send_n(label6, 7);
  UART_send_n(CRLF, 2);
  for (i = 0; i < 4; i++){
    cycles_len = my_itoa(time_array[i], strcycles, 10);
    UART_send_n(strcycles, cycles_len);
    UART_send_n(CRLF, 2);
  }

  UART_send_n(CRLF, 2);

  UART_send_n(label3, 10);
  UART_send_n(label6, 7);
  UART_send_n(CRLF, 2);
  tran_size = 8;
  for (i = 0; i < 4; i++){
    time_array[i] = memset_kl25z_dma(len_array[i], tran_size);
  }

  for (i = 0; i < 4; i++){
    cycles_len = my_itoa(time_array[i], strcycles, 10);
    UART_send_n(strcycles, cycles_len);
    UART_send_n(CRLF, 2);
  }

  UART_send_n(CRLF, 2);
  UART_send_n(label4, 10);
  UART_send_n(label6, 7);
  UART_send_n(CRLF, 2);
  tran_size = 16;
  for (i = 0; i < 4; i++){
    time_array[i] = memset_kl25z_dma(len_array[i], tran_size);
  }

  for (i = 0; i < 4; i++){
    cycles_len = my_itoa(time_array[i], strcycles, 10);
    UART_send_n(strcycles, cycles_len);
    UART_send_n(CRLF, 2);
  }

  UART_send_n(CRLF, 2);
  UART_send_n(label5, 10);
  UART_send_n(label6, 7);
  UART_send_n(CRLF, 2);
  tran_size = 32;
  for (i = 0; i < 4; i++){
    time_array[i] = memset_kl25z_dma(len_array[i], tran_size);
  }

  for (i = 0; i < 4; i++){
    cycles_len = my_itoa(time_array[i], strcycles, 10);
    UART_send_n(strcycles, cycles_len);
    UART_send_n(CRLF, 2);
  }
  #endif
  return;
}

void profile_BBB(void){
  #ifdef BBB
  uint16_t len_array[4] = {10, 100, 1000, 5000};
  double time_array[4] = {0, 0, 0, 0};
  uint8_t i = 0;

  for(i = 0; i < 4; i++){
    time_array[i] = memtest_BBB_stdlib(len_array[i]);
  }

  for (i = 0; i < 4; i++){
    printf("BBB STD LIB MEMMOVE %d BYTES: %f\n", len_array[i], time_array[i]);
  }

  printf("\n");

  for(i = 0; i < 4; i++){
    time_array[i] = memtest_BBB_mymem(len_array[i]);
  }

  for (i = 0; i < 4; i++){
    printf("BBB CUSTOM MEMMOVE %d BYTES: %f\n", len_array[i], time_array[i]);
  }

  printf("\n");

  for(i = 0; i < 4; i++){
    time_array[i] = memset_BBB_stdlib(len_array[i]);
  }

  for (i = 0; i < 4; i++){
    printf("BBB STD LIB MEMSET %d BYTES: %f\n", len_array[i], time_array[i]);
  }

  printf("\n");

  for(i = 0; i < 4; i++){
    time_array[i] = memset_BBB_mymem(len_array[i]);
  }

  for (i = 0; i < 4; i++){
    printf("BBB CUSTOM MEMSET %d BYTES: %f\n", len_array[i], time_array[i]);
  }

  printf("\n");
  #endif
  return;
}

double memtest_BBB_stdlib(uint16_t length){

  double cpu_time = 0;
  #ifdef BBB

  clock_t start, end;

  uint8_t *bytessrc = NULL;
  uint8_t *bytesdst = NULL;
  uint16_t i = 0;

  bytessrc = (uint8_t *)malloc(sizeof(int)*length);
  bytesdst = (uint8_t *)malloc(sizeof(int)*length);

  //initialize memory
  for (i = 0; i < length; i++){
    *(bytessrc + i) = (uint8_t)i;
    *(bytesdst + i) = (uint8_t)(length - i);
  }

  //Time standard library memory move
  start = clock();
  memmove(bytesdst, bytessrc, length);
  end = clock();

  cpu_time = ((double)(end - start));


  //Disallocate memory
  free_words((uint32_t *)bytessrc);
  free_words((uint32_t *)bytesdst);
  #endif
  return cpu_time;
}

double memtest_BBB_mymem(uint16_t length){
  double cpu_time = 0;
  #ifdef BBB
  clock_t start, end;

  uint8_t *bytessrc = NULL;
  uint8_t *bytesdst = NULL;
  uint16_t i = 0;

  bytessrc = (uint8_t *)malloc(sizeof(int)*length);
  bytesdst = (uint8_t *)malloc(sizeof(int)*length);

  //initialize memory
  for (i = 0; i < length; i++){
    *(bytessrc + i) = (uint8_t)i;
    *(bytesdst + i) = (uint8_t)(length - i);
  }

  //Time standard library memory move
  start = clock();
  my_memmove(bytessrc, bytesdst, length);
  end = clock();

  cpu_time = ((double)(end - start));


  //Disallocate memory
  free_words((uint32_t *)bytessrc);
  free_words((uint32_t *)bytesdst);

  #endif
  return cpu_time;
}

double memset_BBB_stdlib(uint16_t length){
  double cpu_time = 0;
  #ifdef BBB
  clock_t start, end;
  uint8_t *bytessrc = NULL;
  uint16_t i = 0;

  bytessrc = (uint8_t *)malloc(length);

  //initialize memory
  for (i = 0; i < length; i++){
    *(bytessrc + i) = (uint8_t)i;
  }

  //Time standard library memory move
  start = clock();
  memset(bytessrc, 0xFF, length);
  end = clock();
  cpu_time = ((double)(end - start));


  //Disallocate memory
  free_words((uint32_t *)bytessrc);
  #endif
  return cpu_time;
}

double memset_BBB_mymem(uint16_t length){
  double cpu_time = 0;
  #ifdef BBB
  clock_t start, end;
  uint8_t *bytessrc = NULL;
  uint16_t i = 0;

  bytessrc = (uint8_t *)malloc(length);

  //initialize memory
  for (i = 0; i < length; i++){
    *(bytessrc + i) = (uint8_t)i;
  }

  //Time standard library memory move
  start = clock();
  my_memset(bytessrc, length, 0xFF);
  end = clock();
  cpu_time = ((double)(end - start));


  //Disallocate memory
  free_words((uint32_t *)bytessrc);
  #endif
  return cpu_time;
}

uint32_t memtest_kl25z_stdlib(uint16_t length){
  uint32_t cycles = 0;
  #ifdef KL25Z
  uint8_t *bytessrc = NULL;
  uint8_t *bytesdst = NULL;
  uint16_t i = 0;


  bytessrc = (uint8_t *)malloc(length);
  bytesdst = (uint8_t *)malloc(length);

  //initialize memory
  for (i = 0; i < length; i++){
    *(bytessrc + i) = (uint8_t)i;
    *(bytesdst + i) = (uint8_t)(length - i);
  }

  //Time standard library memory move
  systick_set();
  memmove(bytesdst, bytessrc, length);
  cycles  = systick_read();


  //Disallocate memory
  free_words((uint32_t *)bytessrc);
  free_words((uint32_t *)bytesdst);
  #endif

  return cycles;

}

uint32_t memtest_kl25z_mymem(uint16_t length){
  uint32_t cycles = 0;
  #ifdef KL25Z
  uint8_t *bytessrc = NULL;
  uint8_t *bytesdst = NULL;
  uint16_t i = 0;

  bytessrc = (uint8_t *)malloc(length);
  bytesdst = (uint8_t *)malloc(length);

  //initialize memory
  for (i = 0; i < length; i++){
    *(bytessrc + i) = (uint8_t)i;
    *(bytesdst + i) = (uint8_t)(length - i);
  }

  //Time standard library memory move
  systick_set();
  my_memmove(bytessrc, bytesdst, length);
  cycles = systick_read();


  //Disallocate memory
  free_words((uint32_t *)bytessrc);
  free_words((uint32_t *)bytesdst);
  #endif

  return cycles;
}

uint32_t memtest_kl25z_dma(uint16_t length, uint8_t tran_size){
  uint32_t cycles = 0;
  #ifdef KL25Z
  uint8_t *bytessrc = NULL;
  uint8_t *bytesdst = NULL;
  uint16_t i = 0;

  bytessrc = (uint8_t *)malloc(length);
  bytesdst = (uint8_t *)malloc(length);

  //initialize memory
  for (i = 0; i < length; i++){
    *(bytessrc + i) = (uint8_t)i;
    *(bytesdst + i) = (uint8_t)(length - i);
  }

  //Time standard library memory move
  systick_set();
  memmove_dma(bytessrc, bytesdst, length, tran_size);
  cycles = systick_read();


  //Disallocate memory
  free_words((uint32_t *)bytessrc);
  free_words((uint32_t *)bytesdst);
  #endif

  return cycles;
}

uint32_t memset_kl25z_stdlib(uint16_t length){
  uint32_t cycles = 0;
  #ifdef KL25Z
  uint8_t *bytessrc = NULL;
  uint16_t i = 0;

  bytessrc = (uint8_t *)malloc(length);

  //initialize memory
  for (i = 0; i < length; i++){
    *(bytessrc + i) = (uint8_t)i;
  }

  //Time standard library memory move
  systick_set();
  memset(bytessrc, 0xFF, length);
  cycles  = systick_read();


  //Disallocate memory
  free_words((uint32_t *)bytessrc);
  #endif
  return cycles;
}

uint32_t memset_kl25z_mymem(uint16_t length){
  uint32_t cycles = 0;
  #ifdef KL25Z
  uint8_t *bytessrc = NULL;
  uint16_t i = 0;

  bytessrc = (uint8_t *)malloc(length);

  //initialize memory
  for (i = 0; i < length; i++){
    *(bytessrc + i) = (uint8_t)i;
  }

  //Time standard library memory move
  systick_set();
  my_memset(bytessrc, length, 0xFF);
  cycles  = systick_read();


  //Disallocate memory
  free_words((uint32_t *)bytessrc);
  #endif
  return cycles;
}

uint32_t memset_kl25z_dma(uint16_t length, uint8_t tran_size){
  uint32_t cycles = 0;
  #ifdef KL25Z
  uint8_t *bytessrc = NULL;
  uint16_t i = 0;

  bytessrc = (uint8_t *)malloc(length);

  //initialize memory
  for (i = 0; i < length; i++){
    *(bytessrc + i) = (uint8_t)i;
  }

  //Time standard library memory move
  systick_set();
  memset_dma(bytessrc, length, 0xFF, tran_size);
  cycles  = systick_read();


  //Disallocate memory
  free_words((uint32_t *)bytessrc);

  #endif
  return cycles;
}
