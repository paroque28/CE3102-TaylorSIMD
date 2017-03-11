#include <iostream>
#include <malloc.h>
#include "src/ln_profe.h"
#include "src/test.h"
#include "src/ref.h"
#include "src/opt.h"

//#define HORNER
#define __linux__


using namespace anpi;


template <typename T>
int initVector(T* a, unsigned int l)
{
    for (int i = 0; i < l; ++i) {
        *(a+i) = i;
    }
}
int main() {
    std::cout.precision(100);


    ref::ln_a<double> ref;
    ref.init<10,5>();//centro 10, terms 5
    opt::ln_a<double> opt;
    opt.init<10,5>();//centro 10, terms 5

    std::cout << ref(10) << std::endl;

    std::cout << opt(10) << std::endl;
    //medir tiempos
    tests::time(ref,25000,10); //25000 pruebas empezando en 10
    tests::time(opt,25000,10);

    //medir error
    tests::error(ref,5,10,&std::log);

    return 0;
}

