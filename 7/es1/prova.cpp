#include "funzioni.h"
#include <iostream>
#include <cmath>
#include<iomanip>
#include "TApplication.h"
#include "TH1F.h" 
#include "TGraph.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include <TF1.h>
#include "TLegend.h"


using namespace std;

int main() {
    seno f(1,1);  // Dichiarazione dell'oggetto tangente
    middlepoint a;
    // valore del integrale
  
    double pimez = M_PI / 2;
    cout<<"il valore del integrale è : "<< a.integrale(f,0,pimez,2000)<<endl;

  // ............
    TCanvas c("errore trend", "errore trend");
    c.cd();
    c.SetGridx();
    c.SetGridy();
    c.SetLogy();
    c.SetLogx();

  TGraph g_errore;
  int nstep=4;
  double Iv = 1. ;
  double I = 0, err = 0 , h = 0 ;

  for ( unsigned int k = 0 ; k < 10; k++ ) {
    I=a.integrale(f,0,pimez,nstep);
    h=(pimez-0)/nstep;

    err = fabs(I-Iv);
    cout << " Passi= " << setw(20) << nstep << " Errore= " << setw(20)<< err << endl;
    g_errore.SetPoint(k, h, err );
    nstep *= 2;
  }
  g_errore.SetMarkerStyle(20);  // Imposta lo stile dei marker
g_errore.SetTitle("Andamento dell'Errore; Passo h; Errore");
g_errore.Draw("AP");          // Disegna con punti e assi

    c.SaveAs("errore.pdf");
  // ............


    return 0;
}

