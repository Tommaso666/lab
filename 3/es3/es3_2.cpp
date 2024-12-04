//librerie standard
#include <iostream>
#include <cstdlib>
#include <vector>
//librerie non standard
#include "TApplication.h"
#include "TH1F.h" 
#include "TGraph.h"
#include  "TCanvas.h"
//mie librerie
#include "algoritmiv.h"


using namespace std;

//main
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
    vector<double> a,b;
    //nome file out
    string outfilename(filename);
    outfilename.insert(outfilename.find_first_of(".txt"), "_out");
    cout << outfilename << '\n';

    string outfilenamehisto(filename);
    outfilenamehisto.insert(outfilenamehisto.find_first_of(".txt"), "_out_histo");
    size_t pos = outfilenamehisto.find(".txt"); 
    outfilenamehisto.replace(pos,4,".pdf");

    cout << outfilenamehisto << '\n';

    // inizio app
   // TApplication app("app",0,0);
    // main
    
    
    
    
    
    a=importo_txt_v<double>(filename);
    M = media_v(a);
    cout << "media= " << M << endl;
    V = varianza_v<double>(a);
    cout << "dev.std = " << V << endl;
    mediana = CalcolaMediana_v<double>(a);
    cout << "mediana= " << mediana << endl;
    stampa_txt_v<double>(a, outfilename.c_str());

    
    //root

    
    //instogramma riempito
    TH1F histo (outfilenamehisto.c_str(),"curva di tendenza", 70 , min(a), max(a) );
    histo.StatOverflows( kTRUE );
    for ( int k = 0 ; k < a.size() ; k++ ) histo.Fill( a[k] );
    //informazioni statistiche
    cout << "Media dei valori caricati = " << histo.GetMean() << endl;

    max(a);
    TCanvas mycanvas (outfilenamehisto.c_str(),"curva di tendenza" );
    histo.Draw();
    histo.GetXaxis()->SetTitle("misurazioni");
    mycanvas.Print(outfilenamehisto.c_str());
   // app.Run();

    
















    return 0;
}



