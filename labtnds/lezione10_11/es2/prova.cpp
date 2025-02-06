#include "differenziare.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "random.h"
#include "TH1F.h"
#include "funzioni.h"

int main(){


  randomGen myGen(1);

   int n_max=100000; 

  

  TCanvas c("Distribuzioni","Distribuzioni") ;

  c.Divide(3,4);
    

  vector <TH1F*> somma ; 

  TGraph stdev; 

  for(int N=0; N<12; N++){
    
    string title = "N=" + to_string(N); 
    somma.push_back(new TH1F(title.c_str(),title.c_str(),70,4*(N+1),11*(N+1)));
//    somma.push_back(sum);
    //somma[N] = sum;
    for ( int k = 0 ; k < n_max ; k++ ) {
      double s=0; 
      for(int n=0; n<= N; n++){
        s=s+myGen.Unif(5,10);
      }
      somma[N]->Fill(s) ; 
    }

    c.cd(N+1);
    somma[N]->GetXaxis()->SetTitle("x [AU]");
    somma[N]->GetYaxis()->SetTitle("N");
    somma[N]->Draw();

    stdev.AddPoint(N+1,pow(somma[N]->GetStdDev(),2)); 

  }

  usleep(10000); 
  TCanvas c_2; 

  c_2.cd(); 
  c_2.SetGrid(); 
  stdev.GetXaxis()->SetTitle("N");
  stdev.GetYaxis()->SetTitle("#sigma^2");

  stdev.SetTitle("Andamento di #sigma^2");
  stdev.SetMarkerStyle(20);
  stdev.SetLineColor(kBlue-6);
  stdev.Draw("ALP"); 
c_2.SaveAs("prova.pdf");
c.SaveAs("prova_1.pdf");


return 0;


}
