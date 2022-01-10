CC = g++

all: Project random_k

Project: Project.o
	g++ -std=c++11 -O3 -Wall -o Project Project.cpp -lm

random_k: random_k.o
	g++ -O3 -Wall -o random_k random_k.cpp -lm

clean:
	rm -f *.o LIS LICS