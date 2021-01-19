CC = g++
INC = ../../include
FILES = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(FILES))
TEST := $(wildcard *_test.cpp)
OUT = $(patsubst %_test.cpp, %.out, $(TEST))
HEADER = $(patsubst %_test.cpp, %.hpp, $(TEST))
LIB = ../../lib
EXTRA =-g
CFLAGS =-std=c++98 -pedantic-errors -Wall -Wextra $(EXTRA) -I$(INC) 

all: $(OUT)

$(OUT): $(OBJ) $(INC)/ca_test_util.hpp
	$(CC) -o $@ $(CFLAGS) $(FILES) 

%.o: %.cpp $(HEADER)

debug:
	echo $(FILES)
	echo
	echo $(OBJ)
	echo
	echo $(TEST)
	echo
	echo $(OUT)

.PHONY : clean
clean :
	rm *.out *.o

