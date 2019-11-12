
all: memcost1 memcost2

memcost1: memcost1.o
	 g++ -o memcost1 -std=c++11 -Wall memcost1.o -O2

memcost1.o: memcost1.cpp
	 g++ -c -std=c++11 -Wall memcost1.cpp -O2

memcost2: memcost2.o
	 	g++ -o memcost2 -std=c++11 -Wall memcost2.o -O2

memcost2.o: memcost2.cpp
	 	g++ -c -std=c++11 -Wall memcost2.cpp -O2

clean:
	 rm memcost1.o memcost1 memcost2.o memcost2
