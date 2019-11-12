
all: test_tabla

test_tabla: test_tabla.o
	 g++ -o test_tabla -std=c++11 -Wall test_tabla.o alumno.o tabla.o -O2

test_tabla.o: test_tabla.cpp
	 g++ -c -std=c++11 -Wall test_tabla.cpp alumno.cpp tabla.cpp -O2

clean:
	 rm test_tabla.o alumno.o tabla.o test_tabla
