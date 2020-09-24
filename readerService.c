////////////////////////////////////////////////////////////////////////////////
// Main File: main.c
// This File: readerService.c
// This File Description: This file is the reader service which reads the proc
//						  file and returns the list of current user processes
// Author:           William Hofkamp, Pranet Gowni
// Email:            hofkamp@wisc.edu, gowni@wisc.edu
// CS Login:         hofkamp, pranet
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "readerService.h"

static const int BUFFER = 255;

// This method is used as a way to validate that a char* pid is actually an int
int isInt(char *arg){
	int i = 0;
	// test that each character in the string is a digit
	while(*(arg+i) != '\0'){
		if(!(isdigit(*(arg+i))) ){
			return 0;
		}
		i++;
	}
	return 1;
}

// Find the processes in /proc which belong to the current user,
// and return them in an array
char ** readPIDs(){

	DIR *procDirectory;
	struct dirent *entry;
	char *pid;
	int processUserID = 0;
	
	// Check to see if the directory exists
	if ((procDirectory = opendir("/proc")) == NULL){
		fprintf(stderr, "couldn't open directory");
		return NULL;
	}
	int count = 0;
	char ** pidList;
	pidList = (char **) calloc((BUFFER*600), sizeof(char *));
	// iterate through proc directory
	while((entry = readdir(procDirectory)) != NULL){

		if(entry->d_type == DT_DIR && isInt(entry->d_name)){
			pid = entry->d_name;

			// creating a filepath to check the uid
			char *filePath;
			filePath = calloc((sizeof("/proc/")+sizeof(pid)+sizeof("/status")), sizeof(char));
			strcat(filePath, "/proc/");
			strcat(filePath, pid);
			strcat(filePath, "/status");
				
			FILE *statFile;
			statFile = fopen(filePath, "r");
			free(filePath);

			if (statFile != 0){
				char *statParse;
				statParse = (char *) calloc(BUFFER, sizeof(char *));
				int isUIDNext = 0;
				while ((fscanf(statFile,"%s",statParse)) == 1){
					if(isUIDNext){
						// get uid if it's the next line
						processUserID = atoi(statParse);
						break;
					}
					if(strcmp(statParse, "Uid:") == 0){
						isUIDNext = 1;
					}
				}
				free(statParse);
				// if uid matches add it to the array
				if (getuid() == processUserID) {
						*(pidList+count) = pid;
						count++;
				}
			}
			fclose(statFile);	
		}
	}
	return pidList;
}
