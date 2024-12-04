#ifndef __EquazioniDifferenziali_h__
#define __EquazioniDifferenziali_h__

#include "vectorop.h" 
#include <cmath>

using namespace std;

// ===========================================================================
// classe astratta, restituisce la derivata valutata nel punto x
// ===========================================================================

class FunzioneVettorialeBase {

public:
  virtual vector<double> Eval(double t, const vector<double> & x) const = 0;
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

#endif
