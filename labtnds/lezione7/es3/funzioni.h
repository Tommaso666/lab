#ifndef __FunzioniMatematiche__
#define __FunzioniMatematiche__

// librerie
#include <cmath>
#include <iostream>

// funzioni
using namespace std;

class Funzione {
public:
    virtual double val(double x) const = 0;
    virtual ~Funzione() {};
    int sign(double x)const {
        if (x < 0)
            return -1;
        else
            return 1;
    }
};

class seno :public Funzione{
    public:
    seno():m_an(0),m_a(1),m_exp(0){};
    seno(double an):m_an(0) ,m_a(an),m_exp(0){};
    seno(double an,double exp):m_an(0) ,m_a(an),m_exp(exp){};
    virtual double val(double an)const override{return pow(an,m_exp)*m_a*sin(an+m_an);};
    double getphi()const{return m_an;};
    void setphi(double an){m_an=an;};
   ~seno(){};
    private:
    double m_an,m_a,m_exp;
};
class coseno :public Funzione {
        public:
    coseno():m_an(0),m_a(1){};
    coseno(double an):m_an(0) ,m_a(an){};
    virtual double val(double an)const override{return m_a*cos(an+m_an);};
    double getphi()const{return m_an;};
    void setphi(double an){m_an=an;};
   ~coseno(){};
    private:
    double m_an,m_a;

};
class tangente :public Funzione{
            public:
    tangente():m_an(0),m_a(1){};
    tangente(double an):m_an(0) ,m_a(an){};
    virtual double val(double an)const override{return m_a*tan(an+m_an);};
    double getphi()const{return m_an;};
    void setphi(double an){m_an=an;};
   ~tangente(){};
    private:
    double m_an,m_a;

};
class parabola : public Funzione {
public:
    // costruttori
    parabola() : m_a(0), m_b(0), m_c(1) {};
    parabola(double a, double b, double c) : m_a(a), m_b(b), m_c(c) {};
    ~parabola(){};

    // funzioni con parabola
    virtual double val(double x) const override { return (m_a * x * x) + (m_b * x) + m_c; };
    void seta(double a) { m_a = a; };
    void setb(double b) { m_b = b; };
    void setc(double c) { m_c = c; };
    double geta() const { return m_a; };
    double getb() const { return m_b; };
    double getc() const { return m_c; };
    double getvertice() const { return -m_b / (2 * m_a); };

private:
    double m_a, m_b, m_c;
};




#endif // __FunzioniMatematiche__
