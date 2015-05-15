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

void My_HTTP_GET(void) {
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

	char message[64];

	//GET /city HTTP/1.1\r\nHost:ipinfo.io\r\n\r\n
	strcpy(message,"GET /ip HTTP/1.1\r\nHost:ipinfo.io\r\n\r\n");
	n=send(sockfd , message , strlen(message) , 0);
	if (n <0){
		perror("Error: Sending HTTP GET failed!");
	    exit(1);
	}
	char buffer[600];
	bzero(buffer,600);
	n = recv(sockfd, (void *)buffer,184,0);
	if (n ==-1){
		perror("Error: Reading 1 HTTP RESPONSE failed\n");
		exit(1);
	}
	char* index=strstr(buffer,"\r\n\r\n");
	printf("Here is your IP-Address:\n%s\n\n\n", index+4);

	close(sockfd);
}

void My_HTTP_GET () {
	//Pass a message for ipinfo.io/ip
	//Pass a message for ipinfo.io/city
}

void Locate_This_IP (const char* tIP) {
	//Pass a message for ipinfo.io/ip_adress/city
}

int main(int argc, char *argv[]) {
	if (argc==1) {
		// If No IP address is entered, just lookuP the IP-address of the machine
		My_HTTP_GET ();
	}
	return 0;
}


