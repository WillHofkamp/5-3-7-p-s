////////////////////////////////////////////////////////////////////////////////
// Main File: 537.c
// This File: parser.c
// This File Description: This is the print service which prints out information
//						  about one or multiple processes based on the flags set
//						  when parsing the command line
// Author:           William Hofkamp, Pranet Gowni
// Email:            hofkamp@wisc.edu, gowni@wisc.edu
// CS Login:         hofkamp, pranet
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parseService.h"
#include "printService.h"
#include "readerService.h"

static const int BUFFER = 1000;

// This method retrieves the information that will be printed for the PID
// based off of the flags that were parsed from the command line.
// Returns 0 if a success and -1 if error
int printProcess(cmdLineArgs *args, char *pID){

	// initialize variables that will be printed
	char stateInfo = '\0';
	long unsigned int userTime = 0;
	long unsigned int systemTime = 0;
	int size = 0;

	//create pid file path string through concatenation
	char *currPidPath;
	currPidPath = (char *) calloc((sizeof("/proc/")+sizeof(pID)), sizeof(char));
	strcat(currPidPath, "/proc/");
	strcat(currPidPath, pID);

	//create stat file path string through concatenationd
	char *statPath;
	statPath = (char *) calloc((sizeof("/stat") + sizeof(currPidPath)), sizeof(char));
	strcat(statPath,currPidPath);
	strcat(statPath,"/stat");

	// open the stat file
	FILE *statFile;
	statFile = fopen(statPath, "r");
	free(statPath);

	if (statFile == 0){
		perror("ERROR: Cannot open stat file of current pid\n");
		free(currPidPath);
		return -1;
	}else{
		char *statParse;
		statParse = (char *) calloc(BUFFER, sizeof(char));
		//iterate over the stat file to get the status, u time, and s time.
		//since the file format is the same each time, a for loop and set numbers are used
		for(int i=0; i<= 15; i++) {
			//check that the next line of the file was scanned correctly
			if((!(fscanf(statFile,"%s",statParse))) == 1) {
				break;
			}
			// get status info
			if(i == 2){
				stateInfo = statParse[0];
			}

			// get u time info
			if(i == 13){
				userTime = atoi(statParse);
			}

			// get s time info
			if(i == 14){
				systemTime = atoi(statParse);
				break;
			}
		}
		free(statParse);
		fclose(statFile);
	}

	// -c option
	if(args->cFlag){
		//create command line file path string through concatenation
		char *cmdLinePath = calloc((sizeof("/cmdline") + sizeof(currPidPath)), sizeof(char));
		strcat(cmdLinePath,currPidPath);
		strcat(cmdLinePath,"/cmdline");

		//open the command line file
		FILE *cmdLineFile;
		cmdLineFile = fopen(cmdLinePath, "r");
		free(cmdLinePath);

		if (cmdLineFile == 0){
			perror("ERROR: Cannot open cmdline file\n");
			free(currPidPath);
			return -1;
		}else{
			char *cmdLineParse = calloc((BUFFER*2), sizeof(char));
			//parse command line file and print the first line
			if((fscanf(cmdLineFile," %s",cmdLineParse)) == 1){
				printf("[%s]", cmdLineParse);
			}
			free(cmdLineParse);
			fclose(cmdLineFile);
		}
	}
	
    // -v option
	if(args->vFlag){
		//create statm file path string through concatenation
		char *statmPath = (char *) calloc((sizeof("/statm") + sizeof(currPidPath)), sizeof(char));
		strcat(statmPath,currPidPath);
		strcat(statmPath,"/statm");

		//open the statm file
		FILE *statmFile;
		statmFile = fopen(statmPath, "r");
		free(statmPath);

		if (statmFile == 0){
			perror("ERROR: Cannot open statm file\n");
			free(currPidPath);
			return -1;
		}else{
			char *statmParse = (char *) calloc(BUFFER, sizeof(char));
			//parse statm file and get the first line
			if((fscanf(statmFile,"%s",statmParse)) == 1) {
				size = atoi(statmParse);
			}
			free(statmParse);
			fclose(statmFile);
		}
		printf("vmemory=%d ",size);
	}

	// -s option
	if(args->lSFlag){
		// print state information char
		printf("%c ", stateInfo);
	}

	// -U option
	if(args->uFlag){
		// print user time
		printf("utime=%lu ", userTime); 
	}

	// -S option
	if(args->uSFlag){
		// print stime
		printf("stime=%lu ", systemTime);
	}

	
	
	free(currPidPath);
	printf("\n");
	return 0;
}

// This method prints out either one process or all the current
// user processes based on args that were parsed from the command
// line. A -1 is returned if there's an error
int printProcesses(cmdLineArgs *arguments) {
	// check if printing out information for a single process
	if(arguments->pFlag){

		if(arguments->pID != NULL){
			// print the pid
			printf("%s: ",arguments->pID);
			// print the info related to the process
			if(printProcess(arguments, arguments->pID)){
				// error happened while printing
				printf("\n");
				return -1;
			}	  
		}else{
			// if -p exists there must be pid with it
			printf("ERROR: No PID.\n");
			return -1;
		}
		
	// otherwise print out information for all processes
	}else {
		// get a list of all valid process ids to print
		char ** pIDList = readPIDs();
		int i = 0;
		// go through the list of pids
		while(*(pIDList+i) != NULL) {
			// print individual process id
			printf("%s: ",*(pIDList+i));
			// print the process info
			if(printProcess(arguments, *(pIDList+i))){
				printf("\n");
				return -1;
			}
			i++;
		}

	}
	return 0;
}
