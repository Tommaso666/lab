#ifndef __rand__
#define __rand__
                                                                                      
#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>  // se se vogliono usare algoritmi STL
#include <numeric>    // per inner_product
#include"funzioni.h"

using namespace std;

class randomGen{
    public:
        randomGen(unsigned int seed){m_seed = seed; m_a = 1664525;m_c = 1013904223;m_m=pow(2,31); }

        double rand(){
            m_seed=((m_a*m_seed)+(m_c))%m_m;
            //m_seed=app;
            return double(m_seed)/m_m;
        };

        double Unif(double a ,double b){
//            double rit=rand();
//            while(rit>b && rit <a){rit=rand();};
//            return rit;
              return a + (b-a) * rand() ;   
        };
        double esponenziale(double Y){
            return -(1/Y)*log(1-rand());
        };
        double gauss(double media, double sigma) {
            double s=rand();
            double t=rand();
            double x=sqrt(-2.*log(1.-s))*cos(2.*M_PI*t);
            return media+x*sigma; 
        };
        double aceptreg(double a, double b,double maxf,funzione &f){
            double x,y;
            do{
                x=a+(b-a)*rand();
                y=maxf*rand();
            }while(y>f.val(x));
            return y;
        };
    private:
        unsigned int m_seed;
        unsigned int m_a,m_c,m_m;
};
class IntegraleMC {

public:

  IntegraleMC(unsigned int seed) : 
    m_gen(seed)
  {
    m_errore = 0;
    m_punti  = 0;
  }

  virtual double Integra( const funzione& f, double inf , double sup , unsigned int punti, double fmax ) = 0 ;

  double GetErrore() const {return m_errore;}
  unsigned int GetN() const {return m_punti;}

protected:

  randomGen m_gen;
  double m_errore;
  unsigned int m_punti;

};

class IntegratoreMedia : public IntegraleMC {

public:

  IntegratoreMedia(unsigned int seed) : IntegraleMC(seed) { ; };

  virtual double Integra ( const funzione& f, double inf , double sup , unsigned int punti, double fmax ) {
    double somma=0;
    for(int k=0;k<punti;k++){
        somma=somma+f.val(m_gen.Unif(inf,sup));
    }
    
return (sup-inf)*(somma/punti);
  };

};
class hitmis :public IntegraleMC{
    hitmis(unsigned int seed) : IntegraleMC(seed) { ; };
     virtual double Integra ( const funzione& f, double inf , double sup , unsigned int punti, double fmax ) {
        int Ng,Nt=0;
        for(int i=0;i<punti;i++,Nt++){if(m_gen.Unif(0,fmax)<f.val(m_gen.Unif(inf,sup))){Ng++;};
        return (sup-inf)*fmax*double(Ng/Nt);

        }

     }
};

#endif // __rand__
