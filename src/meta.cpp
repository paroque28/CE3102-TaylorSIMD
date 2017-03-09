//
// Created by pablorod on 3/8/2017.
//
#include <iostream>
#include "meta.h"
#include <xmmintrin.h>
int main()
{
    a_log<10,5> log;
    a_cos<1,5> cos;
    double * b = reinterpret_cast<double*>(&cos);
    //double * c  = __alloc_align(sizeof(double));
    return 0;

}