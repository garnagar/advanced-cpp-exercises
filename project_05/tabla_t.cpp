
#include "tabla_t.h"

/**
 * Constructor of class
 * @param tam Size of table. Must be double of the number of elements.
 */
 template <typename TipoClave, typename TipoDato,
 template <typename,typename> class Container,
 typename Policy>
Tabla<TipoClave,TipoDato,Container,Policy>::Tabla(unsigned tam)
{
    t.resize(tam);
}

/**
 * Insert an element
 * @param clave Key of the element
 * @param valor Value to be stored
 */
 template <typename TipoClave, typename TipoDato,
 template <typename,typename> class Container,
 typename Policy>
void Tabla<TipoClave,TipoDato,Container,Policy>::insertar(TipoClave clave, const TipoDato & valor)
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
 template <typename TipoClave, typename TipoDato,
 template <typename,typename> class Container,
 typename Policy>
bool Tabla<TipoClave,TipoDato,Container,Policy>::buscar(TipoClave clave, TipoDato & valor)
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
 * Hash function controled by HashPolicy.
 * @param clave Key
 */
 template <typename TipoClave, typename TipoDato,
 template <typename,typename> class Container,
 typename Policy>
unsigned Tabla<TipoClave,TipoDato,Container,Policy>::hash(TipoClave clave) const
{

    return Policy::hash(clave,t.size());
}

/**
 * Write the hash table to a stream
 * @param sal output stream
 */
 template <typename TipoClave, typename TipoDato,
 template <typename,typename> class Container,
 typename Policy>
void Tabla<TipoClave,TipoDato,Container,Policy>::mostrar(std::ostream & sal) const
{
    unsigned index = 0;
    for(auto it = t.begin(); it != t.end(); ++it) {
      sal << index++ << ":";
      for(auto it2 = (*it).begin(); it2 != (*it).end(); ++it2)
          sal << (*it2).dato << " -> ";
      sal << std::endl;
    }
}
