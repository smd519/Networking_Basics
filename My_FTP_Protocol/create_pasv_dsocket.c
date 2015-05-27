/*
j * create_pasv_dsocket.c
 *
 *  Created on: 2015-05-25
 *      Author: sajjad
 */
#include <create_pasv_dsocket.h>

char create_pasv_dsocket (int sockfd) {
	char pasv_message[6]={0};
    char status=create_command ("passive", NULL, pasv_message);
	if (status!=0) {
		return -1;
		terminate_socket (sockfd);
	}
	int message_length=strlen(pasv_message);
	status=send_command(sockfd,pasv_message, message_length);
	if (status!=0) {
		return -1;
		terminate_socket (sockfd);
	}

	char buffer[128]={0};
	status=recv_pasv_info(sockfd,buffer);
	if (status!=0) {
		return -1;
		terminate_socket (sockfd);
	}

	char tIP[16]={0};
	char data_port[6]={0};
	status=extract_socket_info(buffer,tIP,data_port);
	if (status!=0) {
		return -1;
		terminate_socket (sockfd);
	}

	int data_sockfd=create_socket (tIP, data_port);
	if (data_sockfd==-1) {
		return -1;
	}
	return data_sockfd;
}

char recv_pasv_info(int sockfd, char *buffer) {
	//Receiving msg response
	char status=0;
	status = recv(sockfd, (void *)buffer,127,0);
	if (status==0) {
		printf ("Connection terminated.\n");
		return -1;
	}
	if (status==-1){
		perror("Error: Reading RESPONSE failed\n");
		return -1;
	}
	char temp[4]={0};
	strncpy(temp,buffer,3);
	if (!strstr(temp,"227")) {
		perror("Error: Server does not permit making data connection.\n");
		return -1;
	}
	return 0;
}

