TARGET = queue
CC = gcc
OBJ = $(TARGET).o $(TARGET)_test.o
LIB = ../../lib
INCLUDE = ../../include

CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I $(INCLUDE)
LDFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

$(TARGET)	: 	$(OBJ) 
	$(CC) -o $(TARGET).out $(CFLAGS) $(OBJ) -L$(LIB) -l ds


.PHONY:	clean

clean:
	rm $(OBJ)	$(TARGET).out

