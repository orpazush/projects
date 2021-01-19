#include <stdio.h>	

/*data types and sizeof*/

int main()
{

	printf("the size of short int/short is:%ld\n", sizeof(short int));
  
	printf("the size of unsigned short int is:%ld\n", sizeof(unsigned short int));

	printf("the size of unsigned int is:%ld\n", sizeof(unsigned int));

	printf("the size of int is:%ld\n", sizeof(int));

	printf("the size of long int/long is:%ld\n", sizeof(long int));

	printf("the size of unsigned long int is:%ld\n", sizeof(unsigned long int));

	printf("the size of long long int is:%ld\n", sizeof(long long int));

	printf("the size of unsigned long long int is:%ld\n", sizeof(unsigned long long int));

	printf("the size of signed char/char is:%ld\n", sizeof(signed char));

	printf("the size of unsigned char is:%ld\n", sizeof(unsigned char));

	printf("the size of float is:%ld\n", sizeof(float));

	printf("the size of double is:%ld\n", sizeof(double));

	printf("the size of long double is:%ld\n", sizeof(long double));

	printf("the size of size_t is:%ld\n", sizeof(size_t));
	
	printf("the size of every pointer is:%ld\n", sizeof(char *));

    return 0;
}

