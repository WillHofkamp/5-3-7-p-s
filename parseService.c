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
  
	// variable for the chosen command from the command line
	int command;
 
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
		// get options from the command line, possible commands are p, s, U, S, v, and c
		command = getopt (argc, argv, "p::s::U::S::v::c::");
		if(command != -1){
			// -p command
			if(command == 'p') {
				//checking for the hyphen
				if(optarg != NULL){
					//checking that the optional argument has been provided
					pID = optarg;
					pFlag = 1;
				} else {
					printf("ERROR: -p command is present but no PID is supplied\n");
					return NULL;
				}
			}
			// -s command
			else if(command == 's') {
				//checks if there is a dash after the command
				if(optarg != NULL && strcmp(optarg, "-") == 0){
					lSFlag = 0;
				}else{
					lSFlag = 1;
				}
			}
			// -U command
			else if(command == 'U') {
				//checks if there is a dash after the command
				if(optarg != NULL && strcmp(optarg, "-") == 0){
					uFlag = 0;
				}else{
					uFlag = 1;
				}
			}
			// -S command
			else if(command == 'S') {
				//checks if there is a dash after the command
				if(optarg != NULL && strcmp(optarg, "-") == 0){
					uSFlag = 0;
				}else{
					uSFlag = 1;
				}
			}
			// -v command
			else if(command == 'v') {
				//checks if there is a dash after the command
				if(optarg != NULL && strcmp(optarg, "-") == 0){
					vFlag = 0;
				}else{
					vFlag = 1;
				}
			}
			// -c command
			else if(command == 'c') {
				//checks if there is a dash after the command
				if(optarg != NULL && strcmp(optarg, "-") == 0){
					cFlag = 0;
				}else{
					cFlag = 1;
				}
			} 
			else if(command == '?') {
				//if arg is not in list of possible commands
				printf("ERROR: Process ID list syntax error\n");
				return NULL;
			}
		}
		else{
			break;
		}
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
