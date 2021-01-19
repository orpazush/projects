
NAME = vsa
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I ../../ds/include
CC = gcc

all : $(NAME).out

$(NAME).out : $(NAME).o $(NAME)_test.o $(NAME).h 
		$(CC) -o $(NAME).out $(CFLAGS) $(NAME).o $(NAME)_test.o 

$(NAME).o : $(NAME).c $(NAME).h 
		$(CC) -c $(CFLAGS) $(NAME).c

$(NAME)_test.o : $(NAME)_test.c $(NAME).h 
		$(CC) -c $(CFLAGS) $(NAME)_test.c

.PHONY : clean

clean: 
	rm $(OBJ) 
