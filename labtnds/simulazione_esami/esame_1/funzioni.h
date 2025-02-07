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
  OscillatoreArmonicoforz(double omega0,double alpha,double omega) {  m_omega0 = omega0; m_alpha=alpha; m_omega=omega; } ;

  virtual vector<double> Eval(double t, const vector<double> & x) const {
  double app = x[1];
  vector<double> rit(x.size());
  rit[0]=app;
  rit[1]=(-(m_omega0*m_omega0)*x[0]-(m_alpha*app)+sin(m_omega*t));
  return rit;
  };

 private:
  double m_omega0;  
  double m_alpha;
  double m_omega;
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
}
#endif // __FUNZIONI__