#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Ex_1.h"

size_t StrLen(const char *string)
{
	size_t length = 0;
 
	for(length = 0; string[length]; ++length);

	return length;	
}

int StrCmp(const char *string1, const char *string2)
{
	while((*string1 != '\0') && (*string2 != '\0'))
	{
		if(*string1 != *string2)
		{
			return 1;
		} 
		++string1;
		++string2;
	}

	return 0;	
}

char *StrCpy(char *dest, const char *src)
{
	int i = 0; 	
	for(i = 0; src[i]; ++i)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return dest;	
}

char *StrNcpy(char *dest, const char *src, size_t n)
{
	int i = 0;

	for(i = 0; src[i] != '\0' || i < n; ++i)
	{
		dest[i] = src[i];
	}
	dest[n] = '\0';

	return dest;	
}

int StrCaseCmp(const char *string1, const char *string2)
{
	int i = 0; 

	while((string1[i]) || (string2[i]))
	{
		if(tolower(string1[i]) != tolower(string2[i]))
		{
			return 1;		
		}
		i++;
	}

	return 0;
}

char *StrChr(const char *string, int c)
{

	while(*string != (char)c)
	{
		string++;
	}

	return (char *)string;
}

char *StrDup(const char *string)
{
	char *dup = NULL;
	size_t length = 0;
	int i = 0;

	length = StrLen(string) + 1;
	dup = (char*)malloc(sizeof(char)*length);
	
	for(i = 0; string[i]; ++i)
	{
		dup[i] = string[i];
	}
	dup[i] = '\0';

	return dup;
}

char *StrCat(char *dest, const char *src)
{
	int i = 0, j = 0;

	for(i = 0; dest[i]; ++i);

	for(j= 0; src[j]; ++j, ++i)
	{
		dest[i] = src[j];
	}
	dest[i] = '\0';

	return dest;	 
}

char *StrNcat(char *dest, const char *src, size_t n)
{

	int i = 0, j = 0;

	i = StrLen(dest);

	for(j = 0; src[j] && j < n; ++j, ++i)
	{
		dest[i] = src[j];
	}
	dest[i] = '\0';

	return dest;
}

char *StrStr(const char *haystack, const char *needle)	
{
	int i = 0;
	char *ret = NULL;

	while(*haystack != '\0')
	{
		if(*haystack == *needle)
		{
			while(haystack[i] == needle[i])
			{
				i++;
				if (needle[i] == '\0')
				{
					ret = StrDup(needle);
					return ret;
				}	
			}			
		}
		++haystack;	
	}	
	return NULL;
}

size_t strspn(const char *string1, const char *string2)
{
    size_t count = 0;

    while(*string1 && StrChr(string2,*string1++))
	{
		count++;
	}

    return count;    
}
