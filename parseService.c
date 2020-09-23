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
cmdLineArgs * parse(int argc, char *argv[]){
  
	// variable for the chosen option from the command line
	int option;
	int argsCount = 0;
 
	// flags to keep track which of the commands were selected
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
	// if no process id is given in the command line arguments
	char *pID = NULL;

	int i = 0;
	for(int i = 0; i < argc; i++) {
		// get options from the command line
		option = getopt (argc, argv, "p::s::U::S::v::c::");
		if(option != -1){
			argsCount++;
			// -p option
			if(option == 'p') {
				//checking for the hyphen
				argsCount++;
				if(optarg != NULL){
					// -p- option
					if(strcmp(optarg, "-" ) == 0){
						pFlag = 0;
					}
				    else{
					//checking that the optional argument has been provided
						pID = optarg;
						pFlag = 1;
	  			}}
				else{
					printf("No argument provided");
	    			pFlag = 1;
				}
			}
			// -s option
			else if(option == 's') {
				if(optarg != NULL){
					if(strcmp(optarg, "-") == 0){
						lSFlag = 0;
					}
			        else{
						printf("ERROR: Invalid argument\n");
						return NULL;
					}
				}else{
					lSFlag = 1;
				}
			}
			// -U option
			else if(option == 'U') {
				if(optarg != NULL){
					if(strcmp(optarg, "-") == 0){
						uFlag = 0;
					}
			        else{
						printf("ERROR: Invalid argument\n");
						return NULL;
					}
				}else{
					uFlag = 1;
				}
			}
			// -S option
			else if(option == 'S') {
				if(optarg != NULL){
					if(strcmp(optarg, "-") == 0){
						uSFlag = 0;
					}
			        else{
						printf("ERROR: Invalid argument\n");
						return NULL;
					}
				}else{
					uSFlag = 1;
				}
			}
			// -v option
			else if(option == 'v') {
				if(optarg != NULL){
					if(strcmp(optarg, "-") == 0){
						vFlag = 0;
					}
			        else{
						printf("ERROR: Invalid argument\n");
						return NULL;
					}
				}else{
					vFlag = 1;
				}
			}
			// -c option
			else if(option == 'c') {
				if(optarg != NULL){
					if(strcmp(optarg, "-") == 0){
						cFlag = 0;
					}
			        else{
						printf("ERROR: Invalid argument\n");
						return NULL;
					}
				}else{
					cFlag = 1;
				}
			} 
			else if(option == '?') {
				printf("ERROR: Process ID list syntax error\n");
				return NULL;
			}
		}
		else{
			break;
		}
		//argsCount++;
	}

	// check the total number of arguments given
	if(argc > argsCount){
		printf("Invalid number of arguments\n");
	}
	

	// construct dto and set values
	cmdLineArgs *cmdLineArguments;
	cmdLineArguments = (cmdLineArgs*) calloc(1, sizeof(pID)+sizeof(cmdLineArgs));
	cmdLineArguments->pFlag = pFlag;
	cmdLineArguments->lSFlag = lSFlag;
	cmdLineArguments->uFlag = uFlag;
	cmdLineArguments->uSFlag = uSFlag;
	cmdLineArguments->vFlag = vFlag;
	cmdLineArguments->cFlag = cFlag;
	cmdLineArguments->pID = pID;

	return cmdLineArguments;
}
