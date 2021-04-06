CC = g++
INC = .
FILES = $(wildcard *.cpp)
EXTRA =-g
CFLAGS =-std=c++98 -pedantic-errors -Wall -Wextra $(EXTRA) -I$(INC)

all:
	$(CC) $(CFLAGS) $(FILES) -o play

debug:
	echo $(FILES)
	echo
	echo $(OBJ)
	echo
	echo $(OUT)

.PHONY : clean
clean :
	rm *.out *.o
