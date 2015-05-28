/*
 *FTP_Client.c
 *FTP for Client Side. It is even compatible with standard FTP server.
 *You can just run this program, and connect with any standard FTP server.
 *  Created on: 2015-05-21
 *      Author: sajjad
 */
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
#include <create_pasv_dsocket.h>

#define CTRLPORT "21"
#define DATAPORT "20"

int main(int argc, char *argv[]) {
	if (argc==1) {
		printf ("please enter the server IP address\n");
	}
	char tIP[16]={0};
	strcpy(tIP, argv[1]);
	int sockfd=0;
	sockfd=create_socket(tIP, CTRLPORT);
	if (sockfd==-1) {
		return -1;
	}

	char status=ftp_authenticat(sockfd);
	if (status!=0) {
		return -1;
		terminate_socket (sockfd);
	}

	char flag=1;
	char user_input[64];
	char std_message[70];
	//create_data_socket (sockfd);
	while (flag){
		printf("ftp> ");
		memset(&user_input,0,64);
		fgets(user_input, sizeof(user_input), stdin);
		printf("User input:%s\n",user_input);
		if (strcmp(user_input, "\n")==0) {
			continue;
		}

		memset(&std_message,0,70);
		int command_status=create_command(user_input, NULL,std_message);
		if (command_status!=0 && command_status!=2 && command_status!=3) {
			return -1;
			terminate_socket (sockfd);
		}
		if (command_status==2) {///exit,bye,quit
			flag=0;
		}

		int data_sockfd=0;
		if (command_status==3) {///if the command needs a data socket
			data_sockfd=create_pasv_dsocket(sockfd);
			if (data_sockfd==-1) {
				return -1;
			}
		}

		status=send_command(sockfd,std_message, strlen(std_message));
		if (status!=0) {
			return -1;
			terminate_socket (sockfd);
		}

		if (command_status==3) {///if the command needs a data socket
			status=recv_response(data_sockfd);
			if (data_sockfd==-1) {
				return -1;
			}
			status=recv_response(sockfd);
			if (status!=0) {
				return -1;
				terminate_socket (sockfd);
			}
		}

		status=recv_response(sockfd);
		if (status!=0) {
			return -1;
			terminate_socket (sockfd);
		}

		if (command_status==3) {///Close Data Socket after use
			terminate_socket (data_sockfd);
		}

	}
	terminate_socket (sockfd);
	return 0;
}
