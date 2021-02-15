CC = gcc
INC = ../../ds/include
LIB = .
EXTRA =-g
CFLAGS =-ansi -pedantic-errors -Wall -Wextra $(EXTRA) -I $(INC) -L $(LIB)
LDFLAGS = -shared -fPIC

space :=

FILES = dllist pqueue scheduler sorted_list task uid\
		heap heap_pq heap_scheduler vector

VPATH := $(subst $(space),:,$(shell find ../../ds/src -type d))
ODIR = $(patsubst %, ../../ds/obj/%.o, $(FILES))

all: watchdog.out wd_test.out

watchdog.out: watchdog.o libwd.so
	$(CC) watchdog.o -o $@ $(CFLAGS) -Wl,-rpath=$(LIB) -lwd -lpthread

wd_test.out: wd_test.o libwd.so
	$(CC) wd_test.o -o $@ $(CFLAGS) -Wl,-rpath=$(LIB) -lwd -lpthread

libwd.so: $(ODIR) wd_api.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(ODIR) wd_api.o

wd_api.o: wd_api.c
	$(CC) wd_api.c -c $(LDFLAGS) $(CFLAGS) 

.PHONY : clean
clean :
	rm *.out *.o *.so
