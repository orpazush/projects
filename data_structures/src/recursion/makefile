CC = gcc
INC = ../../include
FILES = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(FILES))
TEST := $(wildcard *_test.c)
OUT = $(patsubst %_test.c, %.out, $(TEST))
HEADER = $(patsubst %_test.c, %.h, $(TEST))
LIB = ../../lib
EXTRA =-g
CFLAGS =-ansi -pedantic-errors -Wall -Wextra $(EXTRA) -I$(INC) -L$(LIB)

all: $(OUT)

$(OUT): $(OBJ) $(INC)/ca_test_util.h
	$(CC) -o $@ $(CFLAGS) $(FILES) -Wl,-rpath=$(LIB) -lds

%.o: %.c $(HEADER)

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
