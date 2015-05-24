/*
 * basics.c
 *
 *  Created on: 2015-05-24
 *      Author: sajjad
 */
#include <basics.h>

char create_socket (char* tIP, char* port) {
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	struct addrinfo *serv_addr=NULL;
	getaddrinfo(tIP,port, &hints, &serv_addr);

	struct addrinfo *temp=NULL;
	int sockfd=0;
	char status=0;
	for(temp= serv_addr; temp != NULL; temp = temp->ai_next) {
		sockfd = socket(temp->ai_family, temp->ai_socktype,temp->ai_protocol);
		if (sockfd < 0) {
			perror("ERROR: Socket could not be created! Trying another IP_address...\n");
			continue;
		}

		status=connect(sockfd, serv_addr->ai_addr, serv_addr->ai_addrlen);
		if (status<0) {
			perror("ERROR: Connection to server failed. Trying another IP_address...\n");
			continue;
		}
		break;
	}
	if (temp == NULL) {
		fprintf(stderr, "Failed to connect\n");
		return -1;
		freeaddrinfo(serv_addr);
	}
	char Serv_name[32]={0};
	status=getnameinfo(temp->ai_addr, sizeof(struct sockaddr), Serv_name, 31, NULL, 0, 0);
	if (status==0) {
		printf ("Connected to %s.\n", Serv_name);
	} else {
		return -1;
	}
	freeaddrinfo(serv_addr);

	status=recv_response(sockfd);
	if (status!=0) {
		return -1;
	}
	return sockfd;
}

char ftp_authenticat (int sockfd) {
	char user[16]={0};
	printf("Name: ");
	fgets(user, sizeof(user), stdin);

	char credential_message[21]={0};
	create_command("USER", user, credential_message);
	printf("connection.....\n");
	char status=send_command(sockfd,credential_message,strlen(credential_message));
	if (status==0) {
		status=recv_response(sockfd);
	}
	return status;
}


char terminate_socket (int sockfd) {
	char status=close(sockfd);
	return status;
}



