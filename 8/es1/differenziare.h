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

#endif
