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


uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base) {
	int32_t j = 0;
	uint32_t mult = base;
	int32_t temp = 0;
	uint32_t asc_upnib = 0x30;
	int32_t standin = 0;
	int32_t test = 0;
	int32_t mod = 0;

	//Check for null pointer
	if (ptr == NULL){
		return 0;
	}


	if (data < 0)
	{
		temp = (~data) + 1;
	}
	else
	{
		temp = data;
	}
	test = temp/mult;
	while (test >= 1)
	{
		mod = temp%mult;
		standin = mod/(mult/base);
		if(standin > 0x09)
		{
			asc_upnib = 0x40;
			standin = standin - 0x09;
		}
		*(ptr + j) = (uint8_t)(standin) + asc_upnib;
		temp = temp - mod;
		mult = mult*base;
		test = temp/mult;
		j++;
	}

	mod = temp%mult;
	*(ptr + j) = (uint8_t)(mod/(mult/base)) + 0x30;
	if (data < 0)
	{
		*(ptr + ++j) = 0x2D;
	}
	*(ptr + ++j) = 0x00;

	my_reverse(ptr, j);

	return j;


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
    //digits++;
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
