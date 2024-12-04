#ifndef __particella__
#define __particella__

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class Particella {
public:
    // costruttori
    Particella() : m_massa(0), m_carica(0) {}
    Particella(double massa, double carica) : m_massa(massa), m_carica(carica) {}

    // distruttore
    virtual ~Particella() {}

    // metodi
    double GetMassa() const { return m_massa; }
    double GetCarica() const { return m_carica; }
    virtual void Print() const {
        std::cout << "Particella: m=" << m_massa
                  << ", q=" << m_carica
                  << std::endl;
    }

protected:
    double m_massa;
    double m_carica;
};

class Elettrone : public Particella {
public:
    // costruttore
    Elettrone() : Particella(9.1093826E-31, -1.60217653E-19) {}

    // distruttore
    ~Elettrone() override {}

    void Print() const override {
        std::cout << "Elettrone: m=" << m_massa
                  << ", q=" << m_carica
                  << std::endl;
    }
};

#endif // __particella__

