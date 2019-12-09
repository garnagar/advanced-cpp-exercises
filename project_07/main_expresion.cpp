

#include<iostream>
#include "expresion.h"

using std::cout;
using std::endl;

const unsigned TAM = 1000000;

int main()
{
    Array<double> x(TAM), y(TAM);

    for(unsigned i = 0; i < TAM; i++)
    {
        x[i] = 2;
        y[i] = 3;
    }
    
    x = 1.2 * x + y;
    
    for(unsigned i = 0; i < 10; i++)
    {
        cout << x[i] << " ";
    }
    cout << endl;
    
    return 0;
}
