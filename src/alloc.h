//
// Created by pablorod on 3/9/2017.
//

#ifndef META_ALLOC_H
#define META_ALLOC_H


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

#endif //META_ALLOC_H
