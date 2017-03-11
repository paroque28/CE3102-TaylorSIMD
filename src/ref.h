#include <cmath>
#include "meta.h"
#include "alloc.h"
//
// Created by Pablo Rodriguez on 3/5/17.
//
namespace anpi {

    namespace ref {



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
        private:
            T *_coef;
            T _center;
            unsigned int _terms;
        public:
            template<int center, int terms>
            void init() {
                a_log<T, center, terms> log;

                T *b = reinterpret_cast<T *>(&log);
                _center = center;
                _coef = (T *) malloc_simd(sizeof(T) * terms);
                _terms = terms;
                for (int i = 0; i < terms; ++i) {
                    *(_coef + i) = (T) *(b + 1);
                }
            }


            ln_a() {

            }

            ~ln_a() { free(_coef); }

            inline T operator()(const T val) const {
                const T h = val - _center;
#if defined HORNER
                return horner(h,_coef,_terms);
#else
                return estrins(h, _coef, _terms);
#endif
            }

            // Evaluacion de la n-esima derivada.
            inline T diff(const T x, const unsigned int n) {
                T result; //evaluar de alguna forma.
                return result;
            }

        };



        template<typename T>
        class cos_a : public funcion<T>{
        private:
            T* _coef;
            T _center;
            unsigned int _terms;
        public:
            template<int center,int terms>
            void init() {
                a_cos<T,center,terms> log;

                T * b = reinterpret_cast<T*>(&log);
                _center = center;
                _coef = (T*) malloc_simd(sizeof(T)*terms);
                _terms  = terms;
                for (int i = 0; i < terms; ++i) {
                    *(_coef+i) = (T) *(b+1);
                }
            }



            cos_a() {

            }

            ~cos_a() { free(_coef); }

            inline T operator()(const T val) const{
                const T h = val - _center;
#if defined HORNER
                return horner(h,_coef,_terms);
#else
                return estrins(h,_coef,_terms);
#endif
            }

            // Evaluacion de la n-esima derivada.
            inline T diff(const T x, const unsigned int n) {
                T result; //evaluar de alguna forma.
                return result;
            }


        };








    }
}
