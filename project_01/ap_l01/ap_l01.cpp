/**
* Advanced Programming Lab Excercise 01
* Author: Lukas Kyzlik
* Date: 8/10/2019
*/

#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <string>
#include <random>
using namespace std;

vector<int> v(20);
vector<int> v2(20);
list<int> l(20);
list<int> l2(20);

/**
* Prints elements of vector.
* @param vec vector to be printed
*/
void dispVector(vector<int> vec) {
  for(unsigned i = 0; i < vec.size(); ++i) {
    cout << vec.at(i) << ", ";
  }
  cout << '\n';
}

/**
* Prints elements of list.
* @param l list to be printed
*/
void dispList(list<int> l) {
  list<int>::iterator it;
  for(it = l.begin(); it != l.end(); ++it) {
    cout << (*it) << ", ";
  }
  cout << '\n';
}

/**
* Finds digit of number on specified index.
* @param num number
* @param index of digit in given number (0 = 1st order etc.)
* @return Digit of given number on given index.
*/
int digit(int num, int index) {
  for (int i = 0; i < index; ++i) {
    num /= 10;
  }
  return num % 10;
}

/**
* Finds order of given number. (1 = order 1, 10 = order 2 etc.)
* @param num number
* @return Order of the number.
*/
int order(int num) {
  if(num == 0) return 1;
  if(num < 0) num = -num;
  int ord = 0;
  while (num > 0) {
    num /= 10;
    ord++;
  }
  return ord;
}
/**
* Fills given vector with random inteagers in the range.
* @param v vector
* @param min minmum of the range
* @param max maximum of the range
*/
void generateVector(vector<int> &v, int min, int max) {
  mt19937 gen(123);
  uniform_int_distribution<int> dist(min,max);
  for(unsigned i = 0; i < v.size(); ++i) {
    v.at(i) = dist(gen);
  }
}

/**
* Fills given list with random inteagers in the range.
* @param l list
* @param min minmum of the range
* @param max maximum of the range
*/
void generateList(list<int> &l, int min, int max) {
  mt19937 gen(123);
  uniform_int_distribution<int> dist(min,max);
  list<int>::iterator it;
  for(it = l.begin(); it != l.end(); ++it) {
    (*it) = dist(gen);
  }
}

/**
* Sorts given vector of inteagers using count sort method.
* @param v vector
* @param range maximum allowed value in the vector (minmum is 0)
*/
void countSort(vector<int> &v, int range) {
  vector<int> c(range+1);
  vector<int> v2(v.size());
  //histogram
  for(unsigned i = 0; i < v.size(); ++i) {
    c.at(v.at(i))++;
  }
  //count starting idexses of element ids
  for(unsigned i = 1; i < range+1; ++i) {
    c.at(i) = c.at(i)+c.at(i-1);
  }
  //construct sorted vector
  for(unsigned i = 0; i < v.size(); ++i) {
    v2.at(c.at(v.at(i))-1) = v.at(i); //-1 corrects for indexing from 0
    c.at(v.at(i))--;
  }
  v = v2;
}

/**
* Sorts given vector of inteagers using radix sort method.
* @param v vector
* @param range maximum allowed value in the vector (minmum is 0)
*/
void radixSort(vector<int> &v, int range) {
  array<vector<int>,10> bucket;
  for(int ord = 0; ord < order(range); ord++) {
    //put in buckets
    for (int i = 0; i < v.size(); ++i) {
      int d = digit(v.at(i),ord);
      bucket.at(d).push_back(v.at(i));
    }
    //concatenate and save result of iteration
    int index = 0;
    for (int i = 0; i < 10; ++i) {
      for(int j = 0; j < bucket.at(i).size(); ++j) {
        v[index] = bucket.at(i).at(j);
        index++;
      }
      bucket.at(i).clear();
    }
  }
}

/**
* Sorts given list of inteagers using radix sort method.
* @param l list
* @param range maximum allowed value in the vector (minmum is 0)
*/
void radixSortList(list<int> &l, int range) {
  array<vector<int>,10> bucket;
  for(int ord = 0; ord < order(range); ord++) {
    //put in buckets
    list<int>::iterator it;
    for (it = l.begin(); it != l.end(); ++it) {
      int d = digit(*it,ord);
      bucket.at(d).push_back(*it);
    }
    //concatenate and save result of iteration
    it = l.begin();
    for (int i = 0; i < 10; ++i) {
      for(int j = 0; j < bucket.at(i).size(); ++j) {
        (*it) = bucket.at(i).at(j);
        it++;
      }
      bucket.at(i).clear();
    }
  }
}

int main() {
  //2. Count Sort
  //sort 20 ints in range (0,255)
  dispVector(v);
  generateVector(v,0,255);
  dispVector(v);
  countSort(v,255);
  dispVector(v);
  cout << "-----\n";

  //sort 20 ints in range (0,65535)
  dispVector(v2);
  generateVector(v2,0,65535);
  dispVector(v2);
  countSort(v2,65535);
  dispVector(v2);
  cout << "-----\n";

  //3. Radix Sort
  //sort 20 ints in range (0,255)
  generateVector(v,0,255);
  dispVector(v);
  radixSort(v,255);
  dispVector(v);
  cout << "-----\n";

  //sort 20 ints in range (0,65535)
  generateVector(v2,0,65535);
  dispVector(v2);
  radixSort(v2,65535);
  dispVector(v2);
  cout << "-----\n";

  //4. Radix Sort List
  //sort 20 ints in range (0,255)
  dispList(l);
  generateList(l,0,255);
  dispList(l);
  radixSortList(l,255);
  dispList(l);
  cout << "-----\n";

  //sort 20 ints in range (0,65535)
  dispList(l2);
  generateList(l2,0,65535);
  dispList(l2);
  radixSortList(l2,65535);
  dispList(l2);
  cout << "-----\n";

  return 0;
}
