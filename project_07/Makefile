all: main_expresion

main_expresion: main_expresion.o
	 g++ -o main_expresion -std=c++11 -Wall main_expresion.o -O2

main_expresion.o: main_expresion.cpp
	 g++ -c -std=c++11 -Wall main_expresion.cpp -O2

clean:
	 rm main_expresion.o main_expresion
