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
#include <deque>
#include "alumno.h"

using std::string;
using std::vector;

/*
* Hash policy class for string or int keys.
*/
class HashPolicy{
  /*
  * Hash function for string keys.
  * @param clave key
  * @param t_size size of the table
  */
  static const unsigned hash(string clave, unsigned t_size) {
    unsigned long h = 5381;

    // Solo valido para strings
    for(unsigned i = 0; i < clave.size(); i++)
        h = ((h << 5) + h) + clave[i];

    return h % t_size;
  }

  /*
  * Hash function class for int keys.
  * @param clave key
  * @param t_size size of the table
  */
  static const unsigned hash(int clave, unsigned t_size) {
    unsigned long h = 5381;
    while(clave > 0) {
      h = ((h << 5) + h) + clave;
      clave = clave >> 5;
    }
    return h %t_size;
  }
};

/**
* Table of stunets with keys.
* @tparam TipoClave key data typede
* @tparam TipoDato data type of rodat
* @tparam Container iteratible container type, std::vector or std::list allowed
*/
template <typename TipoClave, typename TipoDato,
template <typename T, typename = std::allocator<T>> class Container,
typename Policy = HashPolicy>
class Tabla
{
public:
    //typedef string TipoClave;
    //typedef Alumno TipoDato;
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
    typedef Container<Celda> ListaDatos;
    vector<ListaDatos> t;
};

#endif
