all: ap_l01

ap_l01: ap_l01.o
	 g++ -o ap_l01 -std=c++11 -Wall ap_l01.o

ap_l01.o: ap_l01.cpp
	 g++ -c -std=c++11 -Wall ap_l01.cpp

clean:
	 rm ap_l01.o ap_l01
