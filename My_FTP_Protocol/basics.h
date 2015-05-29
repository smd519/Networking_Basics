/*
 * basics.h
 * basic functions for setting up a socket connection including:
 * 	-create the socket
 * 	- Authentication
 * 	- closing the socket
 *  Created on: 2015-05-24
 *      Author: sajjad
 */
#ifndef BASICS_H_
#define BASICS_H_
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

#include <create_command.h>
#include <recv_response.h>

char create_socket (char* tIP, char* port);
char ftp_authenticat (int sockfd) ;
char terminate_socket (int sockfd);


#endif /* BASICS_H_ */
