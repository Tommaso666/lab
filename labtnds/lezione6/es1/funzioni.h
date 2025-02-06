// controloli di inclusione
#ifndef __campo__
#define __campo__
//librerie

#include<cmath>
#include<iostream>

// funzioni

class funzione{
    public:
    virtual double val(double x)const=0;
    virtual~funzionbase(){;};
    int sign(double x){
        if(x<0)
            return -1;
        else
            return 1;
    };
};
class parabola : public funzione {
    // costruttori
    parobola(){m_a=0;m_b=0;m_c=1;};
    parobola(double a,double b, double c){m_a=a;m_b=b;m_c=c;};
    ~parabola(){;};
    // funzioni con parabola
    virtual double val(double x)const override{return (m_a*x*x)+(m_b*x)+m_c};
    void seta(double a){m_a=a;};
    void setb(double a){m_b=a;};
    void setc(double a){m_c=a;};
    double geta()const{return m_a;};
    double getb()const{return m_b;};
    double getc()const{return m_c;};
    double getvertice()const{return -m_b/(2*m-a);};
    private:
    double m_a,m_b,m_c;
    

}


// metodo di soluzione
class sol {
    public:
//costruttori
solutore();
solutore(double perc);

virtual ~sol(){;};

virtual double CercaZeriPointer(double xmin ,double xmax ,const FunzioneBase* f,double prec = 0.001,unsigned int nmax = 100) = 0;
 void SetPrecisione(double epsilon) { m_prec = epsilon; }
  double GetPrecisione() { return m_prec;}

  void SetNMaxiterations(unsigned int n ) { m_nmax = n ; }
  unsigned int GetNMaxiterations () { return m_nmax ; } ;

  unsigned int GetNiterations () { return m_niterations ; } ;


protected:
double m_a,m_b,m_prec;
unsigned int m_nmax;
unsigned int m_niterations;
}




//classi oluzione concrete
class bisezione : public Sol {

 public:

  bisezione() {} ;
  bisezione(double prec );
  virtual ~bisezione();


  virtual double cercazeri((double xmin ,double xmax ,const funzione* f,double prec = 0.001,unsigned int nmax = 1000)){
    double a= (xmin);
    double b =(xmax);
    //dimezzo gli intervali
    double parziale=0;
  int fermati=0;
    if(sing(val(a))*sing(val(b))<0){
          while(b-a>prec){
            if(fermati=nmax){break;}
            parziale =(a+b)/2;
        if(val(parziale)=0){
            return parziale;
        }else{ if(sing(val(a)!=sing(val(parziale)))){b=parziale;

        }else{a=parziale;};
        fermati++;

  };
  };
  }else cout << "intervallo non valido "<< endel;




  } ;
}
#endif // __campo__