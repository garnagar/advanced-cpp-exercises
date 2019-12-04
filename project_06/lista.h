/**
 * Implementacion de una lista simplemente enlazada
 * Programación Avanzada
 * Curso 2015/2016
 *
 * @author F. Barber
 */

#ifndef _LISTA_H
#define _LISTA_H

#include <iostream>
#include <iterator>

template<typename T>
class ListaIterator;

/**
 * Lista simplemente enlazada
 * @param T Tipo de los elementos de la lista
 */
template<typename T>
class Lista
{
    struct Nodo
    {
        T valor;
        Nodo * sig;
    };

    typedef Nodo * PtrNodo;
    PtrNodo ptr;
    friend class ListaIterator<T>;

public:
    using value_type = T;
    using iterator = ListaIterator<T>;

    Lista():ptr(nullptr) {}

    void push_front(const T &);

    void mostrar() const;

    ListaIterator<T> begin(){
      ListaIterator<T> itr(ptr);
      return itr;
    }

    ListaIterator<T> end(){
      ListaIterator<T> itr(nullptr);
      return itr;
    }
};

/**
 * Añadir elemento al inicio de la lista
 * @param x elemento a añadir
 */
template<typename T>
void Lista<T>::push_front(const T & x)
{
    PtrNodo aux = new Nodo;
    aux->valor = x;
    aux->sig = ptr;
    ptr = aux;
}

/**
 * Muestra la lista por pantalla
 */
template<typename T>
void Lista<T>::mostrar() const
{
    PtrNodo aux = ptr;

    while(aux != nullptr)
    {
        std::cout << aux->valor << " ";
        aux = aux->sig;
    }
}

/**
* Custom iterator for the Lista class
* @tparam T data stored in Lista container
*/
template<typename T>
class ListaIterator : public std::iterator<std::forward_iterator_tag, T> {
private:

  typename Lista<T>::Nodo* ptr_;

public:

  ListaIterator(){}

  ListaIterator(typename Lista<T>::Nodo* ptr) {
    ptr_ = ptr;
  }

  ListaIterator operator++() {
          ptr_ = ptr_->sig;
          return *this;
  }

  ListaIterator<T> operator++(int junk) {
          ListaIterator<T> i = *this;
          ptr_ = ptr_->sig;
          return i;
  }

  T& operator*() {
          return ptr_->valor;
  }

  bool operator==(const ListaIterator& rhs) {
          return ptr_ == rhs.ptr_;
  }

  bool operator!=(const ListaIterator& rhs) {
          return ptr_ != rhs.ptr_;
  }

};

#endif
