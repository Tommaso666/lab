#ifndef __CAMPO__
#define __CAMPO__

// librerie
#include <cmath>
#include <iostream>
#include"funzioni.h"
// funzioni
using namespace std;
class integratore {
    public:
    virtual double integrale(const funzione& f ,double a,double b,int pass) const = 0;
    virtual ~integratore() {}; 
    protected:
    double m_a ,m_b;
    unsigned int passi; 
};
class middlepoint : private integratore {
    public:
    double integrale(const funzione& f ,double a,double b,int pass)override{
        double h =(b-a)/pass;
        double somma;
        double calcinx=0;
        for(int i =0;i<pass;i++){
            calcinx+=val(a+((i+0.5)*h));

        }
    }
}



#endif // __CAMPO__