CC=g++
C11= -std=c++11
FLAGSBASE= -O2 -W -Wextra -Wcast-qual -Wcast-align -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wchar-subscripts -Wcomment -Wformat -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wuninitialized -Wreorder -Wundef -Wwrite-strings -Wsign-compare -Wmissing-declarations 
NAZIBASE= $(FLAGSBASE) -pedantic -Wconversion -Wmissing-noreturn -Wold-style-cast -Weffc++ -Wall -Wunused -Wsign-conversion -Wunused -Wstrict-aliasing -Wstrict-overflow -Wconversion -Wdisabled-optimization
ifeq ($(CC), g++)
    NAZI= $(NAZIBASE) -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wlogical-op -Wunsafe-loop-optimizations
else
    NAZI=$(NAZIBASE)
endif
CFLAGS=$(NAZI)
LDFLAGS= 
EXEC=setup B32

all: $(EXEC) 

debug: CFLAGS = $(NAZI) -D DEBUG -g
debug: FLAGSBASE = -O2 -W -Wextra -Wcast-qual -Wcast-align -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wchar-subscripts -Wcomment -Wformat -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wuninitialized -Wreorder -Wundef -Wshadow -Wwrite-strings -Wsign-compare -Wmissing-declarations -D DEBUG -g
debug: $(EXEC)

purge: clean all

setup:
	mkdir -p obj

B32: obj/main.o
	$(CC) -o $@ $^ $(LDFLAGS)

obj/main.o: main.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

clean:
	rm -f obj/*.o
