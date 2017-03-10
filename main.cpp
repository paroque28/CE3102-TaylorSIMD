#include <iostream>
#include <malloc.h>
#include "src/ln_profe.h"
#include "src/test.h"
#include "src/algo.h"
#include "src/polinomios.h"
#include "src/simd.h"
#include "src/alloc.h"

#define __linux__

int main() {
    std::cout.precision(100);
    int l =10;
    float x = 2.0f;
    float * a =(float*)(malloc_simd(l*sizeof(float)));
    for (int i = 0; i < l; ++i) {
        *(a+i) = i;
    }
    std::cout << anpi::opt::estrinEval(x,a, l) << std::endl;
    for (int i = 0; i < l; ++i) {
        *(a+i) = i;
    }
    std::cout << anpi::ref::estrins(x,a,l) << std::endl;
    for (int i = 0; i < l; ++i) {
        *(a+i) = i;
    }
    std::cout << anpi::ref::hornerEval(x,a,l) << std::endl;
    return 0;
}

