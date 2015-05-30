/*
 * create_rawscoket.c
 *
 *  Created on: 2015-05-30
 *      Author: sajjad
 */

#include <create_rawscoket.h>

int create_rawscoket(void) {
	int sockfd = socket(AF_INET,SOCK_RAW ,IPPROTO_TCP);
	if (sockfd < 0) {
		perror("ERROR: Socket could not be created!\n");
		return -1;
	}

    //set IP_HDRINCL to 1.
	const int opt_on = 1;
    if (setsockopt (sockfd, IPPROTO_IP, IP_HDRINCL, &opt_on, sizeof (opt_on)) < 0)
    {
    	perror("ERROR: Error in socket options\n");
        return -1;
    }

    printf ("socket is created\n");
	return sockfd;
}


