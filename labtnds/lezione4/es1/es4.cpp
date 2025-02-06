// librerie standard
#include <iostream>
#include <cstdlib>
#include <vector>
#include<algorithm>
// librerie ROOT
#include "TApplication.h"
#include "TH1F.h" 
#include "TGraph.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include <TF1.h>

// mie librerie
#include "funzioni.h"

using namespace std;

// main
int main() { 
    int numero = 0;
    int quanto = 0;
    double media = 0;
    double errore = 0;
    const string txt = ".txt";
    
    int index = 0;
    cout << "inserisci da dove partire: ";
    cin >> numero;
    cout << endl;
    cout << "inserisci quanti elementi: ";
    cin >> quanto;
    cout << endl;

    TGraphErrors trend;

    // Ciclo per elaborare i file
    for (int i = 0; i < quanto; i++) {
        int file = numero + i;
        string filename = "TemperatureMilano/"+to_string(file) + txt;
        cout << filename <<endl;

        vector<double> a;
        
        // Assicurati che importo_txt_v restituisca un vector<double>
        a = importo_txt_v<double>(filename.c_str());

        // Calcola media e varianza
        media = media_v(a);
        errore = varianza_vm<double>(a);
        cout<<"errore"<<errore<<endl;

        // Aggiungi i punti al grafico
        trend.SetPoint(index,numero+i , media);
        trend.SetPointError(index, 0, errore);  // Corretto con virgole
        index++;
    }

    // Crea il canvas
    TCanvas c("temperatura trend", "temperatura trend");
    c.cd();
    c.SetGridx();
    c.SetGridy();
    
    // Impostazioni del grafico
    trend.SetMarkerSize(1.0);
    trend.SetMarkerStyle(20);
    trend.SetFillColor(5);

    trend.SetTitle("trend di temperature");
    trend.GetXaxis()->SetTitle("anno");
    trend.GetYaxis()->SetTitle("#Delta(#circ C)");

    trend.Draw("AP");


    // Salva il grafico in un file PDF
    c.SaveAs("trend.pdf");
   

    return 0;
}