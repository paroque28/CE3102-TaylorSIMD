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
        T estrinEval(T x, T * a, const int grado) {
            //Evaluacion secuencial de un polinomio mediante el metodo de Estrin.
            int h = 1; // contador cantidad de pisos
            int exponente = 1;//eficiencia dos a la e
            int n = log2(grado); // cantidad pisos
            int cantidad_Ts = 16/sizeof(T); // cantidad t
            T x_ala_e = x;

                if (sizeof(T)==8) {
                    while (h <= n) {

                        int i = 0;
                        for (i = 0; i + 2 * cantidad_Ts * exponente < grado; i += 2 * cantidad_Ts * exponente) {


                            __m128d leftd = _mm_set_pd(a[i + 2 * exponente], a[i]);
                            __m128d rightd = _mm_set_pd(a[i + 3 * exponente], a[i + exponente]);
                            __m128d xsd = _mm_set_pd1(x_ala_e);
                            __m128d interd = _mm_mul_pd(xsd, rightd);
                            __m128d resd = _mm_add_pd(leftd, interd);

                        }

                        for (;i + exponente < grado ; i += 2 * exponente) {
                            a[i] += a[i + exponente] * x_ala_e;
                        }

                        h++;
                        exponente *= 2;
                        x_ala_e *=x;
                    }
                }
                else {
                    while (h <= n) {
                        int i = 0;
                    for (i = 0; i + 2 * cantidad_Ts * exponente < grado; i += 2 * cantidad_Ts * exponente) {
                        //para float
                        __m128 leftf = _mm_set_ps(a[i + 6 * exponente], a[i + 4 * exponente], a[i + 2 * exponente],a[i]);
                        __m128 rightf = _mm_set_ps(a[i + 7 * exponente], a[i + 5 * exponente], a[i + 3 * exponente],a[i + exponente]);
                        __m128 xsf = _mm_set1_ps(x_ala_e);
                        __m128 interf = _mm_mul_ps(xsf, rightf);
                        __m128 resf = _mm_add_ps(leftf, interf);
                        a[i] = resf[0];
                        a[i + 2 * exponente] = resf[0];
                        a[i + 4 * exponente] = resf[0];
                        a[i + 6 * exponente] = resf[0];
                    }
                        for (;i + exponente < grado ; i += 2 * exponente) {
                            a[i] += a[i + exponente] * x_ala_e;
                        }

                        h++;
                        exponente *= 2;
                        x_ala_e *=x;
                }
            }
            if (log2(grado) > (double) n) // si no es potencia de 2 le suma el ultimo
                a[0] += a[(int)std::pow(2, n)] * x_ala_e;
            return a[0];
        }


    }
}
#endif //META_SIMD_H
