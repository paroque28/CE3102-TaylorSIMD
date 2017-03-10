#include <cmath>
//
// Created by Pablo Rodriguez on 3/5/17.
//
namespace anpi {

    namespace ref {
        template <typename  T>
        T estrins(T x, T *m, const int length) {

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
            return m[0];
        }
    }
}
