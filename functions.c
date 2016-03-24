#include "functions.h"

/*char* parseLine(char* unparsed)
{
	char* parsed;
	parsed = stringCopy(unparsed);
	int len;
	len = stringLength(unparsed);
	int begin;
	begin = 0;
	int end;
	end = 0;
	int readingEnvVar;
	readingEnvVar = 0;
	int validEnvVar;
	validEnvVar = 0;
	char* envVar;

	int i;
	for(i = 0; i < len; i++){
		if(readingEnvVar == 1){
			if(isFirstChar(begin, end)){
				if(!isValidFirstChar(unparsed[i]))
					validEnvVar = 0;
				else
					end++;
			}	
			else if(!isValidChar(unparsed[i])){
				if(validEnvVar == 1){
					if((int)unparsed[i] == 32){
						envVar = extract(unparsed, begin, end);
						return getEnvVal(envVar);	
					}
				}
			}
			else if(i == len - 1){
				if(validEnvVar == 1){
					end++;
					envVar = extract(unparsed, begin, end);
					return getEnvVal(envVar);	
				}
			}
			else
				end++;
		}
		else if(unparsed[i] == '$'){
			if(i > 0){
				if(unparsed[i - 1] == 32){
					readingEnvVar = 1;
					validEnvVar = 1;
					begin = i;
					end = i;
				}
			}
			else if(i == 0){
				readingEnvVar = 1;
				validEnvVar = 1;
				begin = i;
				end = i;
			}
		}	
	}
	
	return parsed;	
}*/

char* extract(char* unparsed, int begin, int end)
{
	char* section;
	section = malloc(sizeof(char) * (end - begin + 1));
	int i;
	for(i = 0; i <= (end - begin - 1); i++)
	{
		section[i] = unparsed[begin + i + 1]; 
	}
	section[end - begin] = '\0';
	return section;
}

int isFirstChar(int begin, int end)
{
	return begin == end;
}

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



















