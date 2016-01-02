all: dates

dates: main.o Date.o 
	g++ main.o Date.o -o dates

main.o: main.cpp Date.h
	g++ -c main.cpp Date.h

Date.o: Date.cpp Date.h
	g++ -c Date.cpp Date.h


