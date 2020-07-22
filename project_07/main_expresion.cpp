/**
* Project: Advanced Programming Lab Excercise 07
* Authors: Lukas Kyzlik and Matej Sojak
* Date: 17/12/2019
*/

#include<iostream>
#include "expresion.h"
#include "Eigen/Dense"
#include "sarray2.h"

using std::cout;
using std::endl;

const unsigned TAM = 1000000;

int main()
{
    // SECTION 1
    Array<double> x(TAM), y(TAM);

    for(unsigned i = 0; i < TAM; i++)
    {
        x[i] = 2;
        y[i] = 3;
    }

     x = (1.2 + x) * y + ( (2.0 * y) ^ 2.0 );

    for(unsigned i = 0; i < 10; i++)
    {
        cout << x[i] << " ";
    }
    cout << endl;

    //SECTION 2
    SArray2<double> sx(TAM);
    SArray2<double> sy(TAM);

    for(unsigned i = 0; i < TAM; i++)
    {
        sx[i] = 2;
        sy[i] = 3;
    }

     sx = (1.2 + sx) * sy + ( (2.0 * sy) ^ 2.0 );

    for(unsigned i = 0; i < 10; i++)
    {
        cout << sx[i] << " ";
    }
    cout << endl;

    //SECTION 4

    Eigen::ArrayXd eigx(TAM);
    Eigen::ArrayXd eigy(TAM);

    for(unsigned i = 0; i < TAM; i++)
    {
        eigx(i) = 2;
        eigy(i) = 3;
    }

    eigx = (1.2 + eigx) * eigy + (pow((2.0 * eigy), 2.0));

    for(unsigned i = 0; i < 10; i++)
    {
        cout << eigx(i) << " ";
    }
    cout << endl;

    return 0;
}
