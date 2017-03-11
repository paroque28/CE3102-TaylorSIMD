#include <iostream>
#include <malloc.h>
#include "src/ln_profe.h"
#include "src/test.h"
#include "src/ref.h"
#include "src/opt.h"


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


    ref::ln_a<double> ref_log_centro10;
    ref_log_centro10.init<10,4>();//centro 10, terms 13 MAX
    opt::ln_a<double> opt_log_centro10;
    opt_log_centro10.init<10,4>();//centro 10, terms 13

    opt::ln_a<double> opt_cos_centro10;
    opt_cos_centro10.init<10,4>();//centro 10, terms 5

    ref::ln_a<double> ref_cos_centro10;
    ref_cos_centro10.init<10,4>();//centro 10, terms 5

    //Calculatr log en 10
    std::cout << ref_log_centro10(11) << std::endl;

    std::cout << opt_cos_centro10(11) << std::endl;
    //medir tiempos
    tests::time(ref_log_centro10,25000,10); //25000 pruebas empezando en 10
    tests::time(opt_log_centro10,25000,10);

    //medir error
    tests::error(ref_cos_centro10,5,10,&std::log);

    return 0;
}

