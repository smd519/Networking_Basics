/*
 * create_command.h
 *
 *  Created on: 2015-05-24
 *      Author: sajjad
 */

#ifndef CREATE_COMMAND_H_
#define CREATE_COMMAND_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <basics.h>

char create_command (char* user_input, char* arg, char* std_message);
char send_command(int sockfd,char* fttp_message, int message_length);

#endif /* CREATE_COMMAND_H_ */
