CC = g++

all: LIS LICS random_k

LIS: LIS.o
	g++ -std=c++11 -O3 -Wall -o LIS LIS.cpp -lm

LICS: LICS.o
	g++ -std=c++11 -O3 -Wall -o LICS LICS.cpp -lm

random_k: random_k.o
	g++ -O3 -Wall -o random_k random_k.cpp -lm

clean:
	rm -f *.o LIS LICS