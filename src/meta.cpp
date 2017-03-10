//
// Created by pablorod on 3/8/2017.
//
#include <iostream>
#include "meta.h"
#include <xmmintrin.h>

#include "alloc.h"

#define __linux__
int main()
{
    const int l = 5;
    a_log<10,l> log;
    a_cos<1,l> cos;
    double * b = reinterpret_cast<double*>(&cos);
    double * aligned = (double*) malloc_simd(sizeof(double)*l);
    for (int i = 0; i < l; ++i) {
        *(aligned+i) = *(b+1);
    }
    return 0;

}