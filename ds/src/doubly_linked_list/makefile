objects = dllist.o dllist_test.o
sources = dllist.c dllist_test.c
flags =  -ansi -pedantic-errors -Wall -Wextra -g

dllist : $(objects)
	gcc -o dllist $(flags) $(objects)

$(objects): dllist.h $(sources)
	gcc -c $(flags) $(sources)

.PHONY : clean
clean : 
	rm *.o 
