/*
 * ip_header.h
 *  Created on: 2015-05-29
 *      Author: sajjad
 */

#ifndef IP_HEADER_H_
#define IP_HEADER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <checksum.h>


char create_iph(char * tIP,struct iphdr *ip_header);

#endif /* IP_HEADER_H_ */
