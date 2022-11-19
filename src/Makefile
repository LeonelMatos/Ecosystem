# Ecosystem Makefile

CC = gcc # C compiler
SOURCEFILES = $(wildcard *.c)
OBJECTS = $(SOURCEFILES:%.c=%.o)

.PHONY: run, rm

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
