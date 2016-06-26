# Reference: https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html

CC = g++
CFLAGS  = -g -std=c++0x
#CFLAGS  = -g -Wall

all: nsp

# To create the executable file main we need the object files
# main.o, evolutive.o and hospital.o:
#
nsp:  main.o hospital.o
	$(CC) $(CFLAGS) -o nsp main.o hospital.o

# To create the object file main.o, we need the source
# files evolutive.c, and hospital.h:
#
main.o:  hospital.h
	$(CC) $(CFLAGS) -c main.cxx

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