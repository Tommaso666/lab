#ifndef __rand__
#define __rand__

#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm> // se se vogliono usare algoritmi STL
#include <numeric>   // per inner_product
#include "funzioni.h"

using namespace std;

class randomGen
{
public:
  randomGen(unsigned int seed)
  {
    m_seed = seed;
    m_a = 1664525;
    m_c = 1013904223;
    m_m = pow(2, 31);
  }

  double rand()
  {
    m_seed = ((m_a * m_seed) + (m_c)) % m_m;
    // m_seed=app;
    return double(m_seed) / m_m;
  };
  double Unif(double a, double b)
  {
    //            double rit=rand();
    //            while(rit>b && rit <a){rit=rand();};
    //            return rit;
    return a + (b - a) * rand();
  };
  double esponenziale(double Y)
  {
    return -(1 / Y) * log(1 - rand());
  };
  double gauss(double media, double sigma)
  {
    double s = rand();
    double t = rand();
    double x = sqrt(-2. * log(1. - s)) * cos(2. * M_PI * t);
    return media + x * sigma;
  };
  double aceptreg(double a, double b, double maxf, Funzione &f)
  {
    double x, y;
    do
    {
      x = a + (b - a) * rand();
      y = maxf * rand();
    } while (y > f.val(x));
    return y;
  };

private:
  unsigned int m_seed;
  unsigned int m_a, m_c, m_m;
};
#endif //__rand__