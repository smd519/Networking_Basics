/*
 * Syn_Scanner.c
 *
 *  Created on: 2015-05-29
 *      Author: sajjad
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ip_header.h>
#include <tcp_header.h>
#include <create_rawscoket.h>
#include <recv_response.h>


int main(int argc, char *argv[]) {
	if (argc<4) {
		printf ("please enter the server IP address and range of ports to be scanned\n");
		printf ("Sync_Scanner IPv4_address First_Port Last_Port\n");
	}
	char tIP[16]={0};
	strcpy(tIP, argv[1]);
	struct in_addr  target_IP;
	memset(&target_IP,0, sizeof(target_IP));
	int status=inet_aton(tIP, &target_IP);
	if (status==0) {
		printf("address is not valid\n");
		return -1;
	}
	char First_Port[6]={0};
	strcpy(First_Port, argv[2]);
	char Last_Port[6]={0};
	strcpy(Last_Port, argv[3]);

    char packet[4096]={0}; // |--IP_header--| |--TCP-header--| + |--Data--|
    memset(&packet,0,4096);
    //1. Initialize the tcp/ip Packet
	//1.1 create the ip header
    struct iphdr *ip_header = (struct iphdr *) packet;
    status=0;
    status=create_iph(tIP,ip_header);
	if (status!=0) {
		return -1;
	}
	//1.2 initialize the tcp header
    struct tcphdr *tcp_header = (struct tcphdr *) (packet + sizeof (struct ip));
    status=0;
    status=init_tcph(tcp_header);
	if (status!=0) {
		return -1;
	}

	//1.3 create a raw socket
	int sockfd=-1;
	sockfd=create_rawscoket();
	if (sockfd <0) {
		return -1;
	}
	//2. LOOP:
	int s_port=atoi(First_Port);
	int e_port=atoi(Last_Port);
	//----------
	struct sockaddr_in target;
	memset(&target,0, sizeof(struct sockaddr_in));
	target.sin_family=AF_INET;
	target.sin_port=htons(80); //for now-initialize
	target.sin_addr=target_IP;
	//.............

	int port=0;
    for(port = s_port; port <= e_port ; port=port+1)
    {
		//2.1 update TCP header with new port information
    	tcp_header->dest = htons(80);
    	//target.sin_port=tcp_header->dest;
    	//2.2 calculate the checksum for tcp header
    	tcp_header->check =0;
    	tcp_header->check=tcp_checksum(tcp_header);

   	 printf ("Message sent:\n");
        int segment_len=sizeof(struct tcphdr)+sizeof(struct ip);
        int i=0;
        for (i = 0; i < segment_len; i++) {
             printf ("%02X ", packet[i]);
        }
        printf ("\n\n");

		//2.3 send the packets
    	status=0;
    	status= sendto(sockfd, packet, sizeof(struct iphdr) + sizeof(struct tcphdr),
    			0, (struct sockaddr*)&target, sizeof(target));

    	 if (status < 0) {
    	    perror("Error: Sending SYN packet failed\n");
    	    terminate_socket(sockfd);
    	    return -1;
    	 }

    	 if (status < sizeof(struct iphdr) + sizeof(struct tcphdr) ) {
    	    perror("Error: Sending SYN packet failed\n");
    	    terminate_socket(sockfd);
    	    return -1;
    	 }

    	 status=0;
    	 //status=recv_response(sockfd,(struct sockaddr*)&target);
    	 if (status < 0) {
    	    perror("Error: Sending SYN packet failed\n");
    	    terminate_socket(sockfd);
    	    return -1;
    	 }
    }
		//2.5 receive from other side
			//2.5.1 analyze the packets & identify if port is open/close/filtered
	//Repeat LOOP
    terminate_socket(sockfd);
	return 0;
}
