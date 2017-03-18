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
    protected:
        T* _coef;
        T _center;
        unsigned int _terms;
    public:
        virtual T operator() (const T val) const {
            return 0;
        }

        virtual T diff(const T val, const unsigned int n) const {
            return 0;
        }

        virtual void setTerms(unsigned int t)
        {
            _terms = t;
        }
    };

}

#endif //PROYECTO1_FUNCTION_H
