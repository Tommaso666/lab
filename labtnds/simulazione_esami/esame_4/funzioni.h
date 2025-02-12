#ifndef __FUNZIONI__
#define __FUNZIONI__

#include <cmath>
#include <iostream>
#include <vector>
#include "vectorop.h"

// Classi astratte
class Funzione {
public:
    virtual double val(double x) const = 0;
    virtual ~Funzione() {};

    int sign(double x)const {
        if (x < 0)
            return -1;
        else
            return 1;
    };
};

class FunzioneVettorialeBase {

public:
  virtual vector<double> Eval(double t, const vector<double> & x) const = 0;
};

// Classe seno
class Seno : public Funzione {
public:
    Seno() : m_an(0), m_a(1), m_exp(0) {}
    Seno(double an) : m_an(an), m_a(1), m_exp(0) {}
    Seno(double an, double exp) : m_an(an), m_a(1), m_exp(exp) {}

    double val(double x) const override { return std::pow(x, m_exp) * m_a * std::sin(x + m_an); }
    double getPhi() const { return m_an; }
    void setPhi(double an) { m_an = an; }

private:
    double m_an, m_a, m_exp;
};

// Classe coseno
class Coseno : public Funzione {
public:
    Coseno() : m_an(0), m_a(1) {}
    Coseno(double an) : m_an(an), m_a(1) {}

    double val(double x) const override { return m_a * std::cos(x + m_an); }
    double getPhi() const { return m_an; }
    void setPhi(double an) { m_an = an; }

private:
    double m_an, m_a;
};

// Classe tangente
class Tangente : public Funzione {
public:
    Tangente() : m_an(0), m_a(1) {}
    Tangente(double an) : m_an(an), m_a(1) {}

    double val(double x) const override { return m_a * std::tan(x + m_an); }
    double getPhi() const { return m_an; }
    void setPhi(double an) { m_an = an; }

private:
    double m_an, m_a;
};

// Classe parabola
class Parabola : public Funzione {
public:
    Parabola() : m_a(1), m_b(0), m_c(0) {}
    Parabola(double a, double b, double c) : m_a(a), m_b(b), m_c(c) {}

    double val(double x) const override { return (m_a * x * x) + (m_b * x) + m_c; }

    void setA(double a) { m_a = a; }
    void setB(double b) { m_b = b; }
    void setC(double c) { m_c = c; }
    double getA() const { return m_a; }
    double getB() const { return m_b; }
    double getC() const { return m_c; }
    
    double getVertice() const { return (m_a != 0) ? -m_b / (2 * m_a) : 0; }

private:
    double m_a, m_b, m_c;
};

// caso fisico concreto, oscillatore armonico
class OscillatoreArmonico : public FunzioneVettorialeBase {
public:
  OscillatoreArmonico(double omega0) {  m_omega0 = omega0;  } ;

  virtual vector<double> Eval(double t, const vector<double> & x) const {
  double app = x[1];
  vector<double> rit(x.size());
  rit[0]=app;
  rit[1]=-(m_omega0*m_omega0)*x[0];
  return rit;
  };

 private:
  double m_omega0;  
};
class OscillatoreArmonicoforz : public FunzioneVettorialeBase {
public:
  OscillatoreArmonicoforz(double omega0/* pulsazione propria*/,double alpha/*smorzamento*/,double omega/*forzantes*/) {  m_omega0 = omega0; m_alpha=alpha; m_omega=omega; } ;
  void setsmorzante(double smorzante){m_alpha=smorzante;};
  virtual vector<double> Eval(double t, const vector<double> & x) const {
  double app = x[1];
  vector<double> rit(x.size());
  rit[0]=app;
  rit[1]=(-(m_omega0*m_omega0)*x[0]-(m_alpha*app)+sin(m_omega*t));
  return rit;
  };

 private:
  double m_omega0;  //pulsazione propria
  double m_alpha;   //smorzante
  double m_omega;   //forzante
};
class pendol0 :public FunzioneVettorialeBase{
  public:
  pendol0(double omega0) {  m_omega0 = omega0;  } ;

  virtual vector<double> Eval(double t, const vector<double> & x) const {
  double app = x[1];
  vector<double> rit(x.size());
  rit[0]=app;
  rit[1]=-(m_omega0*m_omega0)*sin(x[0]);
  return rit;
  };

   private:
  double m_omega0;  

};
// visto che il diavolo è tanto fino
class OscillatoreBidimensionale : public FunzioneVettorialeBase {
    public:
        OscillatoreBidimensionale(double omega0, double alpha) 
          : m_omega0(omega0), m_alpha(alpha),m_addizione(0.) { }
    
        virtual vector<double> Eval(double t, const vector<double>& X) const override {
            // X[0]=x, X[1]=v_x, X[2]=y, X[3]=v_y
            double r=sqrt((X[0]*X[0])+(X[2]*X[2]));
            double B = 1.0 / pow(r, m_alpha);
            vector<double> dX(4);
            dX[0] = X[1];
            dX[1]= -(B+m_addizione)*X[3];
            dX[2] = X[3];
            dX[3]=(B+m_addizione)*X[1];

            return dX;
        }
    
        // Se ti serve modificare il parametro alpha (come nel cambio da +2 a -2)
        void setAlpha(double alpha) { m_alpha = alpha; };
        void setaddizione(double addendo){m_addizione=addendo;};
    
    private:
        double m_omega0;
        double m_alpha;
        double m_addizione;
    };
    

//funzioni non std per simulazioni di esame
class Xcubo :public Funzione {
    public:
    Xcubo(){};
    double val(double x) const override {
        double risultato = (x*x*x)*log(sqrt(M_E+(x*x)));
        return risultato;
    }

};
class fratta :public Funzione{
    public:
    fratta(){};
    double val(double x) const override {
        return (1./sqrt(4-(x*x)));
    }
};
// Classe per l'integranda
class integranda : public Funzione {
    public:
        integranda(double lambda, double L,double d) : m_lambda(lambda), m_L(L), m_x(0),m_d(d) {}  // Inizializza m_x
    
        double val(double t) const override {
            double app=(1./m_d)*cos((1./m_lambda)*(sqrt((m_L*m_L)+pow(m_x-t,2.))-sqrt((m_L*m_L)+(m_x*m_x))));
            
            return app;
        }
    
        void set_x(double x) const { m_x = x; };  // Setter per x
        double getD()const {return m_d;};
        void set_lambda(double lambda) { m_lambda = lambda ; };
    private:
        double m_lambda, m_L, m_d;
        //grazie sign. serraino
        mutable double m_x;
    };
    

#endif // __FUNZIONI__