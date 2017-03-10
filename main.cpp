#include <iostream>
#include <malloc.h>
#include "src/ln_profe.h"
#include "src/test.h"
#include "src/ref.h"
#include "src/opt.h"

//#define HORNER
#define __linux__
template <typename T>
int initVector(T* a, unsigned int l)
{
    for (int i = 0; i < l; ++i) {
        *(a+i) = i;
    }
}
int main() {
    std::cout.precision(100);
    int l =10;
    float x = 2.0f;
    float * a =(float*)(malloc_simd(l*sizeof(float)));
    initVector(a,l);
    std::cout << anpi::opt::estrins(x,a, l) << std::endl;
    std::cout << anpi::ref::estrins(x,a,l) << std::endl;
    std::cout << anpi::ref::horner(x,a,l) << std::endl;
    return 0;
}

