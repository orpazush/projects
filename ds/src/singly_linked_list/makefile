objects = sllist.o sllist_test.o
sources = sllist.c sllist_test.c
flags =  -ansi -pedantic-errors -Wall -Wextra -g

sllist : $(objects)
	gcc -o sllist $(flags) $(objects)

$(objects): sllist.h $(sources)
	gcc -c $(flags) $(sources)

.PHONY : clean
clean : 
	rm *.o 
