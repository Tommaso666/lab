#ifndef __INTEGRATORI__
#define __INTEGRATORI__

#include<vector>
#include <cmath>
#include <iostream>
#include "funzioni.h"
#include"vectorop.h"
#include"rand.h"
using namespace std;



// metodo di soluzione
class solutore {
public:
    // costruttori
    solutore() : m_a(0), m_b(0), m_prec(0.0001), m_nmax(100000), m_niterations(0) {};
    solutore(double perc) : m_a(0), m_b(0), m_prec(perc), m_nmax(1000), m_niterations(100000) {};

    virtual ~solutore(){};

    virtual double cercazeri(double xmin, double xmax, const Funzione& f) = 0;
    void SetPrecisione(double epsilon) { m_prec = epsilon; };
    double GetPrecisione() const { return m_prec; };

    void SetNMaxiterations(unsigned int n) { m_nmax = n; };
    unsigned int GetNMaxiterations() const { return m_nmax; };

    void setA(double a) { m_a = a; };
    void setB(double b) { m_b = b; };
    double getA() const { return m_a; };
    double getB() const { return m_b; };
    unsigned int GetNiterations() const { return m_niterations; };

protected:
    double m_a, m_b, m_prec;
    unsigned int m_nmax;
    unsigned int m_niterations;
};

// classi di soluzione concrete

class bisezione : public solutore {
  public:
    bisezione() : solutore() {};
    bisezione(double prec) : solutore(prec) {};
    bisezione(double prec, double nmax) : solutore(prec) { m_nmax = nmax; };
    virtual ~bisezione() {};

    virtual double cercazeri(double xmin, double xmax, const Funzione& f) override {
        double a = xmin;
        double b = xmax;
        double parziale = 0;
        int fermati = 0;

        if (f.sign(f.val(a)) * f.sign(f.val(b)) < 0) {
            while (b - a > m_prec && fermati < m_nmax) {
                parziale = (a + b) / 2;
                if (f.val(parziale) == 0) {
                    break;
                } else if (f.sign(f.val(a)) != f.sign(f.val(parziale))) {
                    b = parziale;
                } else {
                    a = parziale;
                }
                fermati++;
            }
        } else {
        cout << "Intervallo non valido " << std::endl;
        }

        setA(a);
        setB(b);
        return parziale;
    }
};

// integratori
class integratore {
    public:
    void seterr(double err){m_err=err;};
    virtual double integrale(const Funzione& f ,double a,double b,int pass) = 0;
    virtual double integraleErr(const Funzione& f, double a, double b, double err) = 0;
    virtual ~integratore() {}; 
    protected:
    double m_a ,m_b;
    unsigned int passi;
    double m_err;
};
class middlepoint : public integratore {
    public:
    middlepoint(){};
    double integrale(const Funzione& f ,double a,double b,int pass) override{
        double h =(b-a)/pass;
        double somma;
        double calcinx=0;
        if(a>b){cout<<"il valore del integrale da ("<<a<<" ; "<<b<<") equivale ad -integrale da ("<<b<<" ; "<<a <<") controlla se il valore è quello che cercavi"<<endl;};
        for(int i =0;i<pass;i++){
            calcinx+=f.val(a+((i+0.5)*h));
        }
      
        calcinx*=h;
        return calcinx;
    };
    double integraleErr(const Funzione& f, double a, double b, double err) override {
      unsigned int passi = 2;
      double errore = 1e9, risultatoPrecedente = integrale(f, a, b, passi);
      int iterazioni = 0;
      do {
          passi *= 2;
          double risultato = integrale(f, a, b, passi);
          errore = (4./3.)*abs(risultato - risultatoPrecedente);
          risultatoPrecedente = risultato;
          iterazioni++;
          if (iterazioni > 20) break;
      } while (errore > err);
      //superfluo ma se otteniamo un risultato migliore dell'atteso di molto sarebbe interessante saperlo
      seterr(errore);
      std::cout << "Iterazioni: " << iterazioni << std::endl;
      return risultatoPrecedente;

}

};
class middleright : public integratore {
    public:
    middleright(){};
    double integrale(const Funzione& f ,double a,double b,int pass) override{
        double h =(b-a)/pass;
        double somma;
        double calcinx=0;
        if(a>b){cout<<"il valore del integrale da ("<<a<<" ; "<<b<<") equivale ad -integrale da ("<<b<<" ; "<<a <<") controlla se il valore è quello che cercavi"<<endl;};
        for(int i =0;i<pass;i++){
            calcinx+=f.val(a+((i*h)));
        }
      
        calcinx*=h;
        return calcinx;
    };
    double integraleErr(const Funzione& f, double a, double b, double err) override {
    return integrale(f, a, b, 100);  // Esegue l'integrale con 100 passi arbitrari
}

};
class simson : public integratore {
    public:
    simson(){};
    double integrale(const Funzione& f ,double a,double b,int pass) override{
        double h =(b-a)/pass;
        double somma;
        double calcinx=0;
        if(a>b){cout<<"il valore del integrale da ("<<a<<" ; "<<b<<") equivale ad -integrale da ("<<b<<" ; "<<a <<") controlla se il valore è quello che cercavi"<<endl;};
        double app2=0;
        calcinx=(1./3)*f.val(a)+(1./3)*f.val(b);
        for(int i =1;i<pass;i++){
            if (i % 2 == 0) {
                app2=2./3; // Valore per numeri pari
            } else {
                app2=4./3; // Valore per numeri dispari
            }
            double appp=f.val(a+((i)*h));
            calcinx+=app2*appp;
        }
        seterr(h*h);
        calcinx*=h;
        return calcinx;
    };
    double integraleErr(const Funzione& f, double a, double b, double err) override {
      unsigned int passi = 2;
      double errore = 1e9, risultatoPrecedente = integrale(f, a, b, passi);
      int iterazioni = 0;
      do {
          passi *= 2;
          double risultato = integrale(f, a, b, passi);
          errore = (15./16.)*abs(risultato - risultatoPrecedente);
          risultatoPrecedente = risultato;
          iterazioni++;
          if (iterazioni > 20) break;
      } while (errore > err);
      //superfluo ma se otteniamo un risultato migliore dell'atteso di molto sarebbe interessante saperlo
      seterr(errore);
      std::cout << "Iterazioni: " << iterazioni << std::endl;
      return risultatoPrecedente;
}

};
class trapezi : public integratore {
    public:
    trapezi(){};
     double integrale(const Funzione& f, double a, double b, int passi) override {
        double h = (b - a) / passi, somma = 0.5 * (f.val(a) + f.val(b));
        for (int i = 1; i < passi; ++i) {
            somma += f.val(a + i * h);
        }
        seterr(h * h);
        return somma * h;
    }

    double integraleErr(const Funzione& f, double a, double b, double err) {
        unsigned int passi = 2;
        double errore = 1e9, risultatoPrecedente = integrale(f, a, b, passi);
        int iterazioni = 0;
        do {
            passi *= 2;
            double risultato = integrale(f, a, b, passi);
            errore = (4./3.)*abs(risultato - risultatoPrecedente);
            risultatoPrecedente = risultato;
            iterazioni++;
            if (iterazioni > 20) break;
        } while (errore > err);
        //superfluo ma se otteniamo un risultato migliore dell'atteso di molto sarebbe interessante saperlo
        seterr(errore);
        std::cout << "Iterazioni: " << iterazioni << std::endl;
        return risultatoPrecedente;
    };

    



};
//============================================================================
//integrali montecarlo
//============================================================================
class IntegraleMC
{

public:
  IntegraleMC(unsigned int seed) : m_gen(seed)
  {
    m_errore = 0;
    m_punti = 0;
  }

  virtual double Integra(const Funzione &f, double inf, double sup, unsigned int punti, double fmax) = 0;

  double GetErrore() const { return m_errore; }
  unsigned int GetN() const { return m_punti; }

protected:
  randomGen m_gen;
  double m_errore;
  unsigned int m_punti;
};

class IntegratoreMedia : public IntegraleMC
{
public:
  IntegratoreMedia(unsigned int seed) : IntegraleMC(seed) { ; };

  virtual double Integra(const Funzione &f, double inf, double sup, unsigned int punti, double fmax)
  {
    double somma = 0;
    for (int k = 0; k < punti; k++)
    {
      somma = somma + f.val(m_gen.Unif(inf, sup));
    }

    return (sup - inf) * (somma / punti);
  };
};

class hitmis : public IntegraleMC
{
public:
  hitmis(unsigned int seed) : IntegraleMC(seed) { ; };
  
  virtual double Integra(const Funzione &f, double inf, double sup, unsigned int punti, double fmax) override
  {
    int Ng, Nt = 0;
    for (int i = 0; i < punti; i++, Nt++)
    {
      if (m_gen.Unif(0, fmax) < f.val(m_gen.Unif(inf, sup)))
      {
        Ng++;
      };
    }
    return (sup - inf) * fmax * double(Ng / Nt);
  }
};


// ===========================================================================
// classe astratta per un integratore di equazioni differenziali
// ===========================================================================

class EquazioneDifferenzialeBase {

public:
  virtual vector<double> Passo(double t, const vector<double>& x, double h, const FunzioneVettorialeBase &f) const =0;
};

// integratore concreto, metodo di Eulero

class Eulero : public EquazioneDifferenzialeBase {

 public:

  virtual vector<double> Passo(double t, const vector<double> & x, double h, const FunzioneVettorialeBase &f) const override {

    return x+(f.Eval(t,x)*h);

  };

};
// questo scala come un h^4 
class RungeKutta : public EquazioneDifferenzialeBase {
  public:

  virtual vector<double> Passo(double t /*tempo*/, const vector<double> & x/*condizioni iniziali*/, double h/*passo*/, const FunzioneVettorialeBase &f/*comportamento*/) const override{
    vector<double> k1{f.Eval(t,x)};
    vector<double> k2{f.Eval(t+(h/2.),x+(k1*(h/2.)))};    
    vector<double> k3{f.Eval(t+(h/2.),x+(k2*(h/2.)))};   
    vector<double> k4{f.Eval(t+h,x+(k3*(h)))}; 
    return x+(double(h/6.)*(k1+(k2*2.)+(k3*2.)+k4));
  };
};


//=================================================================================
//con i metodi montecarlo è utile il calcolo della deviazione standard
//=================================================================================
template <typename T> double media_v(const vector<T> &x)
{
     double y,l=0;
    
    for ( int k= 0 ; k < x.size() ; k++ ) {
        l=l+x[k];
    }
    y=l/x.size();

     return y;
};

template <typename T> double deviazione_std(const vector<T> &x)
{
    double y,a,z =0;
    y=media_v(x);
    for (int i=0;i<x.size();i++){

    a=a+((x[i]-y)*(x[i]-y));
    };
  
    
    z=sqrt(a/x.size());
    return z;
};


#endif //__integratori__