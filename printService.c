////////////////////////////////////////////////////////////////////////////////
// Main File: main.c
// This File: parser.c
// This File Description: This is the print service which prints out information
//						  about one or multiple processes based on the flags set
//						  when parsing the command line
// Author:           William Hofkamp, Pranet Gowni
// Email:            hofkamp@wisc.edu, gowni@wisc.edu
// CS Login:         hofkamp, pranet
////////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parseService.h"
#include "printService.h"
#include "readerService.h"

static const int BUFFER = 1000;

// file path variables
static const char *proc = "/proc/";
static const char *stat = "/stat";
static const char *statm = "/statm";
static const char *cmdline = "/cmdline";
static const char *read = "r";

// This method retrieves the information that will be printed for the PID
// based off of the flags that were parsed from the command line.
// Returns 0 if a success and -1 if error
int printProcesses(cmdLineArgs *options, char *pID){

	// initialize variables that will be printed
	char stateInfo = '\0';
	unsigned long int userTime = 0;
	unsigned long int systemTime = 0;
	int size = 0;

	// create file path for current pid
	char *currPidPath;
	currPidPath = (char *) calloc((sizeof(proc)+sizeof(pID)), sizeof(char));
	strcat(currPidPath, proc);
	strcat(currPidPath, pID);

	// get stat file of current pid
	char *statPath;
	statPath = (char *) calloc((sizeof(stat) + sizeof(currPidPath)), sizeof(char));
	strcat(statPath,currPidPath);
	strcat(statPath,stat);

	// store the stat file of the current pid because it is reused multiple times
	FILE *statFile;
	statFile = fopen(statPath, read);
	free(statPath);
	//check if statfile is loaded 
	if (statFile == 0){
		perror("ERROR: Cannot open stat file of current pid\n");
		free(currPidPath);
		return -1;
	}else{
		char *statParse;
		statParse = (char *) calloc(BUFFER, sizeof(char));
		int i = 0;
		for(int i=0; i<= 15; i++) {
			if(!(fscanf(statFile,"%s",statParse)) == 1) {
				break;
			}
			// get status
			if(i == 2){
				stateInfo = statParse[0];
			}

			// get u time
			if(i == 13){
				userTime = atoi(statParse);
			}

			// get s time
			if(i == 14){
				systemTime = atoi(statParse);
				break;
			}
		}
		free(statParse);
		fclose(statFile);
	}
	
	
	// -s option
	if(options->lSFlag){
		// print state information char
		printf("%c ", stateInfo);
	}

	// -U option
	if(options->uFlag){
		// print user time
		printf("utime=%lu ", userTime); 
		
	}

	// -S option
	if(options->uSFlag){
		// print stime
		printf("stime=%lu ", systemTime);
	}

	// -v option
	if(options->vFlag){
		//get statm file
		char *statmPath;
		statmPath = (char *) calloc((sizeof(statm) + sizeof(currPidPath)), sizeof(char));
		strcat(statmPath,currPidPath);
		strcat(statmPath,statm);

		FILE *statm_file;
		statm_file = fopen(statmPath, read);
		free(statmPath);
		if (statm_file == 0){
			//failed to open file
			perror("ERROR: Cannot open statm file\n");
			free(currPidPath);
			return -1;
		}else{
			char *statmParse;
			statmParse = (char *) calloc(BUFFER, sizeof(char));
			int i = 0;
			if((fscanf(statm_file,"%s",statmParse)) == 1) {
				size = atoi(statmParse);
			}
			free(statmParse);
			fclose(statm_file);
		}
		printf("vmemory=%d ",size);
	}

	// -c option
	if(options->cFlag){
		// get cmdline file
		char *cmdlinePath;
		cmdlinePath = calloc((sizeof(cmdline) + sizeof(currPidPath)), sizeof(char));
		strcat(cmdlinePath,currPidPath);
		strcat(cmdlinePath,cmdline);
		//load in the command line file
		FILE *cmdline_file;
		cmdline_file = fopen(cmdlinePath, read);
		free(cmdlinePath);
		if (cmdline_file == 0){
			//fopen returns 0, the NULL pointer, on failure
			perror("ERROR: Cannot open cmdline file\n");
			free(currPidPath);
			return -1;
		}else{
			char *cmdLineParse;
			cmdLineParse = calloc((BUFFER*2), sizeof(char));
			if((fscanf(cmdline_file,"%s",cmdLineParse)) == 1){
				printf("[%s]", cmdLineParse);
			}
			free(cmdLineParse);
			fclose(cmdline_file);
		}
	}
	free(currPidPath);
	printf("\n");
	return 0;
}
