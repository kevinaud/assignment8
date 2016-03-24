#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

char*	getEnvVal(char*);
char*	readLine(int);
char*	parseLine(char*);
int 	findDollarSign(char*, int);
int		isValidForm(char*, int);
int		getVarLength(char*, int);
int		firstChar(char, int, int);
int		isValidFirstChar(char);
int		isValidChar(char);
char*	extract(char*, int, int);

/**
 * String Functions
 */
char*	stringCopy(char*);
int 	stringLength(char*);
char*	getSubString(char*, int, int);
char*	concatString(char*, char*);

#endif
