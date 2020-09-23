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

static const int MAX_IDS = 600;
static const int BUFFER= 300;

//file path variables
static const char *proc = "/proc/";
static const char *status = "/status";

// This method is used as a way to validate that a char* pid is actually an int
int isInt(char *arg){
	int i = 0;
	// test that each character in the string is a digit
	while(*(arg+i) != '\0'){
		if(!(isdigit(*(arg+i))) ){
			// isn't a number
			return 0;
		}
		i++;
	}
	// is a number
	return 1;
}

// This method reads through the list of processes in /proc,
// checks which ones belong to the current user, and then stores
// those processes in an array and returns that array
char ** readInListOfPIDs(){

	DIR *dp;
	struct dirent *entry;
	char *pid;
	int processUserID = 0;
	char *read = "r";

	int userUserID = getuid();
	
	// a check to see if the directory is valid
	if ((dp = opendir("/proc")) == NULL){
		fprintf(stderr, "cannot open directory");
		return NULL;
	}
	// the while loop that iterates through /proc
	int count = 0;
	char ** listOfPIDs;
	listOfPIDs = (char **) calloc((BUFFER*MAX_IDS), sizeof(char *));
	while((entry = readdir(dp)) != NULL){

		// if the dirent struct holds the pid in d_name
		if(isInt(entry->d_name)){
			pid = entry->d_name;

			// create filepath to check uid
			char *filePath;
			filePath = calloc((sizeof(proc)+sizeof(pid)+sizeof(status)), sizeof(char));
			strcat(filePath, proc);
			strcat(filePath, pid);
			strcat(filePath, status);
			
			// creates object from the stat file	
			FILE *statFile;
			statFile = fopen(filePath, read);
			free(filePath);

			if (statFile == 0){
				// process doesn't belong to current user, ignore
			}else{
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
				if (userUserID == processUserID) {
						*(listOfPIDs+count) = pid;
						// keep an index of pid
						count++;
				}
			}
			fclose(statFile);	
		}
	}
	return listOfPIDs;
}
