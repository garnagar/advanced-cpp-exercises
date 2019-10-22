/**
* Project: Advanced Programming Lab Excercise 02
* Authors: Lukas Kyzlik and Matej Sojak
* Date: 17/10/2019
*/

#include <iostream>
#include <time.h>
#include <vector>
#include <array>
#include <list>
#include <string>
#include <random>
#include <algorithm>

#define TESTS 10000

using namespace std;

/**
* Prints elements of vector.
* @param vec vector to be printed
*/
void dispVector(vector<int> &vec) {
  for(auto &e:vec) {
    cout << e << ", ";
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
* Fills given vector with random inteagers in the range.
* @param v vector
* @param min minmum of the range
* @param max maximum of the range
* @param gen random generator
*/
void generateVector(vector<int> &v, int min, int max, mt19937 &gen) {
  uniform_int_distribution<int> dist(min,max);
  for(auto &e:v) {
    e = dist(gen);
  }
}

/**
* Fills given list with random inteagers in the range.
* @param l list
* @param min minmum of the range
* @param max maximum of the range
* @param gen random generator
*/
void generateList(list<int> &l, int min, int max, mt19937 &gen) {
  uniform_int_distribution<int> dist(min,max);
  list<int>::iterator it;
  for(it = l.begin(); it != l.end(); ++it) {
    (*it) = dist(gen);
  }
}

/**
* Starts or restarts the time counter.
* @param time time counter variable
*/
void startClock(timespec &time) {
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);
}

/**
* Gets current time. Does not reset the time counter.
* @param time time counter variable
* @return Time since the start of the time counter in ms.
*/
double getTimeMs(timespec &time) {
  timespec curr_time;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &curr_time);
  double t = (curr_time.tv_sec-time.tv_sec)*1000;
  t += (double)(curr_time.tv_nsec-time.tv_nsec)/1000000;
  return t;
}

/**
* Finds order of given hexadecimal number. (0x1 = order 1, 0x10 = order 2 etc.)
* @param num number
* @return Order of the number.
*/
int hexOrder(int num) {
  if(num == 0) return 1;
  if(num < 0) num = -num;
  int ord = 0;
  while (num > 0) {
    num >>= 4;
    ord++;
  }
  return ord;
}

/**
* Finds digit of hexadecimal number on specified index.
* @param num number
* @param index of digit in given number (0 = 1st order etc.)
* @return Digit of given number on given index.
*/
int hexDigit(int num, int index) {
  return (num >> (4*index)) % 0x10;
}

/**
* Sorts given vector of inteagers using binary radix sort method.
* @param v vector
* @param range maximum allowed value in the vector (minmum is 0)
*/
void binRadixSortVector(vector<int> &v, int range) {
  array<vector<int>,16> bucket;
  for(int ord = 0; ord < hexOrder(range); ord++) {
    //put in buckets
    for (auto &e:v) {
      int d = hexDigit(e,ord);
      bucket.at(d).push_back(e);
    }
    //concatenate and save result of iteration
    int index = 0;
    for (int i = 0; i < 16; ++i) {
      for(auto &e:bucket.at(i)) {
        v.at(index) = e;
        index++;
      }
      bucket.at(i).clear();
    }
  }
}

/**
* Sorts given list of inteagers using binary radix sort method.
* @param l list
* @param range maximum allowed value in the vector (minmum is 0)
*/
void binRadixSortList(list<int> &l, int range) {
  array<vector<int>,16> bucket;
  for(int ord = 0; ord < hexOrder(range); ord++) {
    //put in buckets
    list<int>::iterator it;
    for (it = l.begin(); it != l.end(); ++it) {
      int d = hexDigit(*it,ord);
      bucket.at(d).push_back(*it);
    }
    //concatenate and save result of iteration
    it = l.begin();
    for (int i = 0; i < 16; ++i) {
      for(auto &e:bucket.at(i)) {
        (*it) = e;
        it++;
      }
      bucket.at(i).clear();
    }
  }
}

/**
* Optimised version of countSort. Sorts given vector of inteagers using count sort method.
* @param v vector
* @param range maximum allowed value in the vector (minmum is 0)
*/
void countSort2(vector<int> &v, int range) {
  vector<int> c(range+1);
  vector<int> v2(v.size());
  //histogram
  for(auto &e:v) {
    ++c.at(e);
  }
  //count starting idexses of element ids
  if(range%2 == 0) {
    for(int i = 2; i < range+1; i += 2) {
      c.at(i-1) = c.at(i-1)+c.at(i-2);
      c.at(i) = c.at(i)+c.at(i-1);
    }
  } else {
    c.at(0) = c.at(0)+c.at(1);
    for(int i = 3; i < range+1; i += 2) {
      c.at(i-1) = c.at(i-1)+c.at(i-2);
      c.at(i) = c.at(i)+c.at(i-1);
    }
  }

  //construct sorted vector
  for(auto &e:v) {
    v2.at(c.at(e)-1) = e; //-1 corrects for indexing from 0
    --c.at(e);
  }

  v = v2;
}


void stlVectorSortTest(int size, int range, int tests, mt19937 &gen, timespec &time) {
  vector<int> randVect(size);
  generateVector(randVect,0,range,gen);

  double timeSum = 0;
  for(int i = 0; i < tests; ++i) {
    vector<int> c = randVect;
    startClock(time);
    //CODE TO BE TEMPORALY TESTED
    sort(c.begin(),c.end());
    //END
    timeSum += getTimeMs(time);
  }
  cout << "time (ms): " <<  timeSum / TESTS << '\n';
}

void stlListSortTest(int size, int range, int tests, mt19937 &gen, timespec &time) {
  list<int> randList(size);
  generateList(randList,0,range,gen);

  double timeSum = 0;
  for(int i = 0; i < tests; ++i) {
    list<int> c = randList;
    startClock(time);
    //CODE TO BE TEMPORALY TESTED
    c.sort();
    //END
    timeSum += getTimeMs(time);
  }
  cout << "time (ms): " <<  timeSum / TESTS << '\n';
}

void binRadixSortListTest(int size, int range, int tests, mt19937 &gen, timespec &time) {
  list<int> randList(size);
  generateList(randList,0,range,gen);

  double timeSum = 0;
  for(int i = 0; i < tests; ++i) {
    list<int> c = randList;
    startClock(time);
    //CODE TO BE TEMPORALY TESTED
    binRadixSortList(c,range);
    //END
    timeSum += getTimeMs(time);
  }
  cout << "time (ms): " <<  timeSum / TESTS << '\n';
}

void countSortTest(int size, int range, int tests, mt19937 &gen, timespec &time) {
  vector<int> randVect(size);
  generateVector(randVect,0,range,gen);

  double timeSum = 0;
  for(int i = 0; i < tests; ++i) {
    vector<int> c = randVect;
    startClock(time);
    //CODE TO BE TEMPORALY TESTED
    countSort2(c,range);
    //END
    timeSum += getTimeMs(time);
  }
  cout << "time (ms): " <<  timeSum / TESTS << '\n';
}

void binRadixSortVectorTest(int size, int range, int tests, mt19937 &gen, timespec &time) {
  vector<int> randVect(size);
  generateVector(randVect,0,range,gen);

  double timeSum = 0;
  for(int i = 0; i < tests; ++i) {
    vector<int> c = randVect;
    startClock(time);
    //CODE TO BE TEMPORALY TESTED
    binRadixSortVector(c,range);
    //END
    timeSum += getTimeMs(time);
  }
  cout << "time (ms): " <<  timeSum / TESTS << '\n';
}


int main() {
  //Variables
  mt19937 gen(123); //init random generator
  timespec time;

  cout << "---Count Sort vector sort" << '\n';

  cout << "--range: [0..255]" << '\n';

  cout << "-size: 1,000" << '\n';
  countSortTest(1000,255,TESTS,gen,time);
  cout << "-size: 10,000" << '\n';
  countSortTest(10000,255,TESTS,gen,time);
  cout << "-size: 100,000" << '\n';
  countSortTest(100000,255,TESTS,gen,time);

  cout << "--range: [0..65535]" << '\n';

  cout << "-size: 1,000" << '\n';
  countSortTest(1000,65535,TESTS,gen,time);
  cout << "-size: 10,000" << '\n';
  countSortTest(10000,65535,TESTS,gen,time);
  cout << "-size: 100,000" << '\n';
  countSortTest(100000,65535,TESTS,gen,time);


  cout << "---Binary Radix Sort vector sort" << '\n';

  cout << "--range: [0..255]" << '\n';

  cout << "-size: 1,000" << '\n';
  binRadixSortVectorTest(1000,255,TESTS,gen,time);
  cout << "-size: 10,000" << '\n';
  binRadixSortVectorTest(10000,255,TESTS,gen,time);
  cout << "-size: 100,000" << '\n';
  binRadixSortVectorTest(100000,255,TESTS,gen,time);

  cout << "--range: [0..65535]" << '\n';

  cout << "-size: 1,000" << '\n';
  binRadixSortVectorTest(1000,65535,TESTS,gen,time);
  cout << "-size: 10,000" << '\n';
  binRadixSortVectorTest(10000,65535,TESTS,gen,time);
  cout << "-size: 100,000" << '\n';
  binRadixSortVectorTest(100000,65535,TESTS,gen,time);

  cout << "---Binary Radix Sort list sort" << '\n';

  cout << "--range: [0..255]" << '\n';

  cout << "-size: 1,000" << '\n';
  binRadixSortListTest(1000,255,TESTS,gen,time);
  cout << "-size: 10,000" << '\n';
  binRadixSortListTest(10000,255,TESTS,gen,time);
  cout << "-size: 100,000" << '\n';
  binRadixSortListTest(100000,255,TESTS,gen,time);

  cout << "--range: [0..65535]" << '\n';

  cout << "-size: 1,000" << '\n';
  binRadixSortListTest(1000,65535,TESTS,gen,time);
  cout << "-size: 10,000" << '\n';
  binRadixSortListTest(10000,65535,TESTS,gen,time);
  cout << "-size: 100,000" << '\n';
  binRadixSortListTest(100000,65535,TESTS,gen,time);


  cout << "---STL vector sort" << '\n';

  cout << "--range: [0..255]" << '\n';

  cout << "-size: 1,000" << '\n';
  stlVectorSortTest(1000,255,TESTS,gen,time);
  cout << "-size: 10,000" << '\n';
  stlVectorSortTest(10000,255,TESTS,gen,time);
  cout << "-size: 100,000" << '\n';
  stlVectorSortTest(100000,255,TESTS,gen,time);

  cout << "--range: [0..65535]" << '\n';

  cout << "-size: 1,000" << '\n';
  stlVectorSortTest(1000,65535,TESTS,gen,time);
  cout << "-size: 10,000" << '\n';
  stlVectorSortTest(10000,65535,TESTS,gen,time);
  cout << "-size: 100,000" << '\n';
  stlVectorSortTest(100000,65535,TESTS,gen,time);


  cout << "---STL list sort" << '\n';

  cout << "--range: [0..255]" << '\n';

  cout << "-size: 1,000" << '\n';
  stlListSortTest(1000,255,TESTS,gen,time);
  cout << "-size: 10,000" << '\n';
  stlListSortTest(10000,255,TESTS,gen,time);
  cout << "-size: 100,000" << '\n';
  stlListSortTest(100000,255,TESTS,gen,time);

  cout << "--range: [0..65535]" << '\n';

  cout << "-size: 1,000" << '\n';
  stlListSortTest(1000,65535,TESTS,gen,time);
  cout << "-size: 10,000" << '\n';
  stlListSortTest(10000,65535,TESTS,gen,time);
  cout << "-size: 100,000" << '\n';
  stlListSortTest(100000,65535,TESTS,gen,time);


  return 0;
}
