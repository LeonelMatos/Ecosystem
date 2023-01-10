\page makefile Makefile

Makefile Guide
---

# Introduction

Makefile has all the essentials to compile and build the project. This page will explain in detail
how each component works to give a better understanding on how to work with and how to build upon the Makefile.

# How to Run

	make

or 

	make [COMMAND]

# List of commands

Commands | Summary
:------: | :-------------------
NULL     | compiles the files from /src/
run      | execute the program after compiling it
rm       | removes the built executable and any *.o files
build    | builds on /usr/bin/ after compiling
help     | show options

## Example

	make run
---

# Make Help

> Ecosystem Makefile Helper
>
>	make [OPTION]
>
> Options:
>
>
>	NULL 	: Compiles the project
>
>	run	: Compiles and runs the project
>
>	rm	: Removes the build and object files
>
>	build	: Builds the program on \usin\ after compiling
>
>	help	: I'll leave you at that one.
>

# Variables

Variables | Value | Description
:-------: | :---: | :----------
CC        | gcc   | C project compiler
SOURCEFILES | $(wildcard *.c) | Additional code files (ex:entity.c)
OBJECTS   | $(SOURCEFILES:%.c=%.o) | Compiled SOURCEFILES


# TODO

\todo Create a profiling option
\todo Create a clean option to remove text files from profiling
