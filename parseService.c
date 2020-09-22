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
#include <ctype.h>
#include "parseService.h"

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

// This method goes through each command line arg and checks if it matches up 
// to one of the possible commands, and then sets the designated flag for that
// as well as retrieving a possible process id.
CmdLineArgDto * parseCommandLine(int argc, char *argv[]){

	// set the string of options that are valid. Used as argument for getopt() func
	const char *commands =  "p::s::U::S::v::c::";
  
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
	while(i < argc){
		// get options from the command line
		option = getopt (argc, argv, commands);
		if(option != -1){
			switch(option)
			{

			// -p option
			case 'p':
				//test that there is an extra hyphen
				if((optarg != NULL) && (strcmp(optarg, "-") == 0)){
					// -p- option
					pFlag = 0;
				}else if((optarg != NULL)){
					//test that the extra argument is a number
					if(isInt(optarg)){
						pID = optarg;
						pFlag = 1;
					}else{
						printf("ERROR: Process ID list syntax error\n");
						// error
						return NULL;
					}
	  			}else{
	    				pFlag = 1;
				}
	  			break;

			// -s option
			case 's':
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
				break;

			// -U option
			case 'U':
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
				break;

			// -S option
			case 'S':
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
				break;

			// -v option
			case 'v':
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
				break;

			// -c option
			case 'c':
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
				break;

			// bad input  
			case '?':
				printf("ERROR: Process ID list syntax error\n");
				// error
				return NULL;
				break;

			default:
			break;
			}
		numOptions++;
		}
		i++;
	}

	// count the number of arguments left that aren't options
	int numNonOptions = (argc-numOptions)-1;
	// there should only be the pid that isn't an option, if it exists
	if(numNonOptions == 1){
		// check it's number
		if(isInt(argv[optind])){
			pID = argv[optind];
		}else{
			printf("ERROR: Process ID is not valid.\n");
			// error
			return NULL;
		}
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
