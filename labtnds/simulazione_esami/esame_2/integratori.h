#ifndef __INTEGRATORI__
#define __INTEGRATORI__

#include<vector>
#include <cmath>
#include <iostream>
#include "funzioni.h"
#include"vectorop.h"
#include"rand.h"

class Solutore {
public:
    Solutore() : m_a(0), m_b(0), m_prec(0.0001), m_nmax(100000), m_niterations(0) {}
    explicit Solutore(double perc) : m_a(0), m_b(0), m_prec(perc), m_nmax(1000), m_niterations(100000) {}
    virtual ~Solutore() = default;

    virtual double cercaZeri(double xmin, double xmax, const Funzione& f) = 0;
    
    void setPrecisione(double epsilon) { m_prec = epsilon; }
    double getPrecisione() const { return m_prec; }
    void setNMaxIterations(unsigned int n) { m_nmax = n; }
    unsigned int getNMaxIterations() const { return m_nmax; }
    void setA(double a) { m_a = a; }
    void setB(double b) { m_b = b; }
    double getA() const { return m_a; }
    double getB() const { return m_b; }
    unsigned int getNIterations() const { return m_niterations; }

protected:
    double m_a, m_b, m_prec;
    unsigned int m_nmax, m_niterations;
};

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

class EquazioneDifferenzialeBase {

public:
  virtual vector<double> Passo(double t, const vector<double>& x, double h, const FunzioneVettorialeBase &f) const =0;
};

class Bisezione : public Solutore {
public:
    using Solutore::Solutore;
    virtual ~Bisezione() = default;

    double cercaZeri(double xmin, double xmax, const Funzione& f) override {
        double a = xmin, b = xmax, parziale = 0;
        int iter = 0;

        if (f.sign(f.val(a)) * f.sign(f.val(b)) < 0) {
            while ((b - a > m_prec) && (iter < m_nmax)) {
                parziale = (a + b) / 2;
                if (std::abs(f.val(parziale)) < m_prec) break;
                (f.sign(f.val(a)) != f.sign(f.val(parziale))) ? b = parziale : a = parziale;
                iter++;
            }
        } else {
            std::cout << "Intervallo non valido" << std::endl;
        }

        setA(a);
        setB(b);
        return parziale;
    }
};

class Integratore {
public:
    virtual ~Integratore() = default;
    void setErrore(double err) { m_err = err; };
    double getErrore(){return m_err;};
    virtual double integrale(const Funzione& f, double a, double b, int passi) = 0;
    virtual double integraleErr(const Funzione& f, double a, double b, double err) = 0;
protected:
    double m_a, m_b, m_err;
    unsigned int m_passi;
};

class MiddlePoint : public Integratore {
public:
    double integrale(const Funzione& f, double a, double b, int passi) override {
        double h = (b - a) / passi, somma = 0;
        for (int i = 0; i < passi; ++i) {
            somma += f.val(a + (i + 0.5) * h);
        }
        setErrore(h * h);
        return somma * h;
    }
};

class Simpson : public Integratore {
public:
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
        setErrore(h*h*h*h);
        calcinx*=h;
        return calcinx;
    };
};

class Trapezi : public Integratore {
public:
    double integrale(const Funzione& f, double a, double b, int passi) override {
        double h = (b - a) / passi, somma = 0.5 * (f.val(a) + f.val(b));
        for (int i = 1; i < passi; ++i) {
            somma += f.val(a + i * h);
        }
        setErrore(h * h);
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
        setErrore(errore);
        std::cout << "Iterazioni: " << iterazioni << std::endl;
        return risultatoPrecedente;
    }
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


// integratore concreto, metodo di Eulero

class Eulero : public EquazioneDifferenzialeBase {

 public:

  virtual vector<double> Passo(double t, const vector<double> & x, double h, const FunzioneVettorialeBase &f) const override {

    return x+(f.Eval(t,x)*h);

  };

};
class RungeKutta : public EquazioneDifferenzialeBase {
  public:

  virtual vector<double> Passo(double t, const vector<double> & x, double h, const FunzioneVettorialeBase &f) const override{
    vector<double> k1{f.Eval(t,x)};
    vector<double> k2{f.Eval(t+(h/2),x+(k1*(h/2)))};    
    vector<double> k3{f.Eval(t+(h/2),x+(k2*(h/2)))};   
    vector<double> k4{f.Eval(t+h,x+(k3*(h)))}; 
    return x+(double(h/6.)*(k1+(k2*2.)+(k3*2.)+k4));
  };
};

#endif // __INTEGRATORI__



