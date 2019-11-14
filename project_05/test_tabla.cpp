#include <iostream>
#include <string>
#include <list>
#include "tabla_t.h"
#include "alumno.h"

#define NUM_SUTDENTS 200

using namespace std;

void printStudentByKey(Table<string,Alumno,list> table, string key) {
  Alumno searchedStudent;
  if(table.buscar(key, searchedStudent)) {
    cout << searchedStudent << '\n';
  }
  else cout << "Student does not exist" << '\n';
}

int main() {
  Tabla table<string,Alumno,list>(NUM_SUTDENTS);
  for(int i = 0; i < NUM_SUTDENTS; ++i) {
    Alumno a(i);
    table.insertar(a.getDNI(),a);
  }
  printStudentByKey(table,"100");
  printStudentByKey(table,"200");

  table.mostrar(cout);

  return 0;
}
