//
// Created by pablorod on 3/8/2017.
//

#ifndef PROYECTO1_META_H
#define PROYECTO1_META_H


#include <cmath>

template <int N>
struct Factorial
{
    enum { value = N * Factorial<N - 1>::value };
};

template <>
struct Factorial<0>
{
    enum { value = 1 };
};


template <int x,int I>
struct a_log {
    a_log<x,I - 1> rest;
    double y = ((((I-1) & 1) == 0) ?  -Factorial<(I-2 )>::value / std::pow(x, (I-1)) : Factorial<(I-2)>::value / std::pow(x, (I-1)));
};

template <int x>
struct a_log<x,1> {
    double y =  std::log(x) ;
};

template <int x,int I>
struct a_cos {
    a_cos<x,I - 1> rest;
    double y = ( (((I-1) & 1) == 0) ?  ( ((((I-1)/2) & 1) == 0) ? std::cos(x)  : - std::cos(x) )
                                        : ( (((I/2) & 1) == 0) ? std::sin(x) : - std::sin(x))
                    );
};

template <int x>
struct a_cos<x,1> {
    double y =  std::cos(x) ;
};


#endif //PROYECTO1_META_H
