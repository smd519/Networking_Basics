/*
 * Syn_Scanner.c
 *
 *  Created on: 2015-05-29
 *      Author: sajjad
 */
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc<4) {
		printf ("please enter the server IP address and range of ports to be scanned\n");
		printf ("Sync_Scanner IPv4_address First_Port Last_Port\n");
	}
	char tIP[16]={0};
	strcpy(tIP, argv[1]);
	char First_Port[6]={0};
	strcpy(First_Port, argv[2]);
	char Last_Port[6]={0};
	strcpy(Last_Port, argv[3]);

	//1. Initialize the tcp/ip Packet
		//1.1 create the ip header
		//1.2 initialize the tcp header
	//2. LOOP:
		//2.1 create tcp header
		//2.2 create pesudo header
		//2.3 calculate checksum;
		//2.4 send the packets
		//2.5 receive from other side
			//2.5.1 analyze the packets & identify if port is open/close/filtered
	//Repeat LOOP

	return 0;
}
