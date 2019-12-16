/* -*- C++ -*- */

#ifndef _SARRAY2_H
#define _SARRAY2_H

#include "expresion.h"

using std::pow;

template<typename T>
class SArray2
{
  T*     storage;       // storage of the elements
  size_t storage_size;  // number of elements

public:
  // create array with initial size
  explicit SArray2 (size_t s)
  : storage(new T[s]), storage_size(s) {
    init();
  }

  // copy constructor
  SArray2 (SArray2<T> const& orig)
  : storage(new T[orig.size()]), storage_size(orig.size()) {
    copy(orig);
  }
  ~SArray2() {
        delete[] storage;
    }

    SArray2<T>& operator= (SArray2<T> const& orig) {
        if (&orig != this) {
            copy(orig);
        }
        return *this;
    }

    size_t size() const {
        return storage_size;
    }

    T operator[] (size_t idx) const {
        return storage[idx];
    }
    T& operator[] (size_t idx) {
        return storage[idx];
    }
protected:
    // init values with default constructor
    void init() {
        for (size_t idx = 0; idx<size(); ++idx) {
            storage[idx] = T();
        }
    }

    // copy values of another array
    void copy (SArray2<T> const& orig) {
        assert(size() == orig.size());
        for (size_t idx = 0; idx<size(); ++idx) {
            storage[idx] = orig.storage[idx];
        }
    }
};

// function template for the + operator for two vectors
template<typename T>
SArray2<T> operator+ (const SArray2<T>& a, const SArray2<T>& b){
  SArray2<T> result(a.size());
  for (std::size_t s= 0; s <= a.size(); ++s){
    result[s]= a[s]+b[s];
  }
  return result;
}

// function template for the + operator for a vector and a scalar
template<typename T>
SArray2<T> operator+ (const SArray2<T>& a, const T& b){
  SArray2<T> result(a.size());
  for (std::size_t s= 0; s <= a.size(); ++s){
    result[s]= a[s]+b;
  }
  return result;
}

// function template for the * operator for two vectors
template<typename T>
SArray2<T> operator* (const SArray2<T>& a, const SArray2<T>& b){
   SArray2<T> result(a.size());
  for (std::size_t s= 0; s <= a.size(); ++s){
    result[s]= a[s]*b[s];
  }
  return result;
}

// function template for the * operator for a vector and a scalar
template<typename T>
SArray2<T> operator* (const SArray2<T>& a, const T& b){
   SArray2<T> result(a.size());
  for (std::size_t s= 0; s <= a.size(); ++s){
    result[s]= a[s]*b;
  }
  return result;
}

// function template for the ^ operator for a vector and a scalar
template<typename T>
SArray2<T> operator^ (const SArray2<T>& a, const T& b){
   SArray2<T> result(a.size());
  for (std::size_t s= 0; s <= a.size(); ++s){
    result[s]= pow(a[s], b);
  }
  return result;
}


#endif
