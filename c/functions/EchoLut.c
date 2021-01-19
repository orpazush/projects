#include <stdio.h>
#include <stdlib.h>

void Esc() 
{
   system("stty icanon echo");
   
   exit(0);
 }

void PrintA()
{
	printf("A pressed\n");
}

void PrintT()
{
	printf("T pressed\n");
}

void Empty()
{
	;
}

static void (*func_ptr_arr[256])() = {[0 ... 26] = Empty, [27] = Esc ,
 [28 ... 64] =  Empty, [65] =  PrintA, [66 ... 83] =  Empty
 , [84] = PrintT, [85 ... 255] =  Empty};

int main()
{
    unsigned char key;

    system("stty -icanon -echo");
	
    printf("Please enter a letter or Esc to get out: \n");
    
    while (1)
    {
	    scanf("%c",&key);
	    
	
	    (*func_ptr_arr[key])();
     }
	
	
    return 0;
    
}
