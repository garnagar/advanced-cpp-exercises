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

#define SIZE 10000
#define RANGE 65535
#define TESTS 1000

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
* Sorts given vector of inteagers using count sort method.
* @param v vector
* @param range maximum allowed value in the vector (minmum is 0)
*/
void countSort(vector<int> &v, int range) {
  vector<int> c(range+1);
  vector<int> v2(v.size());
  //histogram
  for(auto &e:v) {
    c.at(e)++;
  }
  //count starting idexses of element ids
  for(int i = 1; i < range+1; ++i) {
    c.at(i) = c.at(i)+c.at(i-1);
  }
  //construct sorted vector
  for(auto &e:v) {
    v2.at(c.at(e)-1) = e; //-1 corrects for indexing from 0
    c.at(e)--;
  }
  v = v2;
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
    ++c[e];
  }
  //count starting idexses of element ids
  for(int i = 1; i < range+1; ++i) {
    c[i] = c[i]+c[i-1];
  }
  //construct sorted vector
  for(auto &e:v) {
    v2[c[e]-1] = e; //-1 corrects for indexing from 0
    --c[e];
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
    for (auto &e:v) {
      int d = digit(e,ord);
      bucket.at(d).push_back(e);
    }
    //concatenate and save result of iteration
    int index = 0;
    for (int i = 0; i < 10; ++i) {
      for(auto &e:bucket.at(i)) {
        v[index] = e;
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
      for(auto &e:bucket.at(i)) {
        (*it) = e;
        it++;
      }
      bucket.at(i).clear();
    }
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
* @return Time since the start of the time counter in us.
*/
long getTime(timespec &time) {
  timespec curr_time;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &curr_time);
  long t = curr_time.tv_nsec-time.tv_nsec;
  return t;
}

int main() {
  //Variables
  mt19937 gen(123); //init random generator
  timespec time;

  //random vector
  vector<int> randVect(SIZE);
  generateVector(randVect,0,RANGE,gen);

  //test
  long long timeSum = 0;
  for(int i = 0; i < TESTS; ++i) {
    vector<int> c = randVect;
    startClock(time);
    //CODE TO BE TEMPORALY TESTED
    countSort(c,RANGE);
    //END
    timeSum += getTime(time);
  }
  cout << "Time 1 (ns): " <<  timeSum / TESTS << '\n';

  timeSum = 0;
  for(int i = 0; i < TESTS; ++i) {
    vector<int> c = randVect;
    startClock(time);
    //CODE TO BE TEMPORALY TESTED
    countSort2(c,RANGE);
    //END
    timeSum += getTime(time);
  }
  cout << "Time 2 (ns): " <<  timeSum / TESTS << '\n';

  return 0;
}
