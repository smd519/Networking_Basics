/*
 * create_rawscoket.h
 *
 *  Created on: 2015-05-30
 *      Author: sajjad
 */

#ifndef CREATE_RAWSCOKET_H_
#define CREATE_RAWSCOKET_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>

int create_rawscoket(void);

#endif /* CREATE_RAWSCOKET_H_ */
