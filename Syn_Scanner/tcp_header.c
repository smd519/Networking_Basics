/*
 * tcp_header.c
 *
 *  Created on: 2015-05-30
 *      Author: sajjad
 */
#include <tcp_header.h>

char init_tcph(struct tcphdr *tcp_header) {
	tcp_header->source=htons(212015);
	tcp_header->dest=htons (80);

	tcp_header->seq=htonl(1105024978); //Sequence Number (32-bit)
	tcp_header->ack_seq = 0; //Acknowledgement Number (32-bit)
	tcp_header->doff=sizeof(struct tcphdr) / 4; //Data Offset (4-byte units)
	tcp_header->fin=0;  //Finish flag "fin"*/
	tcp_header->syn=1;
	tcp_header->rst=0;
	tcp_header->psh=0;
	tcp_header->ack=0;
	tcp_header->urg=0; // True if 'Urgent' flag is 1
	tcp_header->window = htons ( 16384 );  // Receive Window size// read from filesystem

	tcp_header->check = 0; //if you set a checksum to zero, your kernel's IP stack should fill in the correct checksum during transmission
	tcp_header->urg_ptr = 0; //TCP Urgent Pointer

	return 0;
}

