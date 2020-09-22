////////////////////////////////////////////////////////////////////////////////
// Main File: main.c
// This File: main.c
// This File Description: This file is the main file that calls the services to
//						  parse arguments, set options, and print process info
// Author:           William Hofkamp, Pranet Gowni
// Email:            hofkamp@wisc.edu, gowni@wisc.edu
// CS Login:         hofkamp, pranet
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include "parseService.h"
#include "printService.h"
#include "readerService.h"

// the main function of the program that will utilize other modules
// for parsing the input, finding valid ppids, and printing out
// the relevant information
int main(int argc, char *argv[]){
  
	CmdLineArgDto *cmdLineArgs = parseCommandLine(argc,argv);
	if(cmdLineArgs == NULL){
		// null error, cmd line args weren't loaded correctly
		return -1;
	}

	// check if printing out information for a single process
	if(cmdLineArgs->pFlag){

		if(cmdLineArgs->pID != NULL){
			// print the pid
			printf("%s: ",cmdLineArgs->pID);
			// print the info related to the process
			if(printProcesses(cmdLineArgs, cmdLineArgs->pID)){
				// error happened while printing
				printf("\n");
				return -1;
			}	  
		}else{
			// if -p exists there must be pid with it
			printf("ERROR: No PID.\n");
			// error
			return -1;
		}
		
	// otherwise print out information for all processes
	}else if(!cmdLineArgs->pFlag){
		// get a list of all valid process ids to print
		char ** pIDList = readInListOfPIDs();

		// index for cycling through the pointer to char pointers
		int i = 0;
		// go through the list of pids
		while(*(pIDList+i) != NULL){
			// print individual process id
			printf("%s: ",*(pIDList+i));
			// print the process info
			if(printProcesses(cmdLineArgs, *(pIDList+i))){
				// error
				printf("\n");
				return -1;
			}
			i++;
		}

	}
}
