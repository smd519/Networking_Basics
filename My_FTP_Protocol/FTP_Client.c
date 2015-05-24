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

#define CTRLPORT "21"
#define DATAPORT "20"

int main(int argc, char *argv[]) {
	if (argc==1) {
		// If No IP address is entered, just lookuP the IP-address of the machine
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
		memset(&std_message,0,70);

		fgets(user_input, sizeof(user_input), stdin);
		printf("User input:%s\n",user_input);

		status=create_command(user_input, NULL,std_message);
		if (status!=0 && status!=2) {
			return -1;
			terminate_socket (sockfd);
		}
		if (status==2) {
			flag=0;
		}

		status=send_command(sockfd,std_message, strlen(std_message));
		if (status!=0) {
			return -1;
			terminate_socket (sockfd);
		}

		status=recv_response(sockfd);
		if (status!=0) {
			return -1;
			terminate_socket (sockfd);
		}

	}
	terminate_socket (sockfd);
	return 0;
}
