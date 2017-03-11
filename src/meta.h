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


template <typename T,int x,int I>
struct a_log {
    a_log<T,x,I - 1> rest;
    T y = ((((I-1) & 1) == 0) ?  -Factorial<(I-2 )>::value / std::pow(x, (I-1)) : Factorial<(I-2)>::value / std::pow(x, (I-1)));
};

template <typename T,int x>
struct a_log<T,x,1> {
    T y =  std::log(x) ;
};

template <typename T,int x,int I>
struct a_cos {
    a_cos<T,x,I - 1> rest;
    T y = ( (((I-1) & 1) == 0) ?  ( ((((I-1)/2) & 1) == 0) ? std::cos(x)  : - std::cos(x) )
                                        : ( (((I/2) & 1) == 0) ? std::sin(x) : - std::sin(x))
                    );
};

template <typename T,int x>
struct a_cos<T,x,1> {
    T y =  std::cos(x) ;
};


#endif //PROYECTO1_META_H
