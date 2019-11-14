/**
 * Implementation of a hash table
 *
 */
#ifndef _TABLA_H
#define _TABLA_H

#include <string>
#include <vector>
#include <iostream>
#include "alumno.h"

using std::string;
using std::vector;

template<typename KeyType, typename ValType>
class Tabla
{
public:
    // typedef string TipoClave;
    // typedef Alumno TipoDato;
    struct Celda {
        KeyType clave;
        ValType dato;
    };

    Tabla(unsigned);
    bool buscar(KeyType, ValType&) ;
    void insertar(KeyType, const ValType&);
    unsigned hash(KeyType) const;
    void mostrar(std::ostream & sal) const;

private:
    typedef vector<Celda> ListaDatos;
    vector<ListaDatos> t;
};

#endif
