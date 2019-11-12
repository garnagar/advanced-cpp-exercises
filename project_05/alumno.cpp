/**
 * Implementación de la clase Alumno
 * Curso 2019/2020
 */

#include "alumno.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

// Nombres de ejemplo
string Alumno::list_nombre[] = {
"Javier",
"Jorge",
"Angel",
"Raul",
"José",
"Iñigo",
"Jose Antonio",
"Julio",
"Beatriz",
"Ismael",
"Oliver",
"Carlos",
"Alberto",
"Francisco Manuel",
"Lluís Carles"  };

// Apellidos de ejemplo
string Alumno::list_apellido[] = {
        "Albaladejo" ,
    "Albiach" ,
    "Aldana" ,
    "Alonso" ,
    "Anda" ,
    "Andres" ,
    "Angel" ,
    "Aranda" ,
    "Bernal" ,
    "Bonell" ,
    "Calderon" ,
    "Chakkour" ,
    "Contreras" ,
    "Correa" ,
    "Dacasa" };


/**
 * Constructor Alumno.
 * It generates a student with random data except the course, which is passed as a parameter.
 * @param curs course
 */
Alumno::Alumno(unsigned curs): curso(curs)
{
    unsigned num = rand() % 100000000;
    dni = to_string(num);
    dni.push_back( rand() % ('Z'-'A'+1) + 'A' ); // A 65, Z 90
    nombre = list_nombre[ rand() % NUM_NOMBRE];
    apellidos = list_apellido[ rand() % NUM_NOMBRE];
    telefono = rand() % 100000000 + 600000000;
}

/**
 * Writes the student in an output stream.
 * @param out output stream
 * @param alu student
 */
ostream & operator<<(ostream & out, const Alumno & alu)
{
    const string tab = "    ";
    out << "==================================" << endl;
    out << tab << "DNI: " << alu.dni << endl;
    out << tab << "Nombre: " << alu.nombre << tab << alu.apellidos << endl;;
    out << tab << "Curso: " << alu.curso;
    out << tab << "Teléfono: " << alu.telefono << endl;
    out << "==================================" << endl;
    return out;
}
