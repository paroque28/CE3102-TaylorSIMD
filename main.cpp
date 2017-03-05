#include <iostream>
#include "src/ln_profe.h"
#include "src/test.h"
int main() {
    test<double> t_double;


    anpi::profe::ln<double> aprox;

    t_double.error(aprox,5,10,& std::log);

    t_double.time(aprox,500000,10);

    return 0;
}