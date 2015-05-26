/*
 * creat_pasv_dsocket.h
 *
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
#include <recv_ctrl_socket.h>
#include <create_command.h>

char create_pasv_dsocket (int sockfd);
char recv_pasv_info(int sockfd, char *buffer);


#endif /* CREAT_PASV_DSOCKET_H_ */
