objects = fsa.o fsa_test.o
sources = fsa.c fsa_test.c
flags =  -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

fsa : $(objects)
	gcc -o fsa $(flags) $(objects)

$(objects): fsa.h $(sources)
	gcc -c $(flags) $(sources)

.PHONY : clean
clean : 
	rm *.o 
