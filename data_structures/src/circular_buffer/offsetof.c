/****************************************************************************
 * 					written by : orpaz houta								*
 * 					review : yana Gorikhovski								*
 *					Last update : 14.4.20 									*
 ***************************************************************************/

#include <stdio.h> /* printf */

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT)) 

typedef struct orpaz 
{ 
	int o; 
	char r; 
	short p; 
	float a;
	double z;
}orpaz_t; 

int main() 
{ 
	printf("%lu %lu %lu %lu %lu\n", OFFSETOF(orpaz_t, o), OFFSETOF(orpaz_t, r),
			OFFSETOF(orpaz_t, p), OFFSETOF(orpaz_t, a), OFFSETOF(orpaz_t, z)); 
		
	return 0; 
} 

