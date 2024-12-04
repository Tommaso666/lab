#include "differenziare.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"

std::string convert(double h);

int main()
{
  // vector<double> x70;
  // vector<double> pas;
  TGraph myGraph1;
  const int n_points = 20;
  int p = 0;
  const double tmax = 70.;
  const double omega = 1.;
  const double passo_iniziale = 1e-4;
  const double passo_finale = 1.;
  const double multiplier = log(passo_finale / passo_iniziale) / n_points;
  double h=passo_iniziale;

  for (int m = 0; m < n_points - 1; m++)
  {
    //   TApplication myApp("myApp",0,0);

    RungeKutta myEuler;
    const int nstep = int(tmax / h + 0.5);

    OscillatoreArmonico osc(omega);

    vector<double> x{0., 1.};
    double t = 0.;

    //   TGraph myGraph ;

    // evoluzione del sistema fino a 70 s
    double app2 = 0;
    for (int step = 0; step < nstep; step++)
    {
      // myGraph.SetPoint(step,t,x[0]);
      
      x = myEuler.Passo(t, x, h, osc);
      app2 = x[0];
      t += h;
      // cout<<x[0]<<endl;
    }
    // valutazione errore superfluo
    // pas.Pusch_Back(h);
    // x70.Pusch_Back((app2-sin(70)));

    // grafici  delle cose

    //   TCanvas c ;
    //   c.cd();
    //   string title = "Oscillatore armonico (Eulero h = " + /*var*/convert(h) + ")" ;
    //   myGraph.SetTitle(title.c_str());
    //   myGraph.GetXaxis()->SetTitle("Tempo [s]");
    //   myGraph.GetYaxis()->SetTitle("Posizione x [m]");
    //   myGraph.Draw("AL");
    //   c.SetGridy();

    //   myApp.Run();
    // string out="Oscillatore armonico (Eulero h = " + /*var*/convert(h) + ").png";
    // c.SaveAs(out.c_str());
    cout << app2 << endl;
    myGraph1.SetPoint(p, h, abs(app2 - sin(t)));
    p++;
    h *= exp(multiplier);
  };

  TCanvas c;
  c.cd();
  string title = "errore in funzione del passo";
  myGraph1.SetTitle(title.c_str());
  myGraph1.GetXaxis()->SetTitle("passo");
  myGraph1.GetYaxis()->SetTitle("errore");
  myGraph1.SetMarkerStyle(20);
  myGraph1.SetMarkerSize(0.5);
  myGraph1.Draw("ALP");
  c.SetGridy();
  c.SetGridx();
  c.SetLogx();
  c.SetLogy();

  string out = "errore in funzione del passo.pdf";
  c.SaveAs(out.c_str());

  return 0;
}
std::string convert(double h)
{

  int cifre_significative = -log10(h);
  std::ostringstream streamObj3;
  streamObj3 << std::fixed;
  streamObj3 << std::setprecision(cifre_significative);
  streamObj3 << h;
  std::string strObj3 = streamObj3.str();
  return strObj3;
};
