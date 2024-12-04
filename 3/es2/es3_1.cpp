#include <iostream>
#include <cstdlib>

#include <vector>

#include "algoritmiv.h"

using namespace std;
int main(int argc, char **argv)
{
    // intestazione
    if (argc < 3)
    {
        cout << "Uso del programma : " << argv[0] << " <n_data> <filename> " << endl;
        return -1;
    }
    // variabili
    int ndata = atoi(argv[1]);
    char *filename = argv[2];
    double mediana, M, V = 0;



    string outfilename(filename);
    outfilename.insert(outfilename.find_first_of(".txt"), "_out");
    cout << outfilename << '\n';
    vector<double> a;
    // main
    a=importo_txt_v<double>(filename);
    M = media_v(a);
    cout << "media= " << M << endl;
    V = varianza_v<double>(a);
    cout << "dev.std = " << V << endl;
    mediana = CalcolaMediana_v<double>(a);
    cout << "mediana= " << mediana << endl;
    stampa_txt_v<double>(a, outfilename.c_str());
    return 0;
}

