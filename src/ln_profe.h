//
// Created by Pablo Rodriguez on 3/5/17.
//

#ifndef PROYECTO1_LN_PROFE_H
#define PROYECTO1_LN_PROFE_H

#include <cmath>

#include "function.h"

namespace anpi {
    namespace profe {
        template<typename T>
        T factorial(const unsigned int n) {
            return n < 2 ? T(1) : static_cast<T>(n * factorial<T>(n - 1));
        }


        template<typename T>
        class ln : public funcion<T> {


        public:
            T operator()(const T val) const{
                return std::log(val);
            }

            T diff(const T x, const unsigned int n) const {
                T val = factorial<T>(n - 1) / std::pow(x, n);

                return ((n & 1) == 0) ? -val : val;
            }
        };

    }
}

#endif //PROYECTO1_LN_PROFE_H
