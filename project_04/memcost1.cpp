#include <iostream>
#include <memory>

#define SIZE 10000
#define TESTS 100000

using namespace std;

struct Prueba {
 float f1, f2;
 int i1, i2, i3;
};

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
* Tests cost of allocation in static memory.
* @return Sum of numbers from 0 to 10000.
*/
int costeMem1() {
  Prueba v[SIZE];
  volatile int suma = 0;

  for(int i = 0; i < SIZE; ++i) {
    v[i].i1 = i;
  }

  for(int i = 0; i < SIZE; ++i) {
    suma += v[i].i1;
  }
  return suma;
}

/**
* Tests cost of allocation in dynamic memory.
* @return Sum of numbers from 0 to 10000.
*/
int costeMem2() {
  Prueba* p = new Prueba[SIZE];
  volatile int suma = 0;

  for(int i = 0; i < SIZE; ++i) {
    p[i].i1 = i;
  }

  for(int i = 0; i < SIZE; ++i) {
    suma += p[i].i1;
  }

  delete [] p;
  return suma;
}



int main() {

  timespec time;

  cout << costeMem1() << '\n';
  cout << costeMem2() << '\n';

  startClock(time);
  for(int i = 0; i < TESTS; ++i) {
    costeMem1();
  }
  cout << "Time 1 (ms): " << (getTimeMs(time)/TESTS) << '\n';

  startClock(time);
  for(int i = 0; i < TESTS; ++i) {
    costeMem2();
  }
  cout << "Time 2 (ms): " << (getTimeMs(time)/TESTS) << '\n';


  return 0;
}
