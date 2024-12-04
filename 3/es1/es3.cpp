

#include "vettore.h"

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
    Vettore<double> b(ndata);
    Vettore<double> a(ndata);



    string outfilename(filename);
    outfilename.insert(outfilename.find_first_of(".txt"), "_out");
    cout << outfilename << '\n';

    // main
    importo_txt_v<double>(filename, b);
    duplicavet<double>(b, a);

    M = media_v(b);
    cout << "media= " << M << endl;
    V = varianza_v<double>(b);
    cout << "dev.std = " << V << endl;
    riordinadati_v<double>(a);
    mediana = CalcolaMediana_v<double>(a);
    cout << "mediana= " << mediana << endl;
    stampa_txt_v<double>(a, outfilename.c_str());
   
    
    return 0;
}
