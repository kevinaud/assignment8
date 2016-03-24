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
#include <unistd.h>
#include <fcntl.h>

#define TRUE 1
#define FALSE 0

char*	getEnvVal(char*);
char*	readLine(int);
char*	parseLine(char*);
int 	findDollarSign(char*, int);
int		isValidForm(char*, int);
int		getVarLength(char*, int);
int		firstChar(char, int, int);
int		isValidFirstChar(char);
int		isValidChar(char);

/**
 * String Functions
 */
char*	stringCopy(char*);
int 	stringLength(char*);
char*	getSubString(char*, int, int);
char*	concatString(char*, char*);


int main(int argc, char *argv[])
{
	char* line;
	line = readLine(0);
	while(line != NULL){
		printf("%s\n",line);
		line = readLine(0);
		char* parsed;
		parsed = parseLine(line);
		printf("%s\n", parsed);
	}

	return 0;
}

/******************************************************************************
 * name: parseLine
 * description: does variable expansion on a line
 * params:
 * 		line 	line to be parsed
 * return:
 *		char* 	parsed line
 ******************************************************************************/
char* parseLine(char* line)
{
	int begin;
	int end;
	int varLength;
	varLength = 0;
	begin = findDollarSign(line, 0);
	while(begin != -1){
		if(isValidForm(line, begin)){
			varLength = getVarLength(line, begin);
			end = begin + varLength - 1;
			if(isValidForm(line, begin)){
				char* var;
				var = getSubString(line, begin + 1, end);
				char* val;
				val = getEnvVal(var);
				char* str1;
				str1 = getSubString(line, 0, begin - 1);
				char* half;
				half = concatString(str1, val);
				char* str3;
				str3 = getSubString(line, end + 1, (stringLength(line) - 1));
				char* parsed;
				parsed = concatString(half, str3);
				line = parsed;
			}
		}
		begin = findDollarSign(line, begin + 1);
	}
	return "temp";
}

/******************************************************************************
 * name: concatString
 * description: concatenates two strings 
 * params:
 * 		str1 	left side of concatenated string
 * 		str2	right side of concatenated string	
 * return:
 *		char* 	concatenated string	
 ******************************************************************************/
char* concatString(char* str1, char* str2){
	int len1;
	int len2;
	len1 = stringLength(str1);
	len2 = stringLength(str2);

	char* concat;
	concat = malloc(sizeof(char) * (len1 + len2 + 1));
	int i;
	for(i = 0; i < len1; i++){
		concat[i] = str1[i];
	}
	for(i = len1; i < (len1 + len2); i++){
		concat[i] = str2[i - len1];
	}
	concat[len1 + len2 + 1] = '\0';
	return concat;
}

/******************************************************************************
 * name: getSubString 
 * description: get a substring from a char*
 * params:
 * 		begin	beginning index of substring
 * 		end		ending index of substring	
 * return:
 *		char*	subString of larger string	
 ******************************************************************************/
char* getSubString(char* line, int begin, int end){
	int length;
	length = end - begin + 1;
	char* substr;
	substr = malloc(sizeof(char) * (length + 1));
	int i;
	for(i = 0; i < length; i++){
		substr[i] = line[begin + i];
	}
	substr[length] = '\0';
	return substr;
}

/******************************************************************************
 * name: isValidForm 
 * description:	given a line containing a dollar sign, and the position of the
 * 		dollar sign, checks if a valid env variable is present 
 * params:
 * 		line		char array containing dollar sign	
 * 		startFrom	index of dollar sign in character array	
 * return:
 *		int			1 if valid form, 0 if not	
 ******************************************************************************/
int	isValidForm(char* line, int startFrom){
	int valid;
	valid = 1;
	if(startFrom == (stringLength(line) - 1)){
		valid = 0;
	}
	else if (!isValidFirstChar(line[startFrom + 1])){
		valid = 0;
	}
	else {
		int i;
		for(i = startFrom + 2; i < stringLength(line); i++){
			if(line[i] == ' '){
				break;
			}
			if(!isValidChar(line[i])){
				valid = 0;
				break;
			}
		}
	}

	return valid;
}

/******************************************************************************
 * name: getVarLength 
 * description:	given a character array containing a valid form of an env var 
 * 		and the index of its starting position in the character array, gets the
 * 		length of the variable name
 * params:
 * 		line		character array containing env var	
 * 		startFrom	starting position of env var name
 * return:
 *		int			length of env var name
 ******************************************************************************/
int	getVarLength(char* line, int startFrom){
	int len;
	for(len = 0; (len + startFrom) < stringLength(line); len++)
	{
		if(line[startFrom + len] == ' ')
			break;
	}
	return len;
}

/******************************************************************************
 * name: findDollarSign 
 * description: search for '$' character in a character array 
 * params:
 * 		line	character array to search through
 * 		startAt	position in array to start searching from
 * return:
 *		int		pos of next dollar sign, or -1 if end of string is reached	
 ******************************************************************************/
int findDollarSign(char* line, int startAt){
	int len;
	len = stringLength(line);
	int i;
	int pos;
	pos = -1;
	for(i = startAt; i < len; i++)
	{
		if(line[i] == '$')
		{
			pos = i;
			break;
		}
	}
	return pos;
}

/******************************************************************************
 * name: 
 * description: 
 * params:
 * 		
 * return:
 *		
 ******************************************************************************/
int isFirstChar(int begin, int end)
{
	return begin == end;
}

/******************************************************************************
 * name: 
 * description: 
 * params:
 * 		
 * return:
 *		
 ******************************************************************************/
int isValidFirstChar(char firstChar)
{
	int isValid;
	isValid = 0;

	if((int)firstChar == 95)
	{
		isValid = 1;
	}
	else if((int)firstChar > 64 && (int)firstChar < 91)
	{
		isValid = 1;
	}
	else if((int)firstChar > 96 && (int)firstChar < 123)
	{
		isValid = 1;
	}

	return isValid;
}

/******************************************************************************
 * name: 
 * description: 
 * params:
 * 		
 * return:
 *		
 ******************************************************************************/
int isValidChar(char currentChar)
{
	int isValid;
	isValid = 0;

	if((int)currentChar == 95)
	{
		isValid = 1;
	}
	else if((int)currentChar > 64 && (int)currentChar < 91)
	{
		isValid = 1;
	}
	else if((int)currentChar > 96 && (int)currentChar < 123)
	{
		isValid = 1;
	}
	else if((int)currentChar > 47 && (int)currentChar < 58)
	{
		isValid = 1;
	}

	return isValid;
}

/******************************************************************************
 * name: 
 * description: 
 * params:
 * 		
 * return:
 *		
 ******************************************************************************/
char* readLine(int fileHandle)
{
	char* line;
	line = malloc(sizeof(char)*1024);
	char* source;
	source = "this is a test";

	char buf;
	int charCount;
	charCount = 0;
	int overCap;
	overCap = 0;
	int stopReading;
	stopReading = 0;
	while(stopReading == 0)
	{
		if(read(fileHandle, &buf, sizeof(char)) == 0)
		{
			stopReading = 1;
		}	
		else if(buf == '\n')
		{
			stopReading = 1;
		}
		else if(overCap == 0)
		{
			line[charCount] = buf; 
			charCount++;
			if(charCount >= 1023)
			{
				overCap = 1;
				free(line);
				line = NULL;
			}
		}
	}
	if(line != NULL)
		line[stringLength(source)] = '\0';

	return line;
}

/******************************************************************************
 * name: 
 * description: 
 * params:
 * 		
 * return:
 *		
 ******************************************************************************/
char* getEnvVal(char* envVar)
{
	char* value;
	value = getenv(envVar);
	if(value == NULL)
	{
		value = " ";
	}

	return value;
}

/******************************************************************************
 * name: 
 * description: 
 * params:
 * 		
 * return:
 *		
 ******************************************************************************/
char* stringCopy(char* source)
{
	char* dest;
	int sourceLen;
	sourceLen = stringLength(source);

	dest = malloc(sizeof(char) * (sourceLen + 1));

	int i;
	for(i = 0; i < sourceLen; i++)
	{
		dest[i] = source[i];
	}
	dest[sourceLen] = '\0';

	return dest;
}

/******************************************************************************
 * name: 
 * description: 
 * params:
 * 		
 * return:
 *		
 ******************************************************************************/
int stringLength(char* source)
{
	char c;
	int len;
	len = 0;
	c = source[0];

	while(c != '\0')
	{
		len++;
		c = source[len];
	}

	return len;
}


























