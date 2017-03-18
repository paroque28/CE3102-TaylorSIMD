#ifndef META_SIMD
#define META_SIMD

#include <cmath>
#include "meta.h"
#include "alloc.h"
//#define HORNER
//
// Created by Pablo Rodriguez on 3/5/17.
//
namespace anpi {

    namespace ref {

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
        T estrins(T x, T *a, unsigned int length){
            T * m = static_cast<T*>(malloc(sizeof(T) * length));

            for (int i = 0; i < length; ++i) {
                *(m+i) = *(a+i);
            }

            //empieza
            int h = 1; // contador cantidad de pisos
            int exponente = 1;//eficiencia dos a la e
            int n = log2(length); // cantidad pisos
            T x_ala_e = x;
            while (h <= n) {

                for (int i = 0; i + exponente < length; i += 2 * exponente) {

                    m[i] += m[i + exponente] * x_ala_e;
                }
                h++;
                exponente *= 2;
                x_ala_e = pow(x,exponente);
            }


            if (log2(length) > (double) n) // si no es potencia de 2 le suma el ultimo
                m[0] += m[(int)std::pow(2, n)] * x_ala_e;
            free(m);
            return m[0];
        }



        template<typename T>
        T horner(T x, T *a,  unsigned int grado) {
            //Evaluacion secuencial de un polinomio mediante el metodo de Horner.
            T result = a[grado];
            for(int i=grado-1; i >= 0 ; --i)
                result = result * x + a[i];
            return result;

        }


        template<typename T>
        class ln_a : public funcion<T> {

        public:
            template<int center, int max_terms>
            void init(unsigned int terms) {
                a_log<T, center, max_terms> as;

                T *b = reinterpret_cast<T *>(&as);
                this->_center = center;
                this->_coef = (T *) malloc_simd(sizeof(T) * terms);
                this->_terms = terms;
                for (int i = 0; i < terms; ++i) {
                    *(this->_coef + i) =  *(b + i);
                }
            }


            ln_a() {

            }

            ~ln_a() { free(this->_coef); }

            inline T operator()(const T val) const {
                const T h = val - this->_center;
#if defined HORNER
                return horner(h,this->_coef,this->_terms);
#else
                return estrins(h, this->_coef, this->_terms);
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
                    *(this->_coef+i) = *(b+i);
                }
            }


            cos_a() {

            }

            ~cos_a() { free(this->_coef); }

            inline T operator()(const T val) const{
                const T h = val - this->_center;
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


#endif