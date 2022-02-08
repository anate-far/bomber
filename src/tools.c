#include <stdio.h>
#include <stdlib.h>

#include "tools.h"


int string_to_int(char* str)
{
	int result = 0, i;

	for(i = 0; str[i] != '\0'; i ++)
	{
		result *= 10; 
		result += str[i] - 48;


	}	

	return result; 
}

int char_to_int(char c)
{	
	int result = 0;

	result += c - 48;


	return result;
}

int str_len(char* str)
{
	int result = 0;
	int i;

	for (i = 0; str[i] != '\0';i++)
		result ++;

	return result;
}

void str_copy(char* str, char* str_copy)
{
	int i;
	for(i =  0; str_copy[i] != '\0'; i++)
		str[i] = str_copy[i];
}


