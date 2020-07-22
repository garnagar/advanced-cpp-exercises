/**
* Project: Advanced Programming Lab Excercise 05
* Authors: Lukas Kyzlik and Matej Sojak
* Date: 04/12/2019
*/

#include <iostream>
#include <string>
#include <vector>
#include "tabla_t.h"
#include "alumno.h"

#define NUM_SUTDENTS 200

using namespace std;

class CustomHashPolicy{
public:
  static const unsigned hash(float clave, int t_size) {
    return (int) clave %t_size;
  }
};

void printStudentByKey(Table<string,Alumno,list,CustomHashPolicy> table, string key) {
  Alumno searchedStudent;
  if(table.buscar(key, searchedStudent)) {
    cout << searchedStudent << '\n';
  }
  else cout << "Student does not exist" << '\n';
}

int main() {
  Tabla<string,int,vector,CustomHashPolicy> table = Tabla<string,int,vector>(NUM_SUTDENTS);
  for(int i = 0; i < NUM_SUTDENTS; ++i) {
    Alumno a(i);
    table.insertar(a.getDNI(),a);
  }
  printStudentByKey(table,"100");
  printStudentByKey(table,"200");

  table.mostrar(cout);

  return 0;
}
