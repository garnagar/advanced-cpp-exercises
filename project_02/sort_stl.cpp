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

int main() {
  //Variables
  mt19937 gen(123); //init random generator
  timespec time;

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


  return 0;
}
