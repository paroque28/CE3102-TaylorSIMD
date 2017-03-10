//
// Created by andres on 3/9/17.
//

#ifndef META_FUNCTOR_H
#define META_FUNCTOR_H

#include <malloc.h>
#include "alloc.h"
#include "meta.h"
#include "algo.h"
namespace anpi {

    template<typename T>
    class ln_a {
        private:
            // Coeficientes de la serie de Taylor.
            T* _coef;
                // Centro de la serie
            T _center;

            int _terms;
            /**
             * Inicializa los coeficientes de la serie de Taylor centrada en
             * _center para el numero dado de coeficientes.
             */
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
            
            // Destructor libera memoria reservada.
            ~ln_a() { free(_coef); }
            
            // Evaluacion de la funcion logaritmica.
            inline T operador()(const T val) const {
                T h = val - _center;
                T result = anpi::ref::estrins(h,_coef,_terms); //evaluar de alguna forma
                return result;
            }

            // Evaluacion de la n-esima derivada.
            inline T diff(const T x, const unsigned int n) {
                T result; //evaluar de alguna forma.
                return result;
            }
    };
}
#endif //META_FUNCTOR_H
