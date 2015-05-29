/*
 * creat_pasv_dsocket.h
 * here we create a data socket. To do so, we need to communicate with server and ask for
 * data socket information, including IP and port.These data will be sent to the control socket
 * but we don't need to print them on screen. Data socket should be transparent to the user.
 *  Created on: 2015-05-25
 *      Author: sajjad
 */

#ifndef CREAT_PASV_DSOCKET_H_
#define CREAT_PASV_DSOCKET_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

#include <basics.h>
#include <passive.h>
#include <recv_response.h>
#include <create_command.h>

char create_pasv_dsocket (int sockfd);
char recv_pasv_info(int sockfd, char *buffer);


#endif /* CREAT_PASV_DSOCKET_H_ */
