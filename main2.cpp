//
// Created by ferllini13 on 10/03/17.
//

#include <iostream>
#include <malloc.h>
#include "src/ln_profe.h"
#include "src/test.h"
#include "src/ref.h"
#include "src/opt.h"
#include "src/graph.h"

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


    ref::ln_a<double> ref_log_centro10;
    ref_log_centro10.init<10,13>();//centro 10, terms 13 MAX
    opt::ln_a<double> opt_log_centro10;
    opt_log_centro10.init<10,13>();//centro 10, terms 13

    opt::ln_a<double> opt_cos_centro10;
    opt_cos_centro10.init<10,13>();//centro 10, terms 5

    //Calculatr log en 10
    std::cout << ref_log_centro10(11) << std::endl;

    std::cout << opt_log_centro10(11) << std::endl;
    //medir tiempos
    tests::time(ref_log_centro10,25000,10); //25000 pruebas empezando en 10
    tests::time(opt_log_centro10,25000,10);

    double ejeY [50];
    double ejeX [50];
    for(int j=1;j<50; ++j){
        ejeY[j] = tests::time(ref_log_centro10, j * 100 ,0);//agrega varas
        ejeX[j] = j * 100;

    }
    graph(ejeX,ejeY,"time",50);

    //medir error
    tests::error(opt_cos_centro10,5,10,&std::log);

    return 0;
}

