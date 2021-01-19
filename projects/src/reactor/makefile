objects = reactor.o reactor_test.o
sources = reactor.cpp reactor_test.cpp
flags = -std=c++98 -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -Werror

reactor.out : $(objects)
	g++ -o reactor $(flags) $(objects)

$(objects): reactor.hpp $(sources)
	g++  -c $(flags) $(sources)

.PHONY : clean
clean :
	rm *.o
