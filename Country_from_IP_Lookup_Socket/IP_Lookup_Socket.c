/*
 * IP_Lookup_Socket.c
 *
 *  Created on: 2015-05-13
 *      Author: sajjad
 */
/*
 * IP_Lookup.c
 *
 *  Created on: 2015-05-11
 *      Author: sajjad
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

char Is_Valid_IP (const char* tIP) { //IP in text format
    struct sockaddr_in bIP;
    int result = inet_pton(AF_INET, tIP, &(bIP.sin_addr)); // returns 1 on success
    return result==1;
}

void My_HTTP_GET(char* http_message, int message_length) {
	// Create a socket
	int sockfd=0;
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0) {
		perror("ERROR: Socket could not be created!");
		exit(1);
	}

	//Specify the server parameters
	struct sockaddr_in serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	int result = inet_pton(AF_INET, "54.209.233.84", &(serv_addr.sin_addr.s_addr));
	if (result!=1) {
		perror("Error: Address is not valid!\n");
		exit(1);
	}
	serv_addr.sin_port=htons(80); //HTTP/TCP PORT

	//Connecting to the server:ipinfo.io
	char n=connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (n<0) {
		perror("ERROR: Connection to ipinfo.io failed\n");
	    exit(1);
	}

	//HTTP GET
	n=send(sockfd , http_message , message_length, 0);
	if (n <0){
		perror("Error: Sending HTTP GET failed!");
	    exit(1);
	}
	char buffer[200];
	bzero(buffer,200);
	n = recv(sockfd, (void *)buffer,184,0);
	if (n ==-1){
		perror("Error: Reading 1 HTTP RESPONSE failed\n");
		exit(1);
	}
	char* index=strstr(buffer,"\r\n\r\n");
	printf("%s\n", index+4);

	if (close(sockfd)== -1) {
	    perror("Error: Socket can not be closed\n");
	    exit(1);
	}
}

void Locate_My_IP (void) {
	char message[64]; //for storing the customized HTTTP-message
	bzero(message,64);
	//Find the the external ip_address of the machine
	strcpy(message,"GET /ip HTTP/1.1\r\nHost:ipinfo.io\r\n\r\n");
	int message_length=strlen(message);
	My_HTTP_GET (message, message_length);

	bzero(message,64);
	strcpy(message,"GET /city HTTP/1.1\r\nHost:ipinfo.io\r\n\r\n");
	message_length=strlen(message);
	My_HTTP_GET (message, message_length);

	bzero(message,64);
	strcpy(message,"GET /country HTTP/1.1\r\nHost:ipinfo.io\r\n\r\n");
	message_length=strlen(message);
	My_HTTP_GET (message, message_length);
}

void Locate_This_IP (const char* tIP) {
	if ( Is_Valid_IP(tIP)!=1 ) {
		printf("Not a valid IP address\n");
	}else {
		char message_city[64]={0};
		strcpy(message_city,"GET /");
		strcat(message_city, tIP);
		char message_country[64]={0};
		strcpy(message_country,message_city);
		strcat(message_city,"/city");
		strcat(message_city, " HTTP/1.1\r\nHost:ipinfo.io\r\n\r\n");
		int message_length=strlen(message_city);
		My_HTTP_GET (message_city, message_length);

		strcat(message_country,"/country");
		strcat(message_country, " HTTP/1.1\r\nHost:ipinfo.io\r\n\r\n");
		message_length=strlen(message_country);
		My_HTTP_GET (message_country, message_length);
	}
}

int main(int argc, char *argv[]) {
	if (argc==1) {
		// If No IP address is entered, just lookuP the IP-address of the machine
		Locate_My_IP ();
	} else {
		//If an IP-address is entered to be located
		printf ("Locating %s...\n\n", argv [1]);
		Locate_This_IP (argv [1]);
	}
	return 0;
}
