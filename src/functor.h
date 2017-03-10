//
// Created by andres on 3/9/17.
//

#ifndef META_FUNCTOR_H
#define META_FUNCTOR_H

namespace anpi {

    template<typename T>
    class ln_a {
        private:
            // Coeficientes de la serie de Taylor.
            T* _coef;

            // Alineacion de la memoria en bytes.
            static const unsigned int _alignment = 32u;
            
                // Centro de la serie
            T _center;

            /**
             * Inicializa los coeficientes de la serie de Taylor centrada en
             * _center para el numero dado de coeficientes.
             */
            void init(const T center, const unsigned int terms) {
                _center = center;
                // Redondear hacia arriba.
                unsigned int blocks = ((terms * sizeof(T) + (_alignment - 1)) / _alignment);
                _coef = static_cast<T*>(aligned_alloc(_alignment, blocks * _alignment)); 

                ln<T> logn;k
                for (unsigned int i = 0 ; i < terms ; ++i) {
                    _coef[i] = logn.diff(center, i) / factorial<T>(i);
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
                T result; //evaluar de alguna forma
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
