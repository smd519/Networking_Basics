/*
 * passive.c
 * This function recieves the passive data socket information from the server.
 * This information are passed with code 227, and contatins the IP and Port number.
 *
 * Created on: 2015-05-24
 *      Author: sajjad
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

char recv_pd_info (char* buffer,char* tIP, int data_port) {
	char temp1[4]={0};
	char * ptr1=strstr(buffer, "(");
	char * ptr2=strstr(buffer, ",");
	strncpy(temp1,ptr1+1, ptr2-ptr1-1);
	strcpy(buffer,ptr2+1);

	char temp2[4]={0};
	ptr1=strstr(buffer, ",");
	strncpy(temp2,buffer, ptr1-buffer);
	strcpy(buffer,ptr1+1);

	char temp3[4]={0};
	ptr1=strstr(buffer, ",");
	strncpy(temp3,buffer, ptr1-buffer);
	strcpy(buffer,ptr1+1);

	char temp4[4]={0};
	ptr1=strstr(buffer, ",");
	strncpy(temp4,buffer, ptr1-buffer);
	strcpy(buffer,ptr1+1);
	sprintf(tIP,"%s.%s.%s.%s",temp1, temp2, temp3, temp4);

	printf("IP=%s\n", tIP);

	char temp5[4]={0};
	ptr1=strstr(buffer, ",");
	strncpy(temp5,buffer, ptr1-buffer);
	strcpy(buffer,ptr1+1);
	int f_half=atoi(temp5);

	char temp6[4]={0};
	ptr1=strstr(buffer, ")");
	strncpy(temp6,buffer,ptr1-buffer);
	int s_half=atoi(temp6);

	data_port=s_half+ f_half*256;
	printf("PORT=%d , %d, %d\n", f_half, s_half, data_port);
	return 0;
}
