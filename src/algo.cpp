#include <cmath>

//
// Created by Pablo Rodriguez on 3/5/17.
//
int pow(int x, int y) {if(y==1)return x; int res = 1; while(y>0) {res*=x;y--;}return res;}

int estrins(int x, const int length, int m[]) {

    //empieza
    int e = 1; // contador cantidad de pisos
    int dos_pow_e = 1;//eficiencia dos a la e
    int n = log2(length); // cantidad pisos
    while (e<=n)
    {
        for (int i=0; i+ dos_pow_e< length;i += 2*dos_pow_e)
        {

            m[i] += m[i+dos_pow_e]*pow(x,dos_pow_e);
        }
       e++; dos_pow_e *= 2;
    }
    if (log2(length) > (double) n) // si no es potencia de 2 le suma el ultimo
        m[0] += m[pow(2,n)]*pow(x,dos_pow_e);
    return m[0];
}
