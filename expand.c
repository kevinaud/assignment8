/******************************************************************************
 * Filename: expand.c
 * Author Kevin Aud
 * Description:
 * 		Reads a line from standard input one line at a time and then prints 
 * 		out a copy of each input line. Environment variabel expansion is
 * 		performed on each input line before it is printed. If an environment
 * 		variable has no value, it is replaced by the empty string. Restricts
 * 		input lines to 1024 characters. If input is longer than 1023, outputs
 * 		"INPUT TOO LONG" to stderr and starts over with next line. Continues
 * 		reading until EOF.
 *
 * Dates Modified:
 * 		3/21/2016 - File created
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

#define TRUE 1
#define FALSE 0


int main(int argc, char *argv[])
{
	char* envVar;
	char* value;

	envVar = "PATH";
	value = getEnvVal(envVar);

	printf("envVar: %s\n", envVar);
	printf("value: %s\n", value);

	return 0;
}


























