
#ifndef PROYECTO1
#define PROYECTO1
#include <cmath>
#include <xmmintrin.h>

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
            int piso = 1; // contador cantidad de pisos
            int exponente = 1;//eficiencia dos a la e
            int n = log2(grado); // cantidad pisos
            int x_ala_e;

            while (piso<=n) {
                x_ala_e=pow(x,exponente);
                for (int i = 0 ; i + exponente < grado ; i += 2 * exponente) {
                    coeficientes[i] += coeficientes[i + exponente] * x_ala_e;
                }
                piso++;
                exponente *= 2;
            }
            if (log2(grado) > (double) n) // si no es potencia de 2 le suma el ultimo
                coeficientes[0] += coeficientes[pow(2, n)] * pow(x, exponente);
            return coeficientes[0];
         }
    }

}

#endif