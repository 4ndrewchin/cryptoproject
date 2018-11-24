# makefile for cryptoproject.cpp 

all: pollards

pollards: cryptoproject.cpp
	 g++-8 -std=c++17 -g -Wall -o pollards cryptoproject.cpp

clean:
	rm -rf *.o pollards