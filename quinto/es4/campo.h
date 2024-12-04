#ifndef __campo__
#define __campo__
#include<cmath>
#include"punto.h"
#include "particella.h"


namespace Phyconst {

    // Costanti fondamentali
    constexpr double c = 2.99792458e8;           // Velocità della luce nel vuoto [m/s]
    constexpr double h = 6.62607015e-34;         // Costante di Planck [Js]
    constexpr double h_bar = 1.0545718e-34;      // Costante di Planck ridotta [Js]
    constexpr double e = 1.602176634e-19;        // Carica elementare [C]
    constexpr double G = 6.67430e-11;            // Costante di gravitazione universale [Nm^2/kg^2]
    constexpr double k_B = 1.380649e-23;         // Costante di Boltzmann [J/K]
    constexpr double N_A = 6.02214076e23;        // Costante di Avogadro [mol^-1]
    constexpr double R = 8.314462618;            // Costante dei gas [J/(mol K)]

    // Costanti elettromagnetiche
    constexpr double epsilon_0 = 8.854187817e-12;  // Permittività del vuoto [F/m]
    constexpr double mu_0 = 4.0 * 3.14159265358979323846e-7;  // Permeabilità del vuoto [N/A^2]
    constexpr double Z_0 = 376.730313668;          // Impedenza del vuoto [Ω]

    // Costanti atomiche
    constexpr double m_p = 1.67262192369e-27;     // Massa del protone [kg]
    constexpr double m_e = 9.1093837015e-31;      // Massa dell'elettrone [kg]
    constexpr double a_0 = 5.29177210903e-11;     // Raggio di Bohr [m]
    constexpr double R_inf = 10973731.568160;     // Costante di Rydberg [m^-1]
    constexpr double u = 1.66053906660e-27;       // Unità di massa atomica [kg]

    // Costanti cosmologiche
    constexpr double Lambda = 1e-35;              // Costante cosmologica (esempio) [m^-2]
    constexpr double H_0 = 67.4;                  // Parametro di Hubble attuale [km s^-1 Mpc^-1]

    // Costanti termodinamiche
    constexpr double T_P = 1.416784e32;           // Temperatura di Planck [K]
    constexpr double l_P = 1.616255e-35;          // Lunghezza di Planck [m]

} // namespace PhysicalConstants


class CampoVettoriale : public Posizione {
    public:
// esempi di possibili costruttori
  CampoVettoriale(const Posizione& p):Posizione(p),m_Fx(0),m_Fy(0),m_Fz(0){};
  CampoVettoriale(const Posizione&p, double Fx, double Fy, double Fz):Posizione(p), m_Fx(Fx), m_Fy(Fy), m_Fz(Fz){};
  CampoVettoriale(double x, double y, double z, double Fx, double Fy, double Fz):Posizione(x,y,z), m_Fx(Fx), m_Fy(Fy), m_Fz(Fz){};

 // operazioni 
  CampoVettoriale & operator+=( const CampoVettoriale & ) ;
  CampoVettoriale operator+( const CampoVettoriale & ) const;

// interfacce
  double getFx() const {return m_Fx;};
  double getFy() const {return m_Fy;};
  double getFz() const {return m_Fz;};

  void setFx(double Fx) { m_Fx=Fx;};
  void setFy(double Fy) { m_Fy=Fy;};
  void setFz(double Fz) { m_Fz=Fz;};

  double Modulo() const{
    double E=sqrt((m_Fx*m_Fx)+(m_Fy*m_Fy)+(m_Fz+m_Fz));
    return E;
  } ;

    private:

    double m_Fx, m_Fy, m_Fz;

};

CampoVettoriale CampoVettoriale::operator+( const CampoVettoriale & v ) const {  

  Posizione pos(getX(),getY(), getZ());
  CampoVettoriale sum( pos ) ; // creo un campo vettoriale nella posizione giusta
  sum.setFx( getFx() + v.getFx()) ;  
  sum.setFy( getFy() + v.getFy()) ;  
  sum.setFz( getFz() + v.getFz()) ;  
  return sum;
}

CampoVettoriale & CampoVettoriale::operator+=( const CampoVettoriale & v ) {
  return (*this) = (*this)+v;
}


// punto materialeCampoVettoriale
class PuntoMateriale :public Posizione ,public Particella{
    
public:

  // costruttori
  PuntoMateriale(double massa, double carica, const Posizione&P): Particella(massa, carica),Posizione(P){};


  PuntoMateriale(double massa, double carica, double x, double y, double z): Particella(massa, carica),Posizione(x,y,z){};


  ~PuntoMateriale() {;};

  // forze centrali
  CampoVettoriale CampoElettrico(const Posizione&p) const {

    double E=0;
    double r =sqrt(((p.getX() -getX())*(p.getX() -getX()))+((p.getY()-getY())*(p.getY()-getY()))+((p.getZ() -getZ())*(p.getZ() -getZ())));
    E=(1/(4*M_PI*(Phyconst::epsilon_0)))*GetCarica()/(r*r);
    // posos creare una funzione che faccia questo
    CampoVettoriale vett(p);
    // Calcola le componenti del campo elettrico    
    double theta=p.angoloPxz();
    double phi=p.angoloPxy();
    double x = E * sin(theta) * cos(phi);
    double y = E * sin(theta) * sin(phi);
    double z = E * cos(theta);
    vett.setFx(x);
    vett.setFy(y);
    vett.setFz(z);
      
  
  cout << "campo eletrico totale "<< E<< endl;
    // Imposta le componenti del vettore campo



    return vett;
  };

  CampoVettoriale CampoGravitazionale(const Posizione&p) const{
  CampoVettoriale vett(p);
  double E=0;
  double theta=p.angoloPxz();
  double phi=p.angoloPxy();
  double r =sqrt(((p.getX() -getX())*(p.getX() -getX()))+((p.getY()-getY())*(p.getY()-getY()))+((p.getZ() -getZ())*(p.getZ() -getZ())));
        E=((Phyconst::G)/(4*M_PI))*GetMassa()/(r*r);
    // Calcola le componenti del campo elettrico
    double x = E * sin(theta) * cos(phi);
    double y = E * sin(theta) * sin(phi);
    double z = E * cos(theta);  
    
    cout << "campo gravitazionale totale "<< E << endl;
    // Imposta le componenti del vettore campo
  vett.setFx(x);
  vett.setFy(y);
  vett.setFz(z);
      
        return vett;
  };




};



#endif // __campo__