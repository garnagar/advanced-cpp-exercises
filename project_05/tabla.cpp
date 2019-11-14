
#include "tabla.h"

/**
 * Constructor of class
 * @param tam Size of table. Must be double of the number of elements.
 */
Tabla::Tabla(unsigned tam)
{
    t.resize(tam);
}

/**
 * Insert an element
 * @param clave Key of the element
 * @param valor Value to be stored
 */
void Tabla::insertar(TipoClave clave, const TipoDato & valor)
{
    unsigned i;
    i = hash(clave);
    auto it = t.begin();
    std::advance(it,i);

    (*it).push_back(Celda{clave,valor} );
}

/**
 * Search for an element
 * @param clave Key of the element
 * @param valor Value founded with key "clave"
 * @return true if element founded, false otherwise
 */
bool Tabla::buscar(TipoClave clave, TipoDato & valor)
{
    unsigned i;
    i = hash(clave);
    auto it = t.begin();
    std::advance(it,i);

    for(auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
      if((*it2).clave == clave) {
        valor = (*it2).dato;
        return true;
      }
    }

    return false;
}

/**
 * Hash function for strings
 * @param clave Key
 */
unsigned Tabla::hash(TipoClave clave) const
{
    unsigned long h = 5381;

    // Solo valido para strings
    for(unsigned i = 0; i < clave.size(); i++)
        h = ((h << 5) + h) + clave[i];

    return h % t.size();
}

/**
 * Write the hash table to a stream
 * @param sal output stream
 */
void Tabla::mostrar(std::ostream & sal) const
{
    unsigned index = 0;
    for(auto it = t.begin(); it != t.end(); ++it) {
      sal << index++ << ":";
      for(auto it2 = (*it).begin(); it2 != (*it).end(); ++it2)
          sal << (*it2).dato << " -> ";
      sal << std::endl;
    }
}
