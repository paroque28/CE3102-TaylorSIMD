//
// Created by Pablo Rodriguez on 3/5/17.
//

#ifndef PROYECTO1_FUNCTION_H
#define PROYECTO1_FUNCTION_H


namespace anpi
{
    template <typename T>
    class funcion
    {
    public:
        virtual inline T operator() (const T val) const;

        virtual inline T diff(const T val, const unsigned int n) const;
    };

}

#endif //PROYECTO1_FUNCTION_H
