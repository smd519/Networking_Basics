/*
 * tcp_header.h
 *
 *  Created on: 2015-05-30
 *      Author: sajjad
 */

#ifndef TCP_HEADER_H_
#define TCP_HEADER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

char init_tcph(struct tcphdr *tcp_header);


#endif /* TCP_HEADER_H_ */
