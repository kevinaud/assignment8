#include "functions.h"

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
				printf("VAR: %s\n\n", var);
				char* val;
				val = getEnvVal(var);
				printf("VAL: %s\n\n", val);
				char* str1;
				str1 = getSubString(line, 0, begin - 1);
				char* half;
				half = concatString(str1, val);
				char* str3;
				str3 = getSubString(line, end + 1, (stringLength(line) - 1));
				char* parsed;
				parsed = concatString(half, str3);
				printf("%s\n", parsed);
				line = parsed;
			}
		}
		begin = findDollarSign(line, begin + 1);
	}
	return "temp";
}

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

int	getVarLength(char* line, int startFrom){
	int len;
	for(len = 0; (len + startFrom) < stringLength(line); len++)
	{
		if(line[startFrom + len] == ' ')
			break;
	}
	return len;
}

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


















