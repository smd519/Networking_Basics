/*
 * create_command.c
 *
 *  Created on: 2015-05-24
 *      Author: sajjad
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char create_command (char* user_input, char* arg, char* std_message) {
	char* n=NULL;
	if (strcmp(user_input,"USER")==0){
		//login user name
		sprintf(std_message,"USER %s\r\n",arg);
	}
	else if (strstr(user_input,"PORT")!=NULL){
		//list remote files
		sprintf(std_message,"PORT %s\r\n",arg);
	}
	else if (strstr(user_input,"passive")!=NULL){
		//list remote files
		sprintf(std_message,"PASV\r\n");
	}
	else if (strstr(user_input,"ls")!=NULL){
		//list remote files
		sprintf(std_message,"LIST\r\n");
	}
	else if (strstr(user_input,"pwd")!=NULL){
		//print working directory
		sprintf(std_message,"PWD\r\n");
	}
	else if (strstr(user_input,"cd .. ")!=NULL){
		sprintf(std_message,"CDUP\r\n");
	}
	else if ( (n=strstr(user_input,"cd "))!=NULL){
		//change working directory
		sprintf(std_message,"CWD %s\r\n",user_input+3);
	}
	else if ( (n=strstr(user_input,"mkdir "))!=NULL){
		//make a remote directory
		sprintf(std_message,"MKD %s\r\n",user_input+6);
	}
	else if ( (n=strstr(user_input,"rmdir "))!=NULL){
		//remove a remote directory
		sprintf(std_message,"RMD %s\r\n",user_input+6);
	}
	else if ( (n=strstr(user_input,"get "))!=NULL){
		//retrieve a remote file
		sprintf(std_message,"RETR %s\r\n",user_input+4);
	}
	else if ( (n=strstr(user_input,"delete "))!=NULL){
		//delete a remote file
		sprintf(std_message,"DELE %s\r\n",user_input+7);
	}
	else if (strstr(user_input,"help")!=NULL){
		//better to create my own help- listing non-raw commands
		sprintf(std_message,"HELP\r\n");
	}
	else if(strstr(user_input,"exit") !=NULL || strstr(user_input,"quit") !=NULL || strstr(user_input,"bye") !=NULL) {
		sprintf(std_message,"QUIT\r\n");
		return 2;
	}
	printf("creat_command:%s\n",std_message);
	return 0;
}

char send_command(int sockfd,char* fttp_message, int message_length) {
	//FTTP MSG
	int status=send(sockfd , fttp_message , message_length, 0);
	if (status==-1) {
		printf("Error:Sending message to server failed!\n");
		return -1;
	}
	if (status < message_length) {
		printf("Error: Only %d out of %d bytes is sent!\n",status ,message_length);
		return -1;
	}

	return 0;
}
