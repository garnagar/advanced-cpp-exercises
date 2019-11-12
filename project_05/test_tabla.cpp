#include <iostream>
#include <string>
#include "tabla.h"
#include "alumno.h"

#define NUM_SUTDENTS 200

using namespace std;

void printStudentByKey(Tabla table, string key) {
  Alumno searchedStudent;
  if(table.buscar(key, searchedStudent)) {
    cout << searchedStudent << '\n';
  }
  else cout << "Student does not exist" << '\n';
}

int main() {
  Tabla table(NUM_SUTDENTS);
  for(int i = 0; i < NUM_SUTDENTS; ++i) {
    table.insertar(to_string(i),Alumno(i));
  }
  printStudentByKey(table,"100");
  printStudentByKey(table,"200");

  return 0;
}
