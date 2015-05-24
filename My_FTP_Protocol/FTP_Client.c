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

#define CTRLPORT "21"
#define DATAPORT "20"

char create_socket (char*, char*);
char ftp_authenticat(int);
char create_command (char*, char*, char*);
char send_command(int, char*, int);
char recv_response(int);

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

char recv_response(int sockfd) {
	//Receiving msg response
	char buffer[128];
	memset(&buffer,0,128);
	char chbuffer[2];
	memset(&chbuffer,0,2);
	char status=0;

	char message_flag=1;
	while (message_flag){
		memset(&buffer,0,128);

		char line_flag=1;
		while (line_flag) {
			memset(&chbuffer,0,2);
			status = recv(sockfd, (void *)chbuffer,1,0);
			if (status==0) {
				printf ("Connection terminated.\n");
				message_flag=0;
				line_flag=0;
			}
			if (status==-1){
				perror("Error: Reading RESPONSE failed\n");
				return -1;
			}
			strcat(buffer,chbuffer);
			if ('\n'==chbuffer[0]) {
				line_flag=0;

			}
		}
		printf("%s", buffer);
		if (' '==buffer[3]) {
			message_flag=0;
		}
	}
	printf ("server message fully received.\n");
	return 0;
}

char send_command(int sockfd,char* fttp_message, int message_length) {
	//FTTP MSG
	int status=send(sockfd , fttp_message , message_length, 0);
	if (status < message_length) {
		printf("Error (size of message):Sending message to server failed!\n");
		return -1;
	}
	if (status==-1) {
		printf("Error:Sending message to server failed!\n");
		return -1;
	}
	return 0;
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

char create_command (char* user_input, char* arg, char* std_message) {
	char* n=NULL;
	if (strcmp(user_input,"USER")==0){
		sprintf(std_message,"USER %s\r\n",arg);
	} else if (strstr(user_input,"ls")!=NULL){
		sprintf(std_message,"LIST\r\n");
	} else if (strstr(user_input,"pwd")!=NULL){
		sprintf(std_message,"PWD\r\n");
	} else if (strstr(user_input,"cd .. ")!=NULL){
		sprintf(std_message,"CDUP\r\n");
	} else	if ( (n=strstr(user_input,"cd "))!=NULL){
		sprintf(std_message,"CWD %s\r\n",user_input+3);
	} else	if (strstr(user_input,"help")!=NULL){
		//better to creat your own help- listing non-raw commands
		sprintf(std_message,"HELP\r\n");
	} else	if(strstr(user_input,"exit") !=NULL || strstr(user_input,"quit") !=NULL || strstr(user_input,"bye") !=NULL) {
		sprintf(std_message,"QUIT\r\n");
		return 2;
	}
	printf("creat_command:%s\n",std_message);
	return 0;
}


char terminate_socket (int sockfd) {
	char status=close(sockfd);
	return status;
}


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
	fflush(stdout);
	char flag=1;
	char user_input[64];
	char std_message[70];

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
