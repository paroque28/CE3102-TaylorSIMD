
#ifndef PROYECTO1
#define PROYECTO1
#include <cmath>
#include <xmmintrin.h>

namespace anpi {
    namespace ref {


        template <typename T>
        T hornerEval(T x, T * a, int grado) {
            //Evaluacion secuencial de un polinomio mediante el metodo de Horner.
            T result = a[grado];
            for(int i=grado-1; i >= 0 ; --i)
                result = result * x + a[i];
            return result;
        }


    }

}

#endif