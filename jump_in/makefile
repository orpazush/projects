CC = g++
INC = ../design_patterns/include
LDIR = ../design_patterns/lib/libdp.so
FILES = $(wildcard *.cpp) ../design_patterns/src/logger/logger.cpp
OUT = $(wildcard *.out)
EXTRA =-g
CFLAGS =-std=c++98 -pedantic-errors -Wall -Wextra $(EXTRA) -I$(INC) -L$(LDIR)
LINKERFLAGS=-lboost_system -pthread -lboost_thread -lboost_chrono

all:
	$(CC) $(CFLAGS) $(FILES) $(LINKERFLAGS) -o jump_in.out
	# $(CC) $(CFLAGS) $(FILES) $(LINKERFLAGS) -o $(OUT)


debug:
	echo $(FILES)
	echo
	echo $(OBJ)
	echo
	echo $(OUT)

.PHONY : clean
clean :
	rm *.out *.o
