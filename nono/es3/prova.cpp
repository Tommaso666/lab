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
//  TApplication app("app",0,0);

 seno f(1,1);
 vector<int> cases;
 TCanvas can2("Uniforme","Uniforme") ;
   int n_max=100000; 
  double pimez=(M_PI/2);
  IntegratoreMedia coso(1);
    vector<TH1F> vhistos;
  int m=100;
  for(int k=1;k<=6;k++){
    double app =0;
    if(k%2){app=m*2;}else{app=m*5;};
    cases.push_back(app);
    m=app;
    };



  for ( int k = 0 ; k < cases.size() ; k++ ) {     // ciclo sui casi da studiare

    TH1F h("distribuzione","distribuzione",100,0.8,1.2) ;                   // costruzione istogramma 
 

      for ( int j = 0 ; j < n_max ; j++ ) h.Fill((coso.Integra(f,0,pimez,cases[k],0.5))) ; // riempimento istogramma

        vhistos.push_back(h);                          // conserviamo i puntatori
        
  };

 


  can2.Divide(3,2);

  
  
   for ( int k = 0 ; k < cases.size() ; k++ ) { 
      can2.cd(k+1);
      vhistos[k].GetXaxis()->SetTitle("x [AU]");
      vhistos[k].GetYaxis()->SetTitle("N");
      vhistos[k].Draw();
     
    

  
  }

  can2.SaveAs("numeriprovaormi.pdf");
  // app.Run();


return 0;


}
