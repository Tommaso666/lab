#include "campo.h"

#include<vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "TApplication.h"
#include "TH1F.h" 
#include "TGraph.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include <TF1.h>
#include "TLegend.h"



using namespace std;

int main() {
// inizio app
TApplication app("app",0,0);
  
 /* string filename ="dati.txt";
  vector<double> x;
  vector<double> y;
  vector<double> z;*/
  vector <double> Ev;
  vector <double> R;

  // ParseFile(filename.c_str(),x,y,z);
  const double e =1.60217653E-19 ;
  const double me=9.1093826E-31;
  const double mp=1.6726219E-27;  
  const double d =1.E-10; 
PuntoMateriale elettrone(me, -e,0.,0.,d/2.);
PuntoMateriale protone(mp, e,0.,0.,-d/2.);


for(int i=0;i<1200;i++){

  Posizione p(0,0,(i+50)*d);
  cout <<p.modulovet(p) <<"raggio"<< endl;

 

  CampoVettoriale E = elettrone.CampoElettrico( p ) + protone.CampoElettrico( p ) ;

  cout<<"campotot "<<E.Modulo()<<endl;
  
  Ev.push_back(E.Modulo());
  R.push_back(p.modulovet(p));

};
TGraph campo;
TCanvas c("campo","campo");
  c.SetGridx();
  c.SetGridy();
 

for(int i=0;i<Ev.size();i++){
  campo.SetPoint(i,R[i],Ev[i]);
}
campo.Draw("AP");
campo.SetMarkerStyle(20);
campo.SetMarkerSize(1);
campo.SetTitle("campo eletrico dipolo");
campo.GetXaxis()->SetTitle("r[m]");
campo.GetYaxis()->SetTitle("|E| [c]");

c.SaveAs("campo2.pdf");
double esponente=0;
vector<double> esponentev ;
cout<<"ora cerchiamo la potenza che eleva il campo che é =";
for(int i =1;i<(Ev.size());i++){

  double app1 =log((Ev[0]/Ev[i]));
  double app2 =log((R[0]/R[i]));
  esponentev.push_back(app1/app2);
};

esponente=media_v(esponentev);
cout<< esponente <<endl;
app.Run();
  return 0;  
}
