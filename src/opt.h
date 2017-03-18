//
// Created by pablorod on 3/9/2017.
//

#ifndef META_SIMD_H
#define META_SIMD_H
//#define HORNER

#include <cmath>
#include "x86intrin.h"

namespace anpi{
    namespace opt{
        int factorial (int n)
        {
            int fac =1;
            for(int i = 1; i <=n; ++i)
            {
                fac *= i;
            }
            return fac;
        }

        template<typename T>
        T estrins(T x, T * a, const unsigned int length){

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
                        __m128d xsd = _mm_set1_pd(x_ala_e);
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

        template<typename T>
        T horner(T x, T *a, const unsigned int grado) {
            //Evaluacion secuencial de un polinomio mediante el metodo de Horner.
            if (sizeof(T)==8) {

                __m128d result = _mm_set1_pd(a[grado]);
                __m128d coef;
                __m128d xm = _mm_set1_pd(x);
                __m128d mult;
                for(int i=grado-1; i >= 0 ; --i) {
                    coef = _mm_set1_pd(a[i]);
                    mult = _mm_mul_pd(result,xm);
                    result = _mm_add_pd(result,mult);
                }
                return result[0];
            } else{
                __m128 result = _mm_set1_ps(a[grado]);
                __m128 coef;
                __m128 xm = _mm_set1_ps(x);
                __m128 mult;
                for(int i=grado-1; i >= 0 ; --i) {
                    coef = _mm_set1_ps(a[i]);
                    mult = _mm_mul_ps(result,xm);
                    result = _mm_add_ps(result,mult);
                }
                return result[0];
            }


        }

        template<typename T>
        class ln_a : public funcion<T>{
        public:
            template<int center,int max_terms>
            void init(unsigned int terms) {
                a_log<T,center,max_terms> as;

                T * b = reinterpret_cast<T*>(&as);
                this->_center = center;
                this->_coef = (T*) malloc_simd(sizeof(T)*terms);
                this->_terms  = terms;
                for (int i = 0; i < terms; ++i) {
                    *(this->_coef+i) =  *(b+i);
                }
            }


            ln_a() {
            }

            ~ln_a() { free(this->_coef); }

            inline T operator()(const T val) const {
                T h = val - this->_center;
#if defined HORNER
                return horner(h,this->_coef,this->_terms);
#else
                return estrins(h,this->_coef,this->_terms);
#endif

            }

            // Evaluacion de la n-esima derivada.
            inline T diff(const T x, const unsigned int n) {
                return ((((n-1) & 1) == 0) ?  -factorial(n-2 )/ std::pow(x, (n-1)) : factorial(n-2) / std::pow(x, (n-1)));
            }


        };

        template<typename T>
        class cos_a : public funcion<T>{

        public:
            template<int center,int max_terms>
            void init(unsigned int terms) {
                a_cos<T,center,max_terms> as;

                T * b = reinterpret_cast<T*>(&as);
                this->_center = center;
                this->_coef = (T*) malloc_simd(sizeof(T)*terms);
                this->_terms  = terms;
                for (int i = 0; i < terms; ++i) {
                    *(this->_coef+i) =  *(b+i);
                }
            }


            cos_a() {
            }

            ~cos_a() { free(this->_coef); }

            inline T operator()(const T val) const {
                T h = val - this->_center;
#if defined HORNER
                return horner(h,this->_coef,this->_terms);
#else
                return estrins(h,this->_coef,this->_terms);
#endif

            }

            // Evaluacion de la n-esima derivada.
            inline T diff(const T x, const unsigned int n) {
                return ( (((n-1) & 1) == 0) ?  ( ((((n-1)/2) & 1) == 0) ? std::cos(x)  : - std::cos(x) )
                                            : ( (((n/2) & 1) == 0) ? std::sin(x) : - std::sin(x))
                );
            }



        };

    }
}
#endif //META_SIMD_H
