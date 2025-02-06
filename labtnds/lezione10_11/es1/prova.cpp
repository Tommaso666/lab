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

  int nmax = 10000000;

  parabola para(-1,0,4);

  TH1F unif("Uniforme","Uniforme",100,4,12) ;
  TH1F unif2("exp","exp",100,0,5) ;
  TH1F unif3("gauss","gauss",100,-5,5) ;
  TH1F unif4("parabola","parabola",100,0,5) ;
  for ( int k = 0 ; k < nmax ; k++ ) {

    unif.Fill( myGen.Unif(5,10)  ) ;  

    unif2.Fill(myGen.esponenziale(1));

    unif3.Fill(myGen.gauss(0,1));

    unif4.Fill(myGen.aceptreg(0,10,20,para));
  };

  TCanvas can2("Uniforme","Uniforme") ;
  can2.Divide(2,2);
  can2.cd(1);
  unif.GetXaxis()->SetTitle("x [AU]");
  unif.GetYaxis()->SetTitle("N");
  unif.Draw();
  can2.cd(2);
  unif2.GetXaxis()->SetTitle("x [AU]");
  unif2.GetYaxis()->SetTitle("N");
  unif2.Draw();
  can2.cd(3);
  unif3.GetXaxis()->SetTitle("x [AU]");
  unif3.GetYaxis()->SetTitle("N");
  unif3.Draw();
  can2.SaveAs("numeri uniformi.pdf");
  can2.cd(4);
  unif4.GetXaxis()->SetTitle("x [AU]");
  unif4.GetYaxis()->SetTitle("N");
  unif4.Draw();
  can2.SaveAs("numeri uniformi.pdf");



return 0;


}
