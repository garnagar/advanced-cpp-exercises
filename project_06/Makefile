
all: lista

lista: lista.o
	 g++ -o lista -std=c++11 -Wall lista.o -O2

lista.o: lista.cpp
	 g++ -c -std=c++11 -Wall lista.cpp -O2

clean:
	 rm lista.o lista
