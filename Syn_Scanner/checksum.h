/*
 * checksum.h
 * Modified version of below code:
 * Copyright (c) 1982, 1986, 1988, 1990, 1993, 1994
 * The Regents of the University of California.  All rights reserved.
 *
 *  Created on: 2015-05-29
 *      Author: sajjad
 */

#ifndef CHECKSUM_H_
#define CHECKSUM_H_

#include <netinet/ip.h>

u_int16_t checksum(char *ptr,int length);


#endif /* CHECKSUM_H_ */
