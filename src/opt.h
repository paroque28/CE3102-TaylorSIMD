//
// Created by pablorod on 3/9/2017.
//

#ifndef META_SIMD_H
#define META_SIMD_H

#include <cmath>
#include "x86intrin.h"

namespace anpi{
    namespace opt{


        template<typename T>
        class ln_a : public funcion<T>{
        private:
            T* _coef;
            T _center;
            unsigned int _terms;

            void init(const T center, const unsigned int terms) {
                a_log<center,terms> log;

                T * b = reinterpret_cast<double*>(&log);
                _center = center;
                _coef = (T*) malloc_simd(sizeof(T)*terms);
                _terms  = terms;
                for (int i = 0; i < terms; ++i) {
                    *(_coef+i) = *(b+1);
                }
            }

        public:
            ln_a(const T center, const unsigned int terms) {
                init(center, terms);
            }

            ~ln_a() { free(_coef); }

            inline T operator()(const T val) const {
                T h = val - _center;
#if defined HORNER
                T result = anpi::opt::horner(h,_coef,_terms);
#else
                T result = anpi::opt::estrins(h,_coef,_terms);
#endif
                return result;
            }

            // Evaluacion de la n-esima derivada.
            inline T diff(const T x, const unsigned int n) {
                T result; //evaluar de alguna forma.
                return result;
            }
        };

        template <typename T>
        T estrins(T x, T * a, const unsigned int length) {

            T * m= static_cast<T*>(malloc_simd(sizeof(T)*length));

            for (int j = 0; j < length; ++j) {
                *(m+j) = *(a+j);
            }

            //Evaluacion secuencial de un polinomio mediante el metodo de Estrin.
            int h = 1; // contador cantidad de pisos
            int exponente = 1;//eficiencia dos m la e
            int n = log2(length); // cantidad pisos
            int cantidad_Ts = 16/sizeof(T); // cantidad t
            T x_ala_e = x;

                if (sizeof(T)==8) {
                    while (h <= n) {

                        int i = 0;
                        for (i = 0; i + 2 * cantidad_Ts * exponente < length; i += 2 * cantidad_Ts * exponente) {

                            __m128d leftd = _mm_set_pd(m[i + 2 * exponente], m[i]);
                            __m128d rightd = _mm_set_pd(m[i + 3 * exponente], m[i + exponente]);
                            __m128d xsd = _mm_set_pd1(x_ala_e);
                            __m128d interd = _mm_mul_pd(xsd, rightd);
                            __m128d resd = _mm_add_pd(leftd, interd);
                            m[i] = resd[0];
                            m[i + 2 * exponente] = resd[1];

                        }

                        for (;i + exponente < length ; i += 2 * exponente) {
                            m[i] += m[i + exponente] * x_ala_e;
                        }

                        h++;
                        exponente *= 2;
                        x_ala_e *=x;
                    }
                }
                else {
                    while (h <= n) {
                        int i = 0;
                    for (i = 0; i + 2 * cantidad_Ts * exponente < length; i += 2 * cantidad_Ts * exponente) {
                        //para float
                        __m128 leftf = _mm_set_ps(m[i + 6 * exponente], m[i + 4 * exponente], m[i + 2 * exponente],m[i]);
                        __m128 rightf = _mm_set_ps(m[i + 7 * exponente], m[i + 5 * exponente], m[i + 3 * exponente],m[i + exponente]);
                        __m128 xsf = _mm_set1_ps(x_ala_e);
                        __m128 interf = _mm_mul_ps(xsf, rightf);
                        __m128 resf = _mm_add_ps(leftf, interf);
                        m[i] = resf[0];
                        m[i + 2 * exponente] = resf[1];
                        m[i + 4 * exponente] = resf[2];
                        m[i + 6 * exponente] = resf[3];

                    }
                        for (;i + exponente < length ; i += 2 * exponente) {
                            m[i] += m[i + exponente] * x_ala_e;
                        }

                        h++;
                        exponente *= 2;
                        x_ala_e =pow(x,exponente);
                }
            }
            if (log2(length) > (double) n) // si no es potencia de 2 le suma el ultimo
                m[0] += m[(int)std::pow(2, n)] * x_ala_e;
            free(m);
            return m[0];
        }

        template <typename T>
        T horner(T x, T *a, const unsigned int grado) {
            //Evaluacion secuencial de un polinomio mediante el metodo de Horner.
                if (sizeof(T)==8) {
                    __m128d result = _mm_set1_ps*(a[grado]);
                    __m128d coef;
                    __m128d xm;
                    __m128d mult;
                    for(int i=grado-1; i >= 0 ; --i) {
                        coef = _mm_set_pd1(a[i]);
                        mult = _mm_mul_pd(result,xm);
                        result = _mm_add_pd(result,mult);
                    }
                    return result[0];
                } else{
                    __m128 result = _mm_set1_ps*(a[grado]);
                    __m128 coef;
                    __m128 xm;
                    __m128 mult;
                    for(int i=grado-1; i >= 0 ; --i) {
                        coef = _mm_set1_ps(a[i]);
                        mult = _mm_mul_ps(result,xm);
                        result = _mm_add_ps(result,mult);
                    }
                    return result[0];
                }


        }

    }
}
#endif //META_SIMD_H
