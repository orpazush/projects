#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Ex_1.h"

int global;
char *gtext = "global";

int main()
{
	char str[] = "hi";
	printf("%lu\n",StrLen(str));	

	char str1[] = "hello";
	char str2[] = "heoollo";
	printf("%d\n", StrCmp(str1, str2));

	char a[50] = "this is an almost ";
    	char b[50] = "success!";
    	printf("%s\n", StrCat(a, b));

	char c[50] = "this is";
    	char d[50] = " almost";
    	printf("%s\n", StrCpy(c, d));

	char e[50] = "this is ";
    	char f[50] = "almostsuccess!";
    	printf("%s\n", StrNcpy(e, f, 5));

	char str3[50] = "HeLLo";
	char str4[50] = "hellO";
	printf("%d\n", StrCaseCmp(str3, str4));

	char str5[50] = "hi to you too";
	const char ch = 'y';
	printf("%s\n",StrChr(str5, ch));	

	char g[50] = "what ";
    	char h[50] = "do you say?";
    	printf("%s\n", StrNcat(g, h, 5));

	char j[50] = "do you say?";
    	printf("%s\n", StrDup(j));
	free(StrDup(j));

	char haystack[] = "let's find it here and here";
	char needle[] = "here";
	printf("%s\n", StrStr(haystack, needle));
	free(StrStr(haystack, needle));

    	return 0;	
}

