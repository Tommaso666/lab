#ifndef __vettore__
#define __vettore__
#include<algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> vector<T> importo_txt_v(const char *);
template <typename T> double media_v(const vector<T> &);
template <typename T> double varianza_v(const vector<T> &);
template <typename T> T CalcolaMediana_v( const vector<T> &);
template <typename T> void stampa_txt_v( const vector<T> &, const char *filename);
template <typename T> double min(const vector<T> &);
template <typename T> double max(const vector<T> &);
template <typename T> double varianza_vm(const vector<T> &);






template <typename T> vector<T> importo_txt_v(const char *filename)
{
    ifstream fin(filename);
    vector<T> v;
    T data;

    if (!fin) {
        cout << "Cannot open file " << filename << endl;
        exit(33);
    }
    
    while (fin >> data) {
        v.push_back(data);
    }
    
    return v;
}



template <typename T> double media_v(const vector<T> &x)
{
     double y,l=0;
    
    for ( int k= 0 ; k < x.size() ; k++ ) {
        l=l+x[k];
    }
    y=l/x.size();

     return y;
}
template <typename T> double varianza_v(const vector<T> &x)
{
    double y,a,z =0;
    y=media_v(x);
    for (int i=0;i<x.size();i++){

    a=a+((x[i]-y)*(x[i]-y));
    };
  
    
    z=sqrt(a/x.size());
    return z;
}

template <typename T> T CalcolaMediana_v( const vector<T> &y0)
{   
    vector<T> y = y0;
    sort(y.begin(),y.end());
    double mediana;
    if (y.size() % 2 == 0)
    {
        // se pari
        mediana = (y[((y.size() / 2) - 1)] + y[(y.size() / 2)]) / 2;
    }
    else
    {
        mediana = y[(y.size() / 2)];
    } // se dispari

    return mediana;
}
template <typename T> void stampa_txt_v( const vector<T> & y0  , const char* filename ) {
  ofstream out(filename);
  vector<T> y = y0;
    sort(y.begin(),y.end());
  if ( !out ) {
    cout << "Non posso creare il file " << filename << endl;
    return;
  }
  for (int i=0; i<y.size(); i++) out << y[i] << endl;
  out.close();
  return;
};
template <typename T> double varianza_vm(const vector<T> & v){
    double a=varianza_v<double>(v);
    a=a/sqrt(v.size());
    return a;
}
#endif //__vettore__