//
// Created by Pablo Rodriguez on 3/5/17.
//

#ifndef PROYECTO1_LN_PROFE_H
#define PROYECTO1_LN_PROFE_H

#include <cmath>

#include "function.h"

namespace anpi {

    template<typename T>
    T factorial (const unsigned int n) {
        return n<2 ? T(1) : static_cast<T>(n * factorial <T>(n-1)); }


    template<typename T>
    class ln_profe : public funcion<T>{
        int a();

    public:
        T operator()(const T val) const override;

        T diff(const T val, const unsigned int n) const override;
    };




}

#endif //PROYECTO1_LN_PROFE_H
