/**
* Project: Advanced Programming Lab Excercise 02
* Authors: Lukas Kyzlik and Matej Sojak
* Date: 17/10/2019
*/

#include <iostream>
#include <time.h>
using namespace std;

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
  //Variables
  timespec ini_time;
  timespec end_time;

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ini_time);



  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);


  return 0;
}
