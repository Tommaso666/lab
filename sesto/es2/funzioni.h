#ifndef __CAMPO__
#define __CAMPO__

// librerie
#include <cmath>
#include <iostream>

// funzioni
using namespace std;

class funzione {
public:
    virtual double val(double x) const = 0;
    virtual ~funzione() {};
    int sign(double x)const {
        if (x < 0)
            return -1;
        else
            return 1;
    }
};
class seno :public funzione{
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
class coseno :public funzione {
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
class tangente :public funzione{
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
class parabola : public funzione {
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

// metodo di soluzione
class solutore {
public:
    // costruttori
    solutore() : m_a(0), m_b(0), m_prec(0.0001), m_nmax(100000), m_niterations(0) {};
    solutore(double perc) : m_a(0), m_b(0), m_prec(perc), m_nmax(1000), m_niterations(100000) {};

    virtual ~solutore(){};

    virtual double cercazeri(double xmin, double xmax, const funzione& f) = 0;
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

    virtual double cercazeri(double xmin, double xmax, const funzione& f) override {
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
    virtual double integrale(const funzione& f ,double a,double b,int pass) = 0;
    virtual ~integratore() {}; 
    protected:
    double m_a ,m_b;
    unsigned int passi;
    double m_err;
};
class middlepoint : private integratore {
    public:
    middlepoint(){};
    double integrale(const funzione& f ,double a,double b,int pass) override{
        double h =(b-a)/pass;
        double somma;
        double calcinx=0;
        if(a>b){cout<<"il valore del integrale da ("<<a<<" ; "<<b<<") equivale ad -integrale da ("<<b<<" ; "<<a <<") controlla se il valore è quello che cercavi"<<endl;};
        for(int i =0;i<pass;i++){
            calcinx+=f.val(a+((i+0.5)*h));
        }
        seterr(h*h);
        calcinx*=h;
        return calcinx;
    };
};


#endif // __CAMPO__
