#include <iostream>
#include <malloc.h>
#include "src/ln_profe.h"
#include "src/test.h"
#include "src/polinomios.h"
#include "src/simd.h"

#define __linux__
void * malloc_simd(const size_t size)
{
#if defined WIN32           // WIN32
    return _aligned_malloc(size, 16);
#elif defined __linux__     // Linux
    return memalign(16, size);
#elif defined __MACH__      // Mac OS X
    return malloc(size);
#else                       // other (use valloc for page-aligned memory)
    return valloc(size);
#endif
}

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

