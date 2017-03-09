//
// Created by pablorod on 3/9/2017.
//

#ifndef META_SIMD_H
#define META_SIMD_H

#include <cmath>
#include "x86intrin.h"

namespace anpi{
    namespace opt{

        template <typename T>
        T pow(T x, T y) {
            //Calculo eficiente de la potencia x^y.
            if(y == 1)
                return x;

            T res = 1;
            while(y > 0) {
                res *= x;
                y--;
            }
            return res;
        }

        template <typename T>
        T estrinEval(T x, T * a, int grado) {
            //Evaluacion secuencial de un polinomio mediante el metodo de Estrin.
            int h = 1; // contador cantidad de pisos
            int exponente = 1;//eficiencia dos a la e
            int n = log2(grado); // cantidad pisos
            int cantidad_Ts = 16/sizeof(T); // cantidad t
            int x_ala_e;

            while (h<=n) {
                x_ala_e=pow(x,exponente);
                int i = 0;
                for (i = 0 ; i + 2 * cantidad_Ts * exponente < grado ; i += 2 * cantidad_Ts * exponente) {
                    if (true) // int check
                    {
                        __m128i left = _mm_set_epi32(a[i],a[i+2*exponente],a[i+4*exponente],a[i+6*exponente]);
                        int blanco = a[i+2*exponente];

                        __m128i right = _mm_set_epi32(a[i+exponente],a[i+3*exponente],a[i+5*exponente],a[i+7*exponente]);

                        __m128i xs = _mm_set1_epi32(pow(x,exponente));

                        __m128i inter = _mm_mul_epi32(right,xs);

                        __m128i res = _mm_add_epi32(left,inter);



                    }
                }

                for (;i + exponente < grado ; i += 2 * exponente) {
                    a[i] += a[i + exponente] * x_ala_e;
                }

                h++;
                exponente *= 2;
            }
            if (log2(grado) > (double) n) // si no es potencia de 2 le suma el ultimo
                a[0] += a[pow(2, n)] * pow(x, exponente);
            return a[0];
        }


    }
}
#endif //META_SIMD_H
