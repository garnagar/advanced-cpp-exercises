
all: test_tabla

test_tabla: test_tabla.o
	 g++ -o test_tabla -std=c++14 -Wall test_tabla.o alumno.o tabla_t.o -O2

test_tabla.o: test_tabla.cpp
	 g++ -c -std=c++14 -Wall test_tabla.cpp alumno.cpp tabla_t.cpp -O2

clean:
	 rm test_tabla.o alumno.o tabla_t.o test_tabla
