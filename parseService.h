////////////////////////////////////////////////////////////////////////////////
// Main File: main.c
// This File: parseService.h
// This File Description: This file is the interface for the command line parser
//			                  which takes in the command line args and sets flags 
//                        based on which commands are or aren't present
// Author:           William Hofkamp, Pranet Gowni
// Email:            hofkamp@wisc.edu, gowni@wisc.edu
// CS Login:         hofkamp, pranet
////////////////////////////////////////////////////////////////////////////////

#ifndef PARSE_SERVICE
#define PARSE_SERVICE

// to keep track of the selected options and the process id
typedef struct{
  int pFlag;
  int lSFlag;
  int uFlag;
  int uSFlag;
  int vFlag;
  int cFlag;
  char *pID;
} cmdLineArgs;

cmdLineArgs* parse(int argc, char *argv[]);

#endif
