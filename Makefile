all: main

main: evolutive.o hospital.o 
	 gcc -o main evolutive.o hospital.o

evolutive.o: evolutive.cxx evolutive.h
	 gcc -c evolutive.cxx

hospital.o: hospital.cxx hospital.h
	 gcc -c hospital.cxx

clean:
	 rm main evolutive.o hospital.o