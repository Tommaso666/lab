#ifndef __prisma__
#define __prisma__
#include "differenziare.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include"random.h"
#include <omp.h>

#include "funzioni.h"
#include "funzionivector.h"

class EsperimentoPrisma {

 public :

  EsperimentoPrisma( unsigned int seed ) ;
  ~EsperimentoPrisma() {;} ;

  void Esegui(){
    
    m_th0_misurato = m_rgen.gauss(m_th0_input,m_sigmat);

    m_th1_misurato = m_rgen.gauss(m_th1_input,m_sigmat);
    
    m_th2_misurato = m_rgen.gauss(m_th2_input,m_sigmat);  
 
  } ;
  void Analizza() {

    m_dm1_misurato = m_th1_misurato - m_th0_misurato ;

    m_dm2_misurato = m_th2_misurato - m_th0_misurato ;

    m_n1_misurato = sin((m_dm1_misurato + m_alpha) / 2.0) / sin(0.5 * m_alpha);
  
    m_n2_misurato = sin((m_dm2_misurato + m_alpha) / 2.0) / sin(0.5 * m_alpha);

    m_B_misurato = (pow(m_n2_misurato, 2) - pow(m_n1_misurato, 2)) / (1.0 / pow(m_lambda2, 2) - 1.0 / pow(m_lambda1, 2));

    m_A_misurato = pow(m_n1_misurato, 2) - m_B_misurato / pow(m_lambda1, 2);

}

// accesso ai membri privati in output
double getAMisurato() { return m_A_misurato; };
double getBMisurato() { return m_B_misurato; };
double getN1Misurato() { return m_n1_misurato; };
double getN2Misurato() { return m_n2_misurato; };
double getDm1Misurato() { return m_dm1_misurato; };
double getDm2Misurato() { return m_dm2_misurato; };
double getTh0Misurato() { return m_th0_misurato; };
double getTh1Misurato() { return m_th1_misurato; };
double getTh2Misurato() { return m_th2_misurato; };

// accesso alle condizioni iniziali
double getAInput() { return m_A_input; };
double getBInput() { return m_B_input; };
double getN1Input() { return m_n1_input; };
double getN2Input() { return m_n2_input; };
double getDm1Input() { return m_dm1_input; };
double getDm2Input() { return m_dm2_input; };
double getTh0Input() { return m_th0_input; };
double getTh1Input() { return m_th1_input; };
double getTh2Input() { return m_th2_input; };
double getsigma(){return m_sigmat;};


// per impostare i dati in imput
void setsigma(double value) {m_sigmat=value;};
void setAInput(double value) { m_A_input = value; };
void setBInput(double value) { m_B_input = value; };
void setN1Input(double value) { m_n1_input = value; };
void setN2Input(double value) { m_n2_input = value; };
void setDm1Input(double value) { m_dm1_input = value; };
void setDm2Input(double value) { m_dm2_input = value; };
void setTh0Input(double value) { m_th0_input = value; };
void setTh1Input(double value) { m_th1_input = value; };
void setTh2Input(double value) { m_th2_input = value; };


  



 private:

  // generatore di numeri casuali

  randomGen m_rgen ;

  // parametri dell'apparato sperimentale

  double m_lambda1, m_lambda2, m_alpha, m_sigmat;

  // valori delle quantita' misurabili :
  // input    : valori assunti come ipotesi nella simulazione
  // misurato : valore dopo la simulazione di misura 

  double m_A_input, m_A_misurato;
  double m_B_input, m_B_misurato;
  double m_n1_input, m_n1_misurato;
  double m_n2_input, m_n2_misurato;
  double m_dm1_input, m_dm1_misurato;
  double m_dm2_input, m_dm2_misurato;
  double m_th0_input, m_th0_misurato;
  double m_th1_input, m_th1_misurato;
  double m_th2_input, m_th2_misurato;

};



//costruttore
EsperimentoPrisma::EsperimentoPrisma( unsigned int seed ) :
  m_rgen( seed ),
  m_lambda1(579.1E-9),
  m_lambda2(404.7E-9),
  m_alpha(60.*M_PI/180.),
  m_sigmat(0.3E-3),
  m_A_input(2.7),
  m_B_input(60000E-18)
{

  // calcolo degli indici di rifrazione attesi

  m_n1_input = sqrt( m_A_input + m_B_input / (m_lambda1*m_lambda1) ) ;
  m_n2_input = sqrt( m_A_input + m_B_input / (m_lambda2*m_lambda2) ) ;

  // theta0 e' arbitrario, scelgo M_PI/2.

  m_th0_input = M_PI/2. ;

  // determino theta1 e theta2 

  m_dm1_input = 2.*asin( m_n1_input * sin (0.5 * m_alpha) ) - m_alpha ;
  
  m_dm2_input = 2.*asin( m_n2_input * sin (0.5 * m_alpha) ) - m_alpha ;

  m_th1_input = m_th0_input + m_dm1_input ;

  m_th2_input = m_th0_input + m_dm2_input ;

}




#endif