objects = vector.o vector_test.o
sources = vector.c vector_test.c
flags =  -ansi -pedantic-errors -Wall -Wextra -g

vector : $(objects)
	gcc -o vector $(flags) $(objects)

$(objects): vector.h $(sources)
	gcc -c $(flags) $(sources)

.PHONY : clean
clean : 
	rm *.o 
