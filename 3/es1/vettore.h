#ifndef __vettore__
#define __vettore__

#include <cmath>
#include <fstream>
#include <iostream>
#include <type_traits>

using namespace std;

// classe
template <typename T> class Vettore
{
    // controllo tipo classe
    static_assert(is_arithmetic<T>::value && "Voglio un tipo aritmetico");

  public:
    Vettore& operator=(const Vettore& V){
        std::cout << "Called Copy Assignement\n";
    } 

    Vettore()
    {
        m_N = 0;
        m_v = NULL;
    };

    Vettore(int n)
    {
        m_N = n;
        m_v = new T[n];
        for (int k = 0; k < n; k++)
            m_v[k] = 0;
    };

    ~Vettore()
    {
        delete [] m_v;
    };

    unsigned int GetN() const
    {
        return m_N;
    }; // dimensione del vettore

    void SetComponent(int k, T val)
    {
        m_v[k] = val;
    }; // valore del vettore

    T GetComponent(int k) const
    {
        return m_v[k];
    }; // dimmi il valore alla posizione k

  private:
    unsigned int m_N;
    T *m_v;
};

// funzioni

template <typename T> void importo_txt_v(char *, Vettore<T> &);
template <typename T> void duplicavet(Vettore<T> &, Vettore<T> &);
template <typename T> double media_v(const Vettore<T> &);
template <typename T> double varianza_v(const Vettore<T> &);
template <typename T> void riordinadati_v(Vettore<T> &);
template <typename T> T CalcolaMediana_v(const Vettore<T> &);
template <typename T> void stampa_txt_v(const Vettore<T> &, const char *filename);

//==========================================================================================================================================================
// testo funzioni
//==========================================================================================================================================================

template <typename T> void importo_txt_v(char *filename, Vettore<T> &a)
{
    ifstream fin(filename);
    T data;
    if (!fin)
    {
        cout << "Cannot open file " << filename << endl;
        exit(33);
    }
    else
    {
        for (int k = 0; k < a.GetN(); k++)
        {

            fin >> data;
            a.SetComponent(k, data);
            if (fin.eof())
            {
                cout << "End of file reached exiting" << endl;
                exit(33);
            }
        }
    }
}

template <typename T> void duplicavet(Vettore<T> &a, Vettore<T> &b)
{
    for (int i = 0; i < a.GetN(); i++)
    {
        ;
        b.SetComponent(i, a.GetComponent(i));
    };
}
template <typename T> double media_v(const Vettore<T> &a)
{
    double y, l = 0;

    for (int k = 0; k < a.GetN(); k++)
    {
        l = l + a.GetComponent(k);
    }
    y = l / a.GetN();

    return y;
}
template <typename T> double varianza_v(const Vettore<T> &x)
{
    double y, a, z = 0;
    y = media_v(x);
    for (int i = 0; i < x.GetN(); i++)
    {

        a = a + ((x.GetComponent(i) - y) * (x.GetComponent(i) - y));
    };

    z = sqrt(a / x.GetN());

    return z;
}
template <typename T> void riordinadati_v(Vettore<T> &x)
{
    int imin;
    double min;
    int n = x.GetN(); // Ottieni la dimensione del vettore

    for (int j = 0; j < n - 1; j++)
    {
        imin = j;                // Supponiamo che il minimo sia l'elemento corrente
        min = x.GetComponent(j); // Inizializza min con il valore alla posizione j

        // Cerca il valore minimo nel resto del vettore
        for (int i = j + 1; i < n; i++)
        {
            if (x.GetComponent(i) < min)
            {
                min = x.GetComponent(i); // Aggiorna il minimo
                imin = i;                // Aggiorna l'indice del minimo
            }
        }

        // Scambia l'elemento corrente con l'elemento minimo trovato
        double temp = x.GetComponent(j);
        x.SetComponent(j, x.GetComponent(imin));
        x.SetComponent(imin, temp);
    }
}

template <typename T> T CalcolaMediana_v(const Vettore<T> &y)
{
    double mediana;
    if (y.GetN() % 2 == 0)
    {
        // se pari
        mediana = (y.GetComponent(y.GetN() / 2 - 1) + y.GetComponent(y.GetN() / 2)) / 2.;
    }
    else
    {
        mediana = y.GetComponent(y.GetN() / 2);
    } // se dispari

    return mediana;
}
template <typename T> void stampa_txt_v(const Vettore<T> &v, const char *filename)
{

    cout << "creazione outstream\n";
    // funzione effettiva
    ofstream out(filename);
    if (!out)
    {
        cerr << "Non posso creare il file " << filename << endl;
        return;
    }
  


    for (int i = 0; i < v.GetN(); i++)
        out << v.GetComponent(i) << endl;
    
  
    
    out.close();
}

#endif //__vettore__
