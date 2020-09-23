  
////////////////////////////////////////////////////////////////////////////////
// Main File: main.c
// This File: main.c
// This File Description: This file is the main file that calls the services to
//						  parse arguments, set options, and print process info
// Author:           William Hofkamp, Pranet Gowni
// Email:            hofkamp@wisc.edu, gowni@wisc.edu
// CS Login:         hofkamp, pranet
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "parseService.h"
#include "printService.h"

// the main function of the program that will utilize other modules
// for parsing the input, finding valid ppids, and printing out
// the relevant information
int main(int argc, char *argv[]){
	//parse the command line args
	cmdLineArgs *args = parse(argc,argv);
	if(args == NULL){
		// null error, command line args weren't loaded correctly
		return -1;
	}
	printProcesses(args);
}
