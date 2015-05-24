/*
 * active.c
 *
 *  Created on: 2015-05-24
 *      Author: sajjad
 */

#include <active.h>

char create_ad_socket (int sockfd) {
	//creating an active data socket
	struct sockaddr_in ctrlsock;
	socklen_t len = sizeof(ctrlsock);
	if (getsockname(sockfd,(struct sockaddr*) &ctrlsock, &len) < 0) {
		perror("getsockname");
	    return -1;
	}
	char tIP[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(ctrlsock.sin_addr), tIP, INET_ADDRSTRLEN);
	short unsigned int port=ntohs(ctrlsock.sin_port);

	ctrlsock.sin_port=ctrlsock.sin_port-1;

	int data_sockfd=0;
	data_sockfd = socket(ctrlsock.sin_family, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("ERROR: data Socket could not be created!\n");
		return -1;
	}

	char status=bind(data_sockfd,(struct sockaddr*) &ctrlsock,len);
	if (status== -1) {
		close(sockfd);
		perror("server: bind");
		return -1;
	}

	status=listen(data_sockfd,4);
	if (status == -1) {
		perror("listen");
		return -1;
	}
	status = AD_to_server(sockfd, tIP, port);
	if (status == -1) {
		return -1;
	}
	printf("data socket ready and waiting for connections...\n");

	return data_sockfd;

}

char AD_to_server (int sockfd,char* tIP, short unsigned int port) {
	//connecting active data socket to server
	char temp1[4]={0};
	char * ptr=strstr(tIP, ".");
	strncpy(temp1,tIP, ptr-tIP);
	strcpy(tIP,ptr+1);

	char temp2[4]={0};
	ptr=strstr(tIP, ".");
	strncpy(temp2,tIP, ptr-tIP);
	strcpy(tIP,ptr+1);

	char temp3[4]={0};
	ptr=strstr(tIP, ".");
	strncpy(temp3,tIP, ptr-tIP);
	strcpy(tIP,ptr+1);

	char temp4[4]={0};
	strcpy(temp4,tIP);

	short unsigned int first_half=0x00FF;
	short unsigned int second_half=0xFF00;
	second_half=(second_half & port)>>8;
	first_half=first_half & port;

	char port_message[64]={0};
	sprintf(port_message,"%s, %s, %s, %s, %d, %d",temp1,temp2,temp3,temp4,second_half,first_half);
	char std_message[36]={0};
	char status=create_command ("PORT", port_message, std_message);

	status= send(sockfd , std_message , strlen(std_message), 0);
			//send_command(sockfd,std_message,strlen(std_message));
	if (status!=-1) {
		status=recv_response(sockfd);
	}

	return status;
}


