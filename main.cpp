#include <iostream>
#include <malloc.h>
#include "src/ln_profe.h"
#include "src/test.h"
#include "src/polinomios.h"
#include "src/simd.h"
#include "src/alloc.h"

#define __linux__

int main() {
    int l =10;
    int * a =(int*)(malloc_simd(l*sizeof(int)));
    for (int i = 0; i < l; ++i) {
        *(a+i) = i;
    }
    int res = anpi::opt::estrinEval(2,a,l);
    std::cout << res << std::endl;
    return 0;
}

