# Ecosystem Makefile

CC = gcc # C compiler
SOURCEFILES = $(wildcard *.c)
OBJECTS = $(SOURCEFILES:%.c=%.o)
OUTPUT = profile_output.txt

.PHONY: run rm help profile clean

ecosystem : $(OBJECTS)
	@$(CC) -o $@ $^ -Wall -Wextra -pedantic -std=c99

%.o : %.c
	@$(CC) -c $< -Wall -Wextra -pedantic -std=c99

run : ecosystem
	@./$<

run1 : ecosystem
	@./$< 1

build : ecosystem
	@echo "Building ecosystem...  0%"
	@sleep 1
	@echo "Building ecosystem... 10%"
	@echo "Building ecosystem... 50%"
	@sleep 1
	@echo "Building ecosystem... 70%"
	@echo "Building ecosystem... 99%"
	@sleep 4
	@echo "Building ecosystem...100%"
	@sudo mv ecosystem /usr/bin

rm :
	@rm ecosystem
	@rm *.o
	@echo Cleaned the room

help :
	@echo "\n\n\033[1m"Ecosystem Makefile Helper"\033[0m\n"
	@echo "\tmake [COMMAND]"
	@echo "\n\033[1m"Commands:"\033[0m\n"
	@echo  "\t 	: Compiles the project"
	@echo  "\trun	: Compiles and runs the project"
	@echo  "\trm	: Removes the build and object files"
	@echo "\tprofile: Creates a .txt output file with results from profiling the program"
	@echo "\tclean	: Clears the junk files from profiling (gmon.out, *.txt)
	@echo  "\tbuild	: Builds the program on \usr\bin\ after compiling"
	@echo  "\thelp	: I'll leave you at that one.\n\n"

a.out : $(OBJECTS)
	$(CC) -pg $^

profile : a.out # Uses gprof
	./$<
	gprof $< gmon.out > $(OUTPUT)

clean :
	@rm *.out
	@rm $(OUTPUT)
	@echo Cleaned the room
