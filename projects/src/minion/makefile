CC=g++
CPPFLAGS=-std=c++98 -pedantic-errors -Wall -Wextra -g -I $(INCLUDE) -DLOGDEBUG
LINKERFLAGS=-lboost_system -lboost_chrono
CPPFLAGS_R=-std=c++98 -pedantic-errors -Wall -Wextra -DNDEBUG
VLG=valgrind --leak-check=yes --track-origins=yes

NAME = $(notdir $(CURDIR))

TEST =../../test/
INCLUDE =../../include/
OBJ =../../obj/
BIN=../../bin/
SRC=../

MAIN=minion_test
OUT=$(MAIN).out

FOLDERS := $(wildcard $(SRC)*/)
FILES :=  $(wildcard $(SRC)*/*.cpp)
#
# dep = ../communicator/communicator.cpp ../vdr_protocol/vdr_protocol.cpp ../macro_logger/logger.cpp ../udp_socket/udp_socket.cpp

$(OUT): $(FILES) $(TEST)$(MAIN).cpp
	@echo $(FILES)
	# $(CC) $(CPPFLAGS) -o $@ $^ $(LINKERFLAGS)

# objects = $(OBJ)communicator.o $(OBJ)udp_socket.o  $(OBJ)looger.o $(OBJ)$(MAIN)_test.o $(OBJ)timer.o
# sources = demultiplexer.cpp $(NAME).cpp $(TEST)$(NAME)_test.cpp
# includes = $(INCLUDE)demultiplexer.hpp $(INCLUDE)$(NAME).hpp $(INCLUDE)logger.hpp
#
# $(BIN)$(MAIN).out: $(objects) $(includes)
# 	$(CC) $(CPPFLAGS) -o $@ $^ $(LINKERFLAGS)
#
# #$(BIN)$(NAME).out: $(objects)
# #	$(CC)  -o $@ $^
#
#
#
# $(OBJ)reactor.o:$(REACTOR)reactor.cpp $(INCLUDE)reactor.hpp
# 	$(CC) $(CPPFLAGS) -c -o $@ $<
#
# $(OBJ)demultiplexer.o:$(REACTOR)demultiplexer.cpp $(INCLUDE)demultiplexer.hpp
# 	$(CC) $(CPPFLAGS) -c -o $@ $<
#
# $(OBJ)$(MAIN)_test.o:$(TEST)$(MAIN)_test.cpp
# 	$(CC) $(CPPFLAGS) -c -o $@ $<
#
# $(OBJ)timer.o:timer.cpp $(INCLUDE)timer.hpp
# 	$(CC) $(CPPFLAGS) -c -o $@ $<
#
#
# open:
# 	gedit  $(INCLUDE)$(NAME).h $(NAME).c $(TEST)$(NAME)_test.c &
#
# run:
# 	./$(BIN)$(MAIN).out
#
# runr:
# 	./$(NAME)_R
#
# vlg:
# 	$(VLG) ./$(BIN)$(MAIN).out
#
# vlgr:
# 	$(VLG) ./$(NAME)_R
#
# gdb:
# 	cgdb $(NAME)
#
# clean:
# 	rm -v -f $(OBJ)*.o
# clean_all:
# 	rm -v -f  rm $(OBJ)*.o
# 	rm -v -f $(LIB)*.so
# 	rm -v -f $(BIN)$(NAME)
