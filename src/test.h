//
// Created by Pablo Rodriguez on 3/5/17.
//

#ifndef PROYECTO1_TEST_H
#define PROYECTO1_TEST_H
#include <typeinfo>
#include <chrono>
#include <iostream>
#include "function.h"
using namespace std;
namespace  anpi{
    namespace tests {
        template<typename T>
        double time(anpi::funcion<T> &f, unsigned int num_tests, const float start) {
            T x = start;
            T d = (2.f - start) / num_tests;
            auto start_time = std::chrono::high_resolution_clock::now();

            for (unsigned int i = 0; i < num_tests; i++, x += d) {
                f(x);
            }

            auto end_time = std::chrono::high_resolution_clock::now();
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

            return  static_cast<double>(ms) / num_tests;
        }

        template<typename T>
        void error(anpi::funcion<T> &f, unsigned int num_tests, const float start, T (*ref)(T)) {
            T x = start;
            T y;
            T teorica;
            T d = (2.f - start) / num_tests;

            for (unsigned int i = 0; i < num_tests; i++, x += d) {
                y = f(x);
                teorica = ref(x);
                std::cout << "Error for x = " << x<< " : " << (teorica - y) / teorica * 100 << " %" << std::endl;
            }
        }
    }
}


#endif //PROYECTO1_TEST_H
