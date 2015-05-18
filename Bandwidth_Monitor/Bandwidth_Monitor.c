/*
 * Bandwidth_Monitor.c
 *
 *  Created on: 2015-05-15
 *      Author: sajjad
 */
/*Bandwidth Monitor - A small utility program that tracks how much data you have uploaded and
downloaded from the net during the course of your current online session. See if you can find out
what periods of the day you use more and less and generate a report or graph that shows it.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

char creat_file_path  (char *filePath, char* net_intf) {
	strcpy(filePath,"/sys/class/net/");
	strcat(filePath,net_intf);
	struct stat link_attributes;

	if( ( lstat( filePath, &link_attributes ) ) != 0 ) {//getting information about the file
		if (errno==ENOENT) {
			fprintf( stderr, "Error_lstat:No such network interface\n" );
			return(-1);
	} else { //other types of error
		perror("Error_lstat: ");
		return(-1);
	}
	}
	return 0;
}

char find_intf_information (char *filePath, char* net_intf) {
	if (strstr(net_intf,"upload") ) {
		strcat(filePath,"/statistics/tx_bytes");
	} else if (strstr(net_intf,"download")){
		strcat(filePath,"/statistics/rx_bytes");
	} else {
		printf("Error: please enter a valid input; upload or download?\n");
		return -1;
	}
	struct stat link_attributes;
	if( ( lstat( filePath, &link_attributes ) ) != 0 ) {//getting information about the file
		if (errno==ENOENT) {//no record about received bytes for this interface
			fprintf( stderr, "Error_lstat:No information about this interface.\n" );
			return(-1);
		} else {//other types of error
			perror("Error_lstat: ");
			return(-1);
		}
	}

	if( !S_ISREG( link_attributes.st_mode ) ) {//Is it a regular file?
		fprintf( stderr, "Error_S_ISREG: Information could not be interpreted.\n" );
		return(-1);
	}

	if( ! ((link_attributes.st_mode & S_IRUSR) && (link_attributes.st_mode & S_IRGRP) && (link_attributes.st_mode & S_IROTH)) ) {
		printf("Warning:You may not have the permission to access to this information.\n" );
		return(-1);
	}
	return 0;
}

void current_session (char *filePath) {
	FILE *file = NULL;
	if ( (file = fopen(filePath, "r") )== NULL ) {
		perror( "Error_fopen" );
		exit (-1);
	}
	char buf[128];
	if( fgets(buf, 127, file)==NULL) {
		perror( "Error_fgets" );
		exit (-1);
	}
	buf[511]='\0';
	printf ("%s",buf);
	if (fclose(file)!=0) {
		perror("Error_fclose");
		exit (-1);
	}
}

int main (int argc, char* argv[]) {
	const int measurement_period=1*60*60;
	const short int measurement_interval=30; // measurement_interval-sec
	const char total_measurement_points=measurement_period/measurement_interval; //how many times we record BW
	char filePath[128];
	if (argc < 2) {
		printf("Error: Please specify which network interface you would like to monitor\n");
		return -1;
	}
	if(creat_file_path(filePath, argv[1])==-1){
		return -1;
	}
	if (argc<3) {
		printf("Error: Please specify upload or download\n");
		return -1;
	}
	if (find_intf_information(filePath, argv[2])==-1) {
		return -1;
	}
	if (argc <4 ) {
		current_session(filePath);
		return 0;
	}
	FILE *file = NULL;
	if ( (file = fopen(filePath, "r") )== NULL ) {
		perror( "Error_fopen" );
		return (-1);
	}

	FILE *Result_file = fopen("file.txt", "w");
	if (Result_file== NULL) {
		printf("Error_fopen\n");
		exit(1);
	}
	char buf[128];//current record
	int i;
	for (i=0; i<total_measurement_points;i++) {
		if( ( file = fopen( filePath, "r" ) ) == NULL ) {
			perror( "Error_fopen" );
			return (-1);
		}
		if( fgets(buf, 127, file)==NULL) {
			perror( "Error_fgets" );
			return (-1);
		}
		buf[511]='\0';
		printf ("%s",buf);
		fprintf(Result_file, "%s", buf);
		sleep(measurement_interval);
	}
	if (fclose(file)!=0) {
	perror("Error_fclose");
		return (-1);
	}
	if (fclose(Result_file)!=0) {
		perror("Error_fclose");
		return (-1);
	}
	return 0;
}
