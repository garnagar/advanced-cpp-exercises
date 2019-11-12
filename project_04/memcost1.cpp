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
        Prueba* p[SIZE];
        volatile int suma = 0;

        for(int i = 0; i < SIZE; ++i) {
                p[i] = new Prueba;
        }

        for(int i = 0; i < SIZE; ++i) {
                (*p[i]).i1 = i;
        }

        for(int i = 0; i < SIZE; ++i) {
                suma += (*p[i]).i1;
        }

        for(int i = 0; i < SIZE; ++i) {
                free(p[i]);
        }
        return suma;
}

/**
 * Tests cost of allocation in dynamic memory using a unique pointer.
 * @return Sum of numbers from 0 to 10000.
 */
int costeMem3() {

        unique_ptr<Prueba> p[SIZE];
        volatile int suma = 0;

        for(int i = 0; i < SIZE; ++i) {
                p[i] = unique_ptr<Prueba>{new Prueba};
                p[i]->i1 = i;
        }

        for(int i = 0; i < SIZE; ++i) {
                suma += p[i]->i1;
                p[i].reset();
        }

        return suma;
}

/**
 * Tests cost of allocation in dynamic memory using a shared pointer.
 * @return Sum of numbers from 0 to 10000.
 */
int costeMem4() {
        shared_ptr<Prueba> p[SIZE];
        volatile int suma = 0;

        for(int i = 0; i < SIZE; ++i) {
                p[i] = shared_ptr<Prueba>{new Prueba};
                p[i]->i1 = i;
        }

        for(int i = 0; i < SIZE; ++i) {
                suma += p[i]->i1;
                p[i].reset();
        }

        return suma;
}



int main() {

        timespec time;

        cout << costeMem1() << endl;
        cout << costeMem2() << endl;
        cout << costeMem3() << endl;
        cout << costeMem4() << endl;

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

        startClock(time);
        for(int i = 0; i < TESTS; ++i) {
                costeMem3();
        }
        cout << "Time 3 (ms): " << (getTimeMs(time)/TESTS) << '\n';

        startClock(time);
        for(int i = 0; i < TESTS; ++i) {
            costeMem4();
        }
        cout << "Time 4 (ms): " << (getTimeMs(time)/TESTS) << '\n';

        return 0;
}
