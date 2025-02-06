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

std::string convert ( double h ) ;

int main () {
vector<double> x70;
vector<double> pas;
TGraph myGraph1 ;
int p=0;



  RungeKutta myEuler;
  double alpha=1./30.;
  double omega =10.;
  
for(int doppio=0;doppio<2;doppio++){
  OscillatoreArmonicoforz osc(10.,alpha,omega);
  double tmax = (1./alpha)*((doppio*10)+1);
  double h =0.0001;   

  vector<double> x {0.,1.} ;
  double t = 0.; 

TGraph myGraph ;
 
  int nstep = int(tmax/h+0.5);

  // evoluzione del sistema fino a 70 s  
    double app2=0;
  for (int step=0; step<nstep; step++) {
  myGraph.SetPoint(step,t,x[0]);
   
    x = myEuler.Passo(t,x,h,osc);
    app2=x[0]; 
    t = t+h;
// cout<<x[0]<<endl;
  };



// grafici  delle cose

  TCanvas c ;
  c.cd();
  string title = "oscillatore con omega_0 =10 ed forzante"+convert(omega) +" ed smorzamento alpha "+convert(alpha)+"dopo un tempo pari ad "+convert(tmax);
  myGraph.SetTitle(title.c_str());
  myGraph.GetXaxis()->SetTitle("Tempo [s]");
  myGraph.GetYaxis()->SetTitle("Posizione x [m]");
  myGraph.Draw("AL");
  c.SetGridy();
    

string out=title+").pdf";
c.SaveAs(out.c_str());
// cout << app2 << endl;



};

//ora implementiamo la curva di risonanza
omega=omega-1;
TGraph myGraph ;
double npunti=1000;
// cout<<"questa parte di programma è parechio pesante consiglio di fare altro per circa 10h"<<endl;
for(int modulatore=0;modulatore<npunti;modulatore++){
double omega1=omega+(modulatore*(2./npunti));
OscillatoreArmonicoforz osc(10.,alpha,omega1);
  double tmax = (1./alpha)*(15);
  double h =0.01;
  int nstep = int(tmax/h+0.5);
  double t = 0.; 
  vector<double> x {0.,1.};

  // evoluzione del sistema fino a 70 s  
    // double app2=0;
    vector<double> appogio;
  for (int step=0; step<nstep; step++) {
  if(step>((2.*nstep)/3.)){appogio.push_back(x[0]);};
   
    x = myEuler.Passo(t,x,h,osc);
    // app2=x[0]; 
    t = t+h;
// cout<<x[0]<<endl;
  };
  double f = 2*(*std::max_element(appogio.begin(), appogio.end()));
  // cout << f << endl;

  myGraph.SetPoint(modulatore,omega1 ,f);
  cout<< "ho finito ora il " << modulatore+1 << " "  <<"/"<<npunti<<" punti e massimo "<<f << endl;

};

// grafici  delle cose

  TCanvas c ;
  c.cd();
  string title = "oscillatore con omega_0 =10 curva di risonanza";
  myGraph.SetTitle(title.c_str());
  myGraph.GetXaxis()->SetTitle("forzante");
  myGraph.GetYaxis()->SetTitle("Posizione x [m]");
  myGraph.Draw("AL");
  c.SetGridy();
    

string out=title+").pdf";
c.SaveAs(out.c_str());

return 0;

}
std::string convert ( double h ) {

  int cifre_significative = -log10(h);
  std::ostringstream streamObj3;
  streamObj3 << std::fixed;
  streamObj3 << std::setprecision(cifre_significative+1);
  streamObj3 << h;

  std::string strObj3 = streamObj3.str();
  return strObj3;

} ;

