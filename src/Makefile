# Ecosystem Makefile

CC = gcc # C compiler
SOURCEFILES = $(wildcard *.c)
OBJECTS = $(SOURCEFILES:%.c=%.o)

.PHONY: run rm help

ecosystem : $(OBJECTS)
	@$(CC) -o $@ $^ -Wall -Wextra -pedantic -std=c99

%.o : %.c
	@$(CC) -c $< -Wall -Wextra -pedantic -std=c99

run : ecosystem
	@./$<

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
	@echo  "\trm	: Removes the build and object files\n\n"
