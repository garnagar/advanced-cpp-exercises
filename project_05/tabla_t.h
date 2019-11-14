/**
 * Implementation of a hash table
 *
 */
#ifndef _TABLA_T_H
#define _TABLA_T_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "alumno.h"

using std::string;
using std::vector;

/**
* Table of stunets with keys.
* @tparam TipoClave key data typede
* @tparam TipoDato data type of rodat
* @tparam C iteratible container type, std::vector or std::list allowed
*/
template <typename TipoClave, typename TipoDato, template <typename,typename = > class C>
class Tabla
{
public:
    // typedef string TipoClave;
    // typedef Alumno TipoDato;
    struct Celda {
        TipoClave clave;
        TipoDato dato;
    };

    Tabla(unsigned);
    bool buscar(TipoClave, TipoDato&) ;
    void insertar(TipoClave, const TipoDato&);
    unsigned hash(TipoClave) const;
    void mostrar(std::ostream & sal) const;

private:
    typedef C<Celda> ListaDatos;
    vector<ListaDatos> t;
};

#endif
