all: sort_test2 sort_stl

sort_test2: sort_test2.o
	 g++ -o sort_test2 -std=c++11 -Wall -O2 sort_test2.o

sort_test2.o: sort_test2.cpp
	 g++ -c -std=c++11 -Wall -O2 sort_test2.cpp

sort_stl: sort_stl.o
	 	g++ -o sort_stl -std=c++11 -Wall -O2 sort_stl.o

sort_stl.o: sort_stl.cpp
	 	g++ -c -std=c++11 -Wall -O2 sort_stl.cpp

clean:
	 rm sort_test2.o sort_test2 sort_stl.o sort_stl
