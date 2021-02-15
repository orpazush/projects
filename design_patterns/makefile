CC = g++
IDIR = include
LDIR = lib
TDIR = test
ODIR = obj
SRC = src
MKDIR_P = mkdir -p

LDFLAGS = -shared -fPIC
EXTRA = -g
CFLAGS =-std=c++98 -pedantic-errors -Wall -Wextra $(EXTRA) -I$(IDIR) -L$(LDIR)
LINKERFLAGS=-pthread -lboost_thread -lboost_system -lboost_chrono

FILES := $(wildcard $(SRC)/*)
TESTS := $(wildcard $(SRC)/*/*_test.cpp)
FILES := $(patsubst %.cpp, %, $(FILES))
SRCDIR = $(wildcard $(SRC)/*/*.hpp)
FILES := $(notdir $(FILES))
# FILES := $(patsubst %.cpp, %, $(FILES))
DIRS = $(wildcard $(SRC)/*)

VPATH := $(subst $(space),:, $(DIRS))

OBJ = $(patsubst %, obj/%.o, $(FILES))
# TESTS = $(patsubst %, test/%_test.out, $(TESTSFILES))
SYM_L := $(patsubst %, ../%, $(SRCDIR))
INC = $(patsubst %, include/%.hpp, $(FILES))

all: $(LDIR)/libdp.so tests

links: | $(IDIR)
	ln -st $(IDIR) $(SYM_L)

tests: $(TESTS) | $(LDIR)/libdp.so
#
# test/%.out: %.o | $(TDIR)
# 	# $(CC) -o $@  $(CFLAGS) $< -Wl,-rpath=../$(LDIR) -lds -lm $(LINKERFLAGS)
# 	$(CC) $(CFLAGS) $^ $(FILES) $(LINKERFLAGS)


$(LDIR)/libdp.so: $(OBJ) | $(LDIR)
	$(CC) $(CFLAGS)  $^ -o $@ $(LDFLAGS) -lm $(LINKERFLAGS)

obj/%.o: %.cpp %.hpp | $(ODIR)
	$(CC) -c -o $@ $(LDFLAGS) $(CFLAGS) $<

$(LDIR):
	$(MKDIR_P) $@

$(IDIR):
	$(MKDIR_P) $@

$(ODIR):
	$(MKDIR_P) $@

$(TDIR):
	$(MKDIR_P) $@


debug:
	echo $(TESTS)
	echo
	echo
	echo $(DIRS)
	echo
	echo
	echo $(VPATH)

.PHONY : clean_all all tests clean_obj links
clean :
	rm $(TDIR)/*.out $(LDIR)/*.so $(ODIR)/*.o *.o *.out

clean_obj :
	rm *.o

clean_all :
	rm -r $(IDIR) $(TDIR) $(LDIR) $(ODIR)
