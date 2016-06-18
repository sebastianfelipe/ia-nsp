# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++
#CFLAGS  = -g -Wall
CFLAGS  = -g

all: nsp

# To create the executable file main we need the object files
# evolutive.o and hospital.o:
#

nsp:  main.o evolutive.o hospital.o
	$(CC) $(CFLAGS) -o nsp main.o evolutive.o hospital.o

# To create the object file evolutive.o, we need the source
# files evolutive.c, and hospital.h:
#
main.o:  evolutive.h hospital.h
	$(CC) $(CFLAGS) -c main.cxx

evolutive.o:  evolutive.cxx evolutive.h 
	$(CC) $(CFLAGS) -c evolutive.cxx

# To create the object file hospital.o, we need the source files
# hospital.c and hospital.h:
#
hospital.o:  hospital.cxx hospital.h 
	$(CC) $(CFLAGS) -c hospital.cxx

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) *.o *~