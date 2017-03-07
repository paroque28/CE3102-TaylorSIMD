#ifndef PROYECTO1_FUNCTION_H
#define PROYECTO1_FUNCTION_H

#include <cmath>

namespace anpi {
    namespace ref {
        
        template <typename T>
        T pow(T x, T y) {
            //Calculo eficiente de la potencia x^y.
            if(y == 1)
                return x;
            
            T res = 1; 
            while(y > 0) {
                res *= x;
                y--;
            }
            return res;
        }

        template <typename T>
        T hornerEval(T x, T * coeficientes, int grado) {
            //Evaluacion secuencial de un polinomio mediante el metodo de Horner.
            T resultado = 0;
            int contador = 0;

            while (contador <= grado) {
                resultado = (resultado * x) + *coeficientes;

                contador++;
                coeficientes++;
            }

            return resultado;
        }

        template <typename T>
        T estrinEval(T x, T * coeficientes, int grado) {
            //Evaluacion secuencial de un polinomio mediante el metodo de Estrin.
            int e = 1; // contador cantidad de pisos
            int dos_pow_e = 1;//eficiencia dos a la e
            int n = log2(grado); // cantidad pisos

            while (e<=n) {
                for (int i = 0 ; i + dos_pow_e < grado ; i += 2 * dos_pow_e) {
                    coeficientes[i] += coeficientes[i + dos_pow_e] * pow(x, dos_pow_e);
                }
                e++; 
                dos_pow_e *= 2;
            }
            if (log2(grado) > (double) n) // si no es potencia de 2 le suma el ultimo
                coeficientes[0] += coeficientes[pow(2, n)] * pow(x, dos_pow_e);
            return coeficientes[0];
         }
    }

}
#endif //PROYECTO1_FUNCTION_H
