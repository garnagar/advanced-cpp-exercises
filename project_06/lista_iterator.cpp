#include "lista.h"

template<typename ValueType>
class ListaIterator {
        //typedef ListaIterator self_type;
        //typedef Node& reference;
        //typedef Node* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;
        ListaIterator(PtrNodo pointer) : ptr_(pointer) {
        }
        ListaIterator operator++() {
                ptr_ = ptr_->sig;
                return *this;
        }
        ListaIterator operator++(int junk) {
                ListaIterator i = *this;
                ptr_ = ptr_->sig;
                return i;
        }
        Nodo& operator*() {
                return ptr_;
        }
        ValueType operator->() {
                return ptr->valor;
        }
        bool operator==(const ListaIterator& rhs) {
                return ptr_ == rhs.ptr_;
        }
        bool operator!=(const ListaIterator& rhs) {
                return ptr_ != rhs.ptr_;
        }
        private:
        PtrNodo ptr_;
};

template<typename T>
ListaIterator<T> Lista<T>::begin()
{
    return ListaIterator<T>(ptr);
}

template<typename T>
ListaIterator<T> Lista<T>::end()
{
    return ListaIterator<T>(nullptr);
}
