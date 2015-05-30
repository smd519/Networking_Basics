/*
 * ip_header.c
 *	This functions populates filed of an ipv4-header.
 *  Created on: 2015-05-29
 *      Author: sajjad
 */
#include <ip_header.h>

char create_iph(char * tIP,struct iphdr *ip_header) {
	struct in_addr  target;
	memset(&target,0, sizeof(target));
	int status=inet_aton(tIP, &target);
	if (status==0) {
		printf("address is not valid\n");
		return -1;
	}

	struct in_addr source;
	memset(&source,0, sizeof(source));
	status=inet_aton("192.168.0.1",&source); //any valid ip address, lets do ip snoofing :D
	if (status==0) {
		printf("address is not valid\n");
		return -1;
	}

	ip_header->ihl = 5;
	ip_header->version = 4;
	ip_header->tos = 72; //Immediate
	ip_header->tot_len = sizeof (struct ip) + sizeof (struct tcphdr);
	ip_header->id = htons((int)(rand()/(((double)RAND_MAX + 1)/14095))); //just random ID
	ip_header->frag_off =0;
	ip_header->ttl = 64;

	ip_header->protocol = IPPROTO_TCP;
	ip_header->saddr = source.s_addr;
	ip_header->daddr = target.s_addr;

	ip_header->check = 0; // Check sum is calculated only for ip header fields except chksum
	ip_header->check = checksum (ip_header, sizeof(struct iphdr)); // only ip-header, before tcp

	return 0;
}
