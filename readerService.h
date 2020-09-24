////////////////////////////////////////////////////////////////////////////////
// Main File: 537.c
// This File: readerService.h
// This File Description: This file finds the current user processes in /proc and 
//			  then stores those processes in an array and returns that array
// Author:           William Hofkamp, Pranet Gowni
// Email:            hofkamp@wisc.edu, gowni@wisc.edu
// CS Login:         hofkamp, pranet
////////////////////////////////////////////////////////////////////////////////

#ifndef READER_SERVICE
#define READER_SERVICE

int isInt(char *arg);

char ** readPIDs();

#endif
