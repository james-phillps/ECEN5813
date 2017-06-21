
#include <stdio.h>
#include <stdint.h>
//#include "conversion.h"
#include "project1.h"


void main()
{
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
* @Jordan Wachs
* @06-18-17
*/

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base) {

	int32_t integer = 0;
	return integer;

}


/*!
* @Big endian to Little Endian converter
* Converts array from big endian to little endian representation.  Returns error if conversion fails
* @Jordan Wachs
* @06-18-17
*/

int8_t big_to_little32(uint32_t * data, uint32_t length) {

	const char * ErrFunc() {
	const char *ErrFlag = "Error in big_to_little32";
	return ErrFlag;
	}



}


/*!
* @Little endian to Big Endian converter
* Converts array from little endian to big endian representation.  Returns error if conversion fails
* @Jordan Wachs
* @06-18-17
*/

int8_t little_to_big32(uint32_t * data, uint32_t length) {

	const char * ErrFunc() {
	const char *ErrFlag = "Error in little_to_big32";
	return ErrFlag;
	}

}


}