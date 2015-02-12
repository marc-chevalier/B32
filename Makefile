CC=g++
C11= -std=c++11
FLAGSBASE= -O2 -W -Wextra -Wcast-qual -Wcast-align -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wchar-subscripts -Wcomment -Wformat -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wuninitialized -Wreorder -Wundef -Wwrite-strings -Wsign-compare -Wmissing-declarations 
NAZIBASE= $(FLAGSBASE) -pedantic -Wconversion -Wmissing-noreturn -Wold-style-cast -Weffc++ -Wall -Wunused -Wsign-conversion -Wunused -Wstrict-aliasing -Wstrict-overflow -Wconversion -Wdisabled-optimization
ifeq ($(CC), g++)
    NAZI= $(NAZIBASE) -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wlogical-op 
else
    NAZI=$(NAZIBASE)
endif
CFLAGS=$(NAZI)
LDFLAGS= 
EXEC=setup B32 post
SRC = $(wildcard src/*.cpp) 
OBJ = $(SRC:.cpp=.o)
OBJ := $(notdir $(OBJ))
OBJ := $(addprefix obj/, $(OBJ))

all: $(EXEC) 

debug: CFLAGS = $(NAZI) -D DEBUG -g
debug: FLAGSBASE = -O2 -W -Wextra -Wcast-qual -Wcast-align -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wchar-subscripts -Wcomment -Wformat -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wuninitialized -Wreorder -Wundef -Wshadow -Wwrite-strings -Wsign-compare -Wmissing-declarations -D DEBUG -g
debug: $(EXEC)

purge: clean all

setup:
	mkdir -p obj

post:
	mv obj/B32 B32

B32: $(OBJ)
	$(CC) -o obj/$@ $^ main.cpp $(C11) $(LDFLAGS)

obj/%.o: src/%.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

clean:
	rm -f obj/*.o
