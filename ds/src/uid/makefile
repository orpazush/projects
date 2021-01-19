objects = uid.o uid_test.o
sources = uid.c uid_test.c
flags =  -ansi -pedantic-errors -Wall -Wextra -g

uid : $(objects)
	gcc -o uid $(flags) $(objects)

$(objects): uid.h $(sources)
	gcc -c $(flags) $(sources)

.PHONY : clean
clean : 
	rm *.o 
