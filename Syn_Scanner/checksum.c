/*
 * checksum.c
 *
 *  Created on: 2015-05-29
 *      Author: sajjad
 */

#include <checksum.h>

u_int16_t checksum(char *ptr,int length) {
	unsigned short *itr=(unsigned short*)ptr;
	long int sum=0;
	while(length>1) {
		sum= sum + *itr;
		itr= itr+1;
	    length=length-2;
	}
	unsigned short last_byte;
	if(1==length) {
		last_byte=0;
	   *( (unsigned char*)&last_byte )= (*(unsigned char*)itr);
	   sum=sum+last_byte;
	}

	sum = (sum & 0xffff) + (sum>>16);
	sum = sum + (sum>>16);
	sum=~sum;

	u_int16_t result;
	result=(u_int16_t)sum;
	return result;
}

