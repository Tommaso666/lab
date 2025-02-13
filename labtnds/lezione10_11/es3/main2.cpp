#include "differenziare.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <omp.h>
#include<fstream>

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "random.h"
#include "TH1F.h"
#include "funzioni.h"
#include "funzionivector.h"
#include "vectorop.h"

std::string convert ( double h ) ;

int main(){
// TApplication app("app",0,0);


    TGraph stdev; 
    vector<int> cases;
    TCanvas can2("Uniforme","Uniforme") ;
    int n_max=10000; 
    vector<TH1F*> vhistos;
    vector<double> devst;
    int m=100;
    for(int k=0;k<6;k++){
    double app =0;
    if((k+1)%2){app=m*2;}else{app=m*5;};
    cases.push_back(app);
    m=app;
    };



  for ( int k = 0 ; k < cases.size() ; k++ ) {     // ciclo sui casi da studiare

    string nomehisto = "h"+to_string(k);
    string nomefiles = "numeri_a_"+to_string(k)+"_punti.txt";
    TH1F* h = new TH1F(nomehisto.c_str(),nomehisto.c_str(),100,0.8,1.2) ;                   // costruzione istogramma 
    vector<double> vettoreapp;
    vector<double> coso;
    double data =0;
    ifstream fin(nomefiles.c_str());
    
        while(fin>>data){
           
            coso.push_back(data);
            if (fin.eof());
        };
    for ( int j = 0 ; j < n_max ; j++ ){ 
      double appoggio=coso[j];
        
      h->Fill((appoggio)) ; // riempimento istogramma

      vettoreapp.push_back(appoggio);
    };
  
    devst.push_back(varianza_v<double>(vettoreapp));    //calcolo dev st e metti in un vector
  
    vhistos.push_back(h);                          // conserviamo i puntatori
    cout<< "finito il giro n=" <<(k+1) <<" su 6"<<endl;
  };



  can2.Divide(3,2);

  
  
   for ( int k = 0 ; k < cases.size() ; k++ ) { 
      can2.cd(k+1);
      string filename = "x [AU] deviazione st calcolata =" +convert(devst[k]) ;
      vhistos[k]->GetXaxis()->SetTitle(filename.c_str());
      vhistos[k]->GetYaxis()->SetTitle("N");
      vhistos[k]->Draw();
     
    

  
  };
  // per minimizare l'errore 

  can2.SaveAs("numeriprovaormi.pdf");
  for(int i=0;i< cases.size();i++)
  stdev.AddPoint(devst[i],cases[i]); 
  TCanvas c_2; 

  c_2.cd(); 
  c_2.SetGrid(); 
  stdev.GetXaxis()->SetTitle("N");
  stdev.GetYaxis()->SetTitle("#sigma");

  stdev.SetTitle("Andamento di #sigma");
  stdev.SetMarkerStyle(20);
  stdev.SetLineColor(kBlue-6);
  stdev.Draw("ALP"); 
  c_2.SaveAs("prova.pdf");
  // app.Run();


return 0;


};
std::string convert ( double h ) {

  int cifre_significative = -log10(h);
  std::ostringstream streamObj3;
  streamObj3 << std::fixed;
  streamObj3 << std::setprecision(cifre_significative+3);
  streamObj3 << h;
  std::string strObj3 = streamObj3.str();
  return strObj3;

} ;
