objects = circular_buffer.o circular_buffer_test.o
sources = circular_buffer.c circular_buffer_test.c
flags =  -ansi -pedantic-errors -Wall -Wextra -g

circular_buffer : $(objects)
	gcc -o circular_buffer $(flags) $(objects)

$(objects): circular_buffer.h $(sources)
	gcc -c $(flags) $(sources)

.PHONY : clean
clean : 
	rm *.o 
