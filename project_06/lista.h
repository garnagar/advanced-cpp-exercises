/**
 * Implementacion de una lista simplemente enlazada
 * Programación Avanzada
 * Curso 2015/2016
 *
 * @author F. Barber
 */

#ifndef _LISTA_H
#define _LISTA_H

#include<iostream>

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
public:
    Lista():ptr(nullptr) {}
    void push_front(const T &);
    void mostrar() const;
private:
    friend class ListaIterator<T>;
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

#endif
