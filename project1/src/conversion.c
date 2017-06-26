/**
 * @file conversion.c
 * @brief Data conversion routines
 * Routines to convert data types and endianness
 * @author James Phillips and Jordan Wachs
 * @date 6/18/2017
 */

/*!
* @integer to ASCII converter
* Converts a standard (signed) integer type to ASCII string and saves to a
memory location specified with an input pointer.  Can support bases 2 to 16
integer outputs.  String ends with a null terminate.
* @Jordan Wachs
* @06-18-17
*/

#include "../include/common/conversion.h"
#include <stdlib.h>

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base) {

	/* Input data is in hex.  Convert this to the specified base and reference
	ASCII table to store as ascii characters */

	/* if value:0-9, upper nibble = 0b0011, lower nibble = value 0b0000 - 0b1001

	if value: a-f, upper nibble = 0b0110 , lower nibble = value minus 0b1000
		if hex value :0-9*/

		/* First convert from base n to base 10*/

		uint32_t i = 0;
		uint32_t divisor;
		uint32_t array[16];
	  uint32_t dec;
		int8_t *ptr2;
		uint32_t nib1;
		uint32_t nib2;

		/* convert hex to decimal*/

		ptr2 = ptr++;

		nib1 = *ptr;
		nib2 = *ptr2;

		dec = 16*nib1 + nib2;

		/* Takes decimal and converts to arbitrary base 2-16 */
		divisor = base*base*base*base*base*base*base; /* There has to be a better way w/0 math.h? */
		for (i = 7; i>=0; i--){

			array[i] = dec/divisor;
			dec = dec%divisor;

			divisor = divisor/base;
		}


}


/*!
* @ASCII to integer converter
* Converts ASCII character set to int32_t data.  Signed values can be input and bases 2 to 16 are supported
* @James Phillips
* @06-22-17
*/

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base) {
	int32_t integer32 = 0;
  uint32_t mult = 1;
  int8_t i =0;
  int8_t stop = -1;
  uint8_t upnib = 0;

  if (*ptr == 0x2D)
  {
    stop = 0;
    digits++;
  }

  for (i = (digits - 1); i > stop; i--)
  {
    upnib = (*(ptr + i)&0xF0);
    if ((upnib == 0x40) || (upnib == 0x60))
    {
      integer32 += ((*(ptr + i)&0x0F)+0x09)*mult;
      mult = mult*base;
    }
    else
    {
      integer32 += (*(ptr + i)&0x0F)*mult;
      mult = mult*base;
    }
  }

  if (*ptr == 0x2D)
  {
    integer32 = integer32*-1;
  }


  return integer32;

}


/*!
* @Big endian to Little Endian converter
* Converts array from big endian to little endian representation.  Returns error if conversion fails
* @Jordan Wachs
* @06-18-17
*/

int8_t big_to_little32(uint32_t * data, uint32_t length) {

	if(data == NULL)
	{
		return 1;
	}

	uint32_t temp = 0; /* create space to store data as each new word is read*/
	uint32_t empty_word = 0;
	uint32_t mask3 = 0xFF000000;
	uint32_t mask2 = 0x00FF0000;
	uint32_t mask1 = 0x0000FF00;
	uint32_t mask0 = 0x000000FF;

  for (int i = 0; i < length; i++) /* cycle through amount of data specified in "length" */
  {
    temp = *(data + i);
		empty_word = (temp&mask3)>>24; /* mapping shifted data from memory location into empty word */
		empty_word += (temp&mask0)<<24;
		empty_word += (temp&mask2)>>8;
		empty_word += (temp&mask1)<<8;
		*(data + i) = empty_word;  /* Saving flipped (endian) word to memory location */
  }

	return 0;

}


/*!
* @Little endian to Big Endian converter
* Converts array from little endian to big endian representation.  Returns error if conversion fails
* @James Phillips
* @06-18-17
*/

int8_t little_to_big32(uint32_t * data, uint32_t length) {
	if(data == NULL)
	{
		return 1;
	}

	uint32_t temp = 0;
	uint32_t empty_word = 0;
	uint32_t mask3 = 0xFF000000;
	uint32_t mask2 = 0x00FF0000;
	uint32_t mask1 = 0x0000FF00;
	uint32_t mask0 = 0x000000FF;

  for (int i = 0; i < length; i++)
  {
    temp = *(data + i);
		empty_word = (temp&mask3)>>24;
		empty_word += (temp&mask0)<<24;
		empty_word += (temp&mask2)>>8;
		empty_word += (temp&mask1)<<8;
		*(data + i) = empty_word;
  }

	return 0;


}
