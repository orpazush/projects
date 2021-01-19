objects = stack.o stack_test.o
sources = stack.c stack_test.c
flags =  -ansi -pedantic-errors -Wall -Wextra -g

stack : $(objects)
	gcc -o stack $(flags) $(objects)

$(objects): stack.h $(sources)
	gcc -c $(flags) $(sources)

.PHONY : clean
clean : 
	rm *.o 
