//
// Created by Pablo Rodriguez on 3/5/17.
//

#include "ln_profe.h"

template <typename T>
T anpi::ln_profe<T>::operator()(const T val) const {
    return std::log(val);
}
template <typename T>
T anpi::ln_profe<T>::diff(const T x, const unsigned int n) const {
    T val = factorial<T>(n-1)/std::pow(x,n);

    return ((n & 1) == 0) ? -val : val;
}
