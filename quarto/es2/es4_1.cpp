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
#include "TLegend.h"

// mie librerie
#include "funzioni.h"

using namespace std;
void ParseFile( string filename, vector<double> & myx, vector<double> & myy , vector<double> & myerry ) {

  ifstream fin(filename.c_str());

  double x, y, err ;

  if ( !fin ) {
    cout << "Cannot open file " << filename << endl;
    exit(11);
  };

  while ( fin >> x >> y >> err ) {
    myx.push_back(x);
    myy.push_back(y);
    myerry.push_back(err);    
  };

  fin.close();
}
TGraphErrors DoPlot( vector<double> myx, vector<double> myy , vector<double> myerry ) {

  TGraphErrors mygraph;

  for ( int k = 0 ; k < myx.size() ; k++ ) {    
    mygraph.SetPoint(k, myx[k] , myy[k] );
    mygraph.SetPointError(k, 0, myerry[k]);
  };

  return mygraph;

}


int main(){
  vector<double> myx ;
  vector<double> myy ;
  vector<double> myerry;
    // read data from file

    ParseFile("data_eom.dat", myx, myy, myerry ) ;
    // create TGraphErrors

    TGraphErrors mygraph = DoPlot(myx, myy, myerry);

    // fit the TGraphErrors ( linear fit )

    TF1 * myfun = new TF1 ("fitfun","[0]*x+[1]",0, 1000) ;
    mygraph.Fit(myfun);
    double moe = myfun->GetParameter(0);
    double error = sqrt(  pow (1./moe, 4) * pow(myfun->GetParError(0),2)  )  ;

    cout << "Valore di e/m dal fit = " << 1./moe << "+/-" << error << endl;
    cout << "Valore del chi2 del fit = " << myfun->GetChisquare() << endl;
    cout << "          prob del chi2 = " << myfun->GetProb() << endl;
    // customise the plot, cosmetics

    mygraph.Draw("AP");
    mygraph.SetMarkerStyle(20);
    mygraph.SetMarkerSize(1);
    mygraph.SetTitle("Misura e/m");
    mygraph.GetXaxis()->SetTitle("2#DeltaV (V)");
    mygraph.GetYaxis()->SetTitle("(B_{z}R)^{2} (T^{2}m^{2} )");
    TLegend leg (0.15,0.7, 0.3, 0.85) ;
    leg.AddEntry(&mygraph,"data","p");
    leg.AddEntry(myfun,"fit","l");
    leg.Draw("same");

      return 0;

}