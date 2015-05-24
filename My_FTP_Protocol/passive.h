/*
 * passive.h
 *
 *  Created on: 2015-05-24
 *      Author: sajjad
 */

#ifndef PASSIVE_H_
#define PASSIVE_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

char recv_pd_info (char* buffer,char* tIP, int data_port);



#endif /* PASSIVE_H_ */
