#include <stdio.h>
#include "../include/common/circbuf.h"

CB_t *buf_struct = NULL;
uint16_t length = 256;
//Stats variables
uint32_t alpha = 0;
uint32_t numeral = 0;
uint32_t punct = 0;
uint32_t misc = 0;

void project2(void){
  uint8_t data = 0;
  //uint8_t data_out = 0;
  //uint8_t *out_ptr = &data_out;
  uint8_t end = 0;
  uint8_t breakchar = 0x21;



  //Initialize buffer
  CB_init(&buf_struct, length);
  printf("Start typing...\n");

  while(end == 0){
    scanf("%c", &data);
    if(data == breakchar){
      break;
    }
    else if(data < 0x20){
      misc++;
    }
    else if(data < 0x30){
      punct++;
    }
    else if(data < 0x3A){
      numeral++;
    }
    else if(data < 0x41){
      punct++;
    }
    else if(data < 0x5B){
      alpha++;
    }
    else if(data < 0x61){
      punct++;
    }
    else if(data < 0x7B){
      alpha++;
    }
    else if(data < 0x7E){
      punct++;
    }
    else{
      misc++;
    }
    CB_buffer_add_item(buf_struct, data);
  }

  /*printf("You Entered...\n");
  while(buf_struct->count != 0){
    CB_buffer_remove_item(buf_struct, out_ptr);
    printf("%c", *out_ptr);
  }
  printf("\n");*/

    return;
}

void dump_statistics(void){
  printf("Number of alphabetics characters: %d\n", alpha);
  printf("Number of numerical characters: %d\n", numeral);
  printf("Number of punctuation characters: %d\n", punct);
  printf("Number of miscellaneous characters: %d\n", misc);
  return;
}
