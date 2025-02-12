#ifndef __prisma__
#define __prisma__
#include "integratori.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include"rand.h"
#include <omp.h>

#include "funzioni.h"
#include "vectorop.h"

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

class capacitor{
  public:
  capacitor(unsigned int seed) :my_gen(seed){
    m_time=(m_cpacity*m_resistance*log(m_voltage_max/m_voltage_min));
  };
  ~capacitor(){;};
  //void cambia i parametri iniziali
  void setcapacity(double capacity){m_cpacity=capacity;
    m_time=(m_cpacity*m_resistance*log(m_voltage_max/m_voltage_min));};
  void setresistance(double resistance){m_resistance=resistance;
    m_time=(m_cpacity*m_resistance*log(m_voltage_max/m_voltage_min));}
  void setvoltagemax(double voltage){m_voltage_max=voltage;
    m_time=(m_cpacity*m_resistance*log(m_voltage_max/m_voltage_min));};
  void setvoltage(double voltage){m_voltage_min=voltage;
    m_time=(m_cpacity*m_resistance*log(m_voltage_max/m_voltage_min));};
  //metodi di get
  double getCapacity() const {return m_cpacity;}
  double getResistance() const {return m_resistance;}
  double getVoltageMax() const {return m_voltage_max;}
  double getVoltageMin() const {return m_voltage_min;}
  double getTime() const {return m_time;}
  double getCapacity_simulated() const {return m_cpacity_simulated;}
  double getResistance_simulated() const {return m_resistance_simulated;}
  double getVoltageMax_simulated() const {return m_voltage_max_simulated;}
  double getVoltageMin_simulated() const {return m_voltage_min_simulated;}
  double getTime_simulated() const {return m_time_simulated;}
  // metodi per gli errori
  double getErrorResistance() const {return m_error_resistance;}
  double getErrorVoltageMax() const {return m_error_voltage_max;}
  double getErrorVoltageMin() const {return m_error_voltage_min;}
  double getErrorTime() const {return m_error_time;}
  // Metodi set per gli errori
  void setErrorResistance(double error) {m_error_resistance = error;}
  void setErrorVoltageMax(double error) {m_error_voltage_max = error;}
  void setErrorVoltageMin(double error) {m_error_voltage_min = error;}
  void setErrorTime(double error) {m_error_time = error;}
  // metodi di esecuzione
  void esegui(){
    double error=m_error_resistance/100.;
    double error1=m_error_voltage_max/100.;
    double error2=m_error_voltage_min/100.;
    double error3=m_error_time/100.;
    if(m_error_resistance!=0){
      m_resistance_simulated=my_gen.gauss(m_resistance,(m_resistance*error));
    }else{m_resistance_simulated = m_resistance;};
    if(m_error_voltage_max!=0){
      m_voltage_max_simulated=my_gen.gauss(m_voltage_max,(m_voltage_max*error1));
    }else{m_voltage_max_simulated=m_voltage_max;};
    if(m_error_voltage_min!=0){
      m_voltage_min_simulated=my_gen.gauss(m_voltage_min,m_voltage_min*error2);
    }else{m_voltage_min_simulated=m_voltage_min;};
    if(m_error_time!=0){
      m_time_simulated=my_gen.gauss(m_time,m_time*error3);
    }else{m_time_simulated=m_time;};
    m_cpacity_simulated=(m_time_simulated/(m_resistance_simulated*log(m_voltage_max_simulated/m_voltage_min_simulated)));
  };

  private:
  randomGen my_gen;
  double m_cpacity =0.000002, m_resistance=100000 , m_voltage_max=12 ,m_voltage_min=3 ; //condizioni iniziali che impostero ai valori dati 
  double m_cpacity_simulated, m_resistance_simulated , m_voltage_max_simulated ,m_voltage_min_simulated ; //condizioni da simulare
  double m_time ,m_time_simulated;
  double m_error_resistance=3.,m_error_voltage_max=3.,m_error_voltage_min=3.,m_error_time = 3.;
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