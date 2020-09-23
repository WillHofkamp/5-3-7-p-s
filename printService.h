////////////////////////////////////////////////////////////////////////////////
// Main File: main.c
// This File: printService.h
// This File Description: This file is the interface for the method that uses 
//                        the parsed commands with the process ID 
//			              that are both passed in and then prints them to the 
//			              screen based on what values are specified
// Author:           William Hofkamp, Pranet Gowni
// Email:            hofkamp@wisc.edu, gowni@wisc.edu
// CS Login:         hofkamp, pranet
////////////////////////////////////////////////////////////////////////////////

#ifndef PRINT_SERVICE
#define PRINT_SERVICE

int printProcess(cmdLineArgs *options, char *pID);

int printProcesses(cmdLineArgs *options);

#endif
