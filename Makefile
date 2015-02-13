CC=g++
C11=-std=c++11
FLAGSBASE= -O2 -W -Wextra -Wcast-qual -Wcast-align -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wchar-subscripts -Wcomment -Wformat -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wuninitialized -Wreorder -Wundef -Wwrite-strings -Wsign-compare -Wmissing-declarations 
NAZIBASE= $(FLAGSBASE) -pedantic -Wconversion -Wmissing-noreturn -Wold-style-cast -Weffc++ -Wall -Wunused -Wsign-conversion -Wunused -Wstrict-aliasing -Wstrict-overflow -Wconversion -Wdisabled-optimization
NAZI= $(NAZIBASE) -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wlogical-op 
CFLAGS=$(NAZI)
LDFLAGS= 
EXEC=setup B32 

NO_COLOR=\033[m\017
ERROR_COLOR=\033[0;31m
OK_COLOR=\033[0;32m
WARN_COLOR=\033[0;33m
CC_COLOR=\033[1;34m

OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)
CC_STRING=$(CC_COLOR)[CC]$(NO_COLOR)
RM_STRING=$(CC_COLOR)[RM]$(NO_COLOR)
LD_STRING=$(CC_COLOR)[LD]$(NO_COLOR)


AWK_CMD = awk '{ printf "%-30s %-10s\n",$$1, $$2; }'
PRINT_ERROR = printf "$@ $(ERROR_STRING)\n" | $(AWK_CMD) && printf "$(CMD)\n$$LOG\n" && false
PRINT_WARNING = printf "$@ $(WARN_STRING)\n" | $(AWK_CMD) && printf "$(CMD)\n$$LOG\n"
PRINT_OK = printf "$@ $(OK_STRING)\n" | $(AWK_CMD)
PRINT_CC = printf "$(CC_STRING)" | awk '{ printf "%-1s %-1s",$$1, $$2; }'
PRINT_RM = printf "$(RM_STRING)" | awk '{ printf "%-1s %-1s",$$1, $$2; }'
PRINT_LD = printf "$(LD_STRING)" | awk '{ printf "%-1s %-1s",$$1, $$2; }'
BUILD_CMD = LOG=$$($(CMD) 2>&1) ; if [ $$? -eq 1 ]; then $(PRINT_ERROR); elif [ "$$LOG" != "" ] ; then $(PRINT_WARNING); else $(PRINT_OK); fi;

SRCS := $(shell find src -name '*.c') $(shell find src -name '*.cpp')
OBJS := $(patsubst src/%.c,obj/%.o,$(patsubst src/%.cpp,obj/%.o,$(SRCS)))
DEPS := $(patsubst src/%.c,obj/%.d,$(patsubst src/%.cpp,obj/%.d,$(SRCS))) 

.PHONY: clean

all: $(EXEC)

purge: clean all

setup:
	@mkdir -p obj

obj/%.o: CMD = $(CC) $(C11) $(CFLAGS) -c $< -o $@ -MD -MT '$@' -MF '$(patsubst obj/%.o,obj/%.d,$@)'
 
obj/%.o: src/%.cpp
	@$(PRINT_CC)
	@mkdir -p $(dir $@)
	@$(BUILD_CMD)
	
B32: CMD = $(CXX) $(OBJS) $(LDFLAGS) -o $@
 
B32: $(OBJS)
	@$(PRINT_LD)
	@mkdir -p $(dir $@)
	@$(BUILD_CMD)

clean:
	@$(PRINT_RM)
	@rm -f obj/*.o
	@rm -f obj/*.d
	@rm -f B32
	@$(PRINT_OK)
	
