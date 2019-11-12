#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <stdio.h>
#include <set>
#include <forward_list>

#define SIZE 10000
#define TESTS 100000

using namespace std;

class IMemoryManager
{
public:
  virtual void* allocate(size_t) = 0;
  virtual void free(void*) = 0;
};

class MemoryManager : public IMemoryManager
{
//the block sizes can be determined by the user based on approximating
//the sizes of object types used in the application
//The MemoryPool can be initialised partially or completely , based on the
//need and the frequency of occurence of certain types of object;
//each block shall contain 4 extra bytes to store metadata information
//One such information is that indicating whether this block is free
//or not. Another tentative information could be guard bytes which detect
//heap memory corruption , ie , when someone writes beyond the boundary
//of an object accidentally via  memcpy or memset functions.In our
//implementation everyblock is guarded by 4 bytes in the end.The first two
//bytes of these four are marked with  special characters 0xde,0xad indicating
//the end of the block .The next byte will contain the size of block and the
//of the byte shall indicate wheteher this block is free or available.
private:
  std::forward_list<void*> Byte24PtrList;
  std::vector<void*> MemoryPoolList;
  friend struct Prueba;
  void InitialiseByte24List(void* );
public:
  MemoryManager() {}
  ~MemoryManager() {}
  void* allocate(size_t);
  void free(void*);
};

MemoryManager gMemoryManager;

struct Prueba {
    float f1, f2;
    int i1, i2, i3;

    inline void* operator new(size_t size)
    {
        return gMemoryManager.allocate(sizeof(Prueba));
    }

    inline void operator delete(void* object)
    {
        gMemoryManager.free(object);
    }
};

const int PRUEBA_SIZE = sizeof(Prueba);
const int POOL_SIZE = 1024; //number of elements in a single pool
                //can be chosen based on application requirements
const int MAX_BLOCK_SIZE = 24; //depending on the application it may change
                   //In above case it came as 36


void* MemoryManager::allocate(size_t size)
{
    void* base = 0;
    switch(size)
    {
    case PRUEBA_SIZE: //20
    {
        printf("IM HERE!\n");
        if(Byte24PtrList.empty())
        {
            printf("list empty\n");
            base = new char [24 * POOL_SIZE];
            MemoryPoolList.push_back(base);
            InitialiseByte24List(base);
        }
        void* blockPtr =  Byte24PtrList.front();
        *((static_cast<char*>(blockPtr)) + 22) = 32; //size of block set
        *((static_cast<char*>(blockPtr)) + 23) = 0; //block is no longer free
        Byte24PtrList.pop_front();
        return blockPtr;
    }
    default: break;
    }
    return 0;
}

void MemoryManager::free(void* object)
{
    char* init = static_cast<char*>(object);

    while(1)
    {
        int count = 0;
        while(*init != 0xde) //this loop shall never iterate more than
        {       // MAX_BLOCK_SIZE times and hence is O(1)
            init++;
            count++;
            if(count > MAX_BLOCK_SIZE)
            {
                printf("count:%d",count);
                printf ("runtime heap memory corruption near %p", &object);
                exit(1);
            }
        }
        if(*(++init) == 0xad) // we have hit the guard bytes
            break; // from the outer while
    }
    init++; // ignore size byte
    init++;
    *init = 1; // set free/available byte
}

void MemoryManager::InitialiseByte24List(void* base)
{
    for (int i = 0; i< POOL_SIZE; ++i)
    {
        char* guardByteStart = &(static_cast<char*>(base)[i*24]) + 20;
        *guardByteStart = 0xde;
        guardByteStart++;
        *guardByteStart = 0xad; //end of block
        guardByteStart++;
        *guardByteStart = 24; //sizeof block
        guardByteStart++;
        *guardByteStart = 1; //block  available
        Byte24PtrList.push_front(&(static_cast<char*>(base)[i*24]));
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// BEGINNING OF THE TEST METHODS
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!


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
        }

        return suma;
}



int main() {

        timespec time;

        cout << costeMem1() << endl;
        //cout << costeMem2() << endl;
        cout << costeMem3() << endl;
        cout << costeMem4() << endl;

        /*startClock(time);
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
        cout << "Time 4 (ms): " << (getTimeMs(time)/TESTS) << '\n';*/

        return 0;
}
