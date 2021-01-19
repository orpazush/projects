INC = ../../ds/include
LIB = ../../ds/lib
CC = gcc
EXTRA =-g
CFLAGS =-ansi -pedantic-errors -Wall -Wextra $(EXTRA) -I $(INC) -L $(LIB)

all: pc1.out pc2_1.out pc2_2.out pc3_1.out pc3_2.out pc4_1.out pc4_2.out pc5.out

pc1.out: pc1.c
	$(CC) -o $@ $(CFLAGS) $^ -lpthread

pc2_1.out: pc2_1.c
	$(CC) -o $@ $(CFLAGS) $^ -Wl,-rpath=$(LIB) -lds -lpthread -lm

pc2_2.out: pc2_2.c
	$(CC) -o $@ $(CFLAGS) $^ -Wl,-rpath=$(LIB) -lds -lpthread -lm

pc3_1.out: pc3_1.c
	$(CC) -o $@ $(CFLAGS) $^ -Wl,-rpath=$(LIB) -lds -lpthread -lm

pc3_2.out: pc3_2.c
	$(CC) -o $@ $(CFLAGS) $^ -Wl,-rpath=$(LIB) -lds -lpthread -lm

pc4_1.out: pc4_1.c
	$(CC) -o $@ -std=c11 $(CFLAGS)  $^ -Wl,-rpath=$(LIB) -lds -lpthread -lm

pc4_2.out: pc4_2.c
	$(CC) -o $@ $(CFLAGS) $^ -Wl,-rpath=$(LIB) -lds -lpthread -lm

pc5.out: pc5.c
	$(CC) -o $@ $(CFLAGS) $^ -Wl,-rpath=$(LIB) -lds -lpthread -lm

.PHONY : clean
clean :
	rm *.out *.o
