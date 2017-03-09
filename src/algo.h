#include <cmath>

//
// Created by Pablo Rodriguez on 3/5/17.
//
namespace anpi {

    namespace ref {
        template <typename  T>
        T estrins(T x, T *m, const int length) {

            //empieza
            int e = 1; // contador cantidad de pisos
            int dos_pow_e = 1;//eficiencia dos a la e
            int n = log2(length); // cantidad pisos
            while (e <= n) {
                for (int i = 0; i + dos_pow_e < length; i += 2 * dos_pow_e) {

                    m[i] += m[i + dos_pow_e] * std::pow(x, dos_pow_e);
                }
                e++;
                dos_pow_e *= 2;
            }
            if (log2(length) > (double) n) // si no es potencia de 2 le suma el ultimo
                m[0] += m[(int)std::pow(2, n)] * pow(x, dos_pow_e);
            return m[0];
        }
    }
}
