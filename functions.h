#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

char*	getEnvVal(char*);
char*	readLine(int);
char*	parseLine(char*);
int		firstChar(char, int, int);
int		isValidFirstChar(char);
int		isValidChar(char);
char*	extract(char*, int, int);

/**
 * String Functions
 */
char*	stringCopy(char*);
int 	stringLength(char*);

#endif
