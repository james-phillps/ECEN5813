/**
 * @file conversion.c
 * @brief Data conversion routines
 * Routines to convert data types and endianness
 * @author James Phillips and Jordan Wachs
 * @date 6/18/2017
 */

/*!
* @integer to ASCII converter
* Converts a standard (signed) integer type to ASCII string and saves to a memory location specified with an input pointer.  Can support bases 2 to 16 integer inputs.  String ends with a null terminate.
* @Jordan Wachs
* @06-18-17
*/

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base) {

	uint8_t length=0;
	return length;
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

	/*
	const char * ErrFunc() {
	const char *ErrFlag = "Error in big_to_little32";
	return ErrFlag;
}
*/
uint8_t temp_loc = 0; /* temporary location to store byte*/
uint8_t i = 0;

for (i = 0; i < length/2; i++)
{
	temp_loc = *(data + i); /* stores MSB in temp_loc */
	*(data + i) = *((uint8_t*)data +i); /* writes LSB into original MSB location*/
	*(data + i) = temp_loc; /*writes MSB into LSB location*/
}

if (*data == temp_loc) /*If unchanged data (temp_loc) is the same as the changed data, then the endian flip didn't work. */
{
printf("Error in little_to_big32. ");

}

else
{
return 0;
}


}


/*!
* @Little endian to Big Endian converter
* Converts array from little endian to big endian representation.  Returns error if conversion fails
* @James Phillips
* @06-18-17
*/

int8_t little_to_big32(uint32_t * data, uint32_t length) {

	uint32_t temp = 0;

  for (int i = 0; i < (length/2); i++)
  {
    temp = *(data + i);
    *(data + i) = *(data + length - 1 - i);
    *(data + length - 1 - i) = temp;
  }

	return 0;


}
