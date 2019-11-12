/**
 * Clase para representar alumnos
 * Curso 2019/2020
 */

#include <iostream>
#include <string>
using namespace std;

#ifndef _ALUMNO_H_
#define _ALUMNO_H_

class Alumno
{
    string dni;
    string nombre;
    string apellidos;
    unsigned curso;
    unsigned telefono;

    static const unsigned NUM_NOMBRE = 15;
    static string list_nombre[];
    static string list_apellido[];


public:
    /**
     * Default constructor.
     * Creates empty Student.
     */
    Alumno() {};
    /**
     * Creates Student wtih a specific course and rest of the random data.
     * @param curs course of the stunet
     */
    Alumno(unsigned curs);
    /**
     * Returns the ID to use as a key.
     * @return ID of the Student.
     */
    string getDNI() const
        {return dni; };

    friend ostream & operator<<(ostream &, const Alumno &);

};

#endif
