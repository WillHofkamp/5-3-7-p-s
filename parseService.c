////////////////////////////////////////////////////////////////////////////////
// Main File: main.c
// This File: parseService.c
// This File Description: This file is the command line parser which parses in
//						  the arguments of the command line and sets flags for
//						  the print options
// Author:           William Hofkamp, Pranet Gowni
// Email:            hofkamp@wisc.edu, gowni@wisc.edu
// CS Login:         hofkamp, pranet
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "parseService.h"

// This method goes through each command line arg and checks if it matches up 
// to one of the possible commands, and then sets the designated flag for that
// as well as retrieving a possible process id.
CmdLineArgDto * parseCommandLine(int argc, char *argv[]){
  
	// hold the selected option
	int option;
 
	// flags to keep track which of the commands were slected
	//-p
	int pFlag = 0;
	// -s
	int lSFlag = 0;
	// -U
	int uFlag = 1;
	// -S
	int uSFlag = 0;
	// -v
	int vFlag = 0;
	// -c
	int cFlag = 1;

	int numOptions = 0;

	// store the process id if one is specified in the command line arguments
	char *pID = NULL;

	int i = 0;
	for(int i = 0; i < argc; i++) {
		// get options from the command line
		option = getopt (argc, argv, "p::s::U::S::v::c::");
		// checks that option was rendered correctly
		if(option != -1){
			// -p option
			if(option == 'p') {
				//test that there is an extra hyphen
				if((optarg != NULL) && (strcmp(optarg, "-") == 0)){
					// -p- option
					pFlag = 0;
				}else if((optarg != NULL)){
					//test that the extra argument is a number
						pID = optarg;
						pFlag = 1;
	  			}else{
	    				pFlag = 1;
				}
			}
			// -s option
			else if(option == 's') {
				if((optarg != NULL) && (strcmp(optarg, "-") == 0)){
					// -s- option
					lSFlag = 0;
				}else if((optarg != NULL)){
					printf("ERROR: Process ID list syntax error\n");
					// error
					return NULL;
				}else{
					lSFlag = 1;
				}
			}
			// -U option
			else if(option == 'U') {
				if((optarg != NULL) && (strcmp(optarg, "-") == 0)){
					// -U- option
					uFlag = 0;
				}else if((optarg != NULL)){
					printf("ERROR: Process ID list syntax error\n");
					// error
					return NULL;
				}else{
					uFlag = 1;
				}
			}
			// -S option
			else if(option == 'S') {
				if((optarg != NULL) && (strcmp(optarg, "-") == 0)){
					// -S- option
					uSFlag = 0;
				}else if((optarg != NULL)){
					printf("ERROR: Process ID list syntax error\n");
					// error
					return NULL;
				}else{
					uSFlag = 1;
				}
			}
			// -v option
			else if(option == 'v') {
				if((optarg != NULL) && (strcmp(optarg, "-") == 0)){
					// -v- option
					vFlag = 0;
				}else if((optarg != NULL)){
					printf("ERROR: Process ID list syntax error\n");
					// error
					return NULL;
				}else{
					vFlag = 1;
				}
			}
			// -c option
			else if(option == 'c') {
				if((optarg != NULL) && (strcmp(optarg, "-") == 0)){
					// -c- option
					cFlag = 0;
				}else if((optarg != NULL)){
					printf("ERROR: Process ID list syntax error\n");
					// error
					return NULL;
				}else{
					cFlag = 1;
				}
			} else if(option == '?') {
				printf("ERROR: Process ID list syntax error\n");
				return NULL;
			}
		}
		numOptions++;
	}

	// count the number of arguments left that aren't options
	int numNonOptions = (argc-numOptions)-1;
	// there should only be the pid that isn't an option, if it exists
	if(numNonOptions == 1){
		// check it's number
		pID = argv[optind];
	}else if(numNonOptions > 1){
		printf("ERROR: Only one id can be specified when using -p.\n");
		// error
		return NULL;
	}

	// construct dto and set values
	CmdLineArgDto *cmdLineArguments;
	cmdLineArguments = (CmdLineArgDto*) calloc(1, sizeof(pID)+sizeof(CmdLineArgDto));
	cmdLineArguments->pFlag = pFlag;
	cmdLineArguments->lSFlag = lSFlag;
	cmdLineArguments->uFlag = uFlag;
	cmdLineArguments->uSFlag = uSFlag;
	cmdLineArguments->vFlag = vFlag;
	cmdLineArguments->cFlag = cFlag;
	cmdLineArguments->pID = pID;

	return cmdLineArguments;
}

