#include "differenziare.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"



int main () {
TGraph myGraph1;
double g=9.8;   //espresso in metri/secondi^2
double l=1;    //espresso in metri
double w=sqrt(g/l);
double T_Oa = 2*M_PI*w;
double h=0.001;
pendol0 oss(w);
RungeKutta myRK4;
for(int i=0;i<30;i++){
double A=0.1*(i+1);
double v=0.;
double t = 0.; 
vector<double> x {-A , v} ;
while ( x[1]>=0.) {
    v = x[1];    
    x = myRK4.Passo(t,x,h,oss);
    t = t+h;
    // std::cout << A << " " << x[0] << " " << t << std::endl;
}
t = t-v*h/(x[1]-v);
double period = 2*t ;



    myGraph1.SetPoint(i,A,period);

}
  TCanvas c;
  c.cd();
  string title = "pendolo";
  myGraph1.SetTitle(title.c_str());
  myGraph1.GetXaxis()->SetTitle("periodo");
  myGraph1.GetYaxis()->SetTitle("angolo iniziale");
  myGraph1.SetMarkerStyle(20);
  myGraph1.SetMarkerSize(0.5);
  myGraph1.Draw("ALP");
  c.SetGridy();
  c.SetGridx();


  string out = "pendolo.pdf";
  c.SaveAs(out.c_str());

return 0;

}

