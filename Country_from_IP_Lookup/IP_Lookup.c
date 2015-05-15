/*
 * IP_Lookup.c
 *
 *  Created on: 2015-05-11
 *      Author: sajjad
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

char Is_Valid_IP (const char* tIP) { //IP in text format
    struct sockaddr_in bIP;
    int result = inet_pton(AF_INET, tIP, &(bIP.sin_addr)); // returns 1 on success
    return result==1;
}

void Locate_My_IP () {
	printf ("Your IP address is:");
	printf ("\n");
	int result=system("curl ipinfo.io/ip"); //We don't have any loops here, so using system() is almost safe.
	if (result==-1 || result==127 ) {
		printf("Error: IP could not be resolved\n");
		exit(EXIT_FAILURE);
	}
	printf ("from city of:");
	printf ("\n");
	result=system("curl ipinfo.io/city");
	if (result==-1 || result==127 ) {
		printf("Error: Location could not be resolved\n");
		exit(EXIT_FAILURE);
	}
}

void Locate_This_IP (const char* tIP) {
	if ( Is_Valid_IP(tIP)!=1 ) {
		printf("Not a valid IP address\n");
	}else {
		char url[50]={0};
		strcpy(url,"curl ipinfo.io/");
		strcat(url, tIP);
		char url2[50]={0};
		strcpy(url2,url);
		strcat(url,"/city");
		int result=system(url);
		if (result==-1 || result==127 ) {
			printf("Error: Location could not be resolved\n");
			exit(EXIT_FAILURE);
		}
		strcat(url2,"/country");
		result=system(url2);
		if (result==-1 || result==127 ) {
			printf("Error: Location could not be resolved\n");
			exit(EXIT_FAILURE);
		}
	}
}
int main(int argc, char *argv[]) {
	if (argc==1) {
		// If No IP address is entered, just lookuP the IP-address of the machine
		Locate_My_IP ();
	} else {
		//If an IP-address is entered to be located
		printf ("Locating %s...\n", argv [1]);
		Locate_This_IP (argv [1]);
	}
	return 0;
}
