// mie librerie
#include "integratori.h"
#include "rand.h"
#include "funzioni.h"
#include "vectorop.h"
#include "prisma.h"
// libvrerie standard
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <omp.h>
// librerie di root
#include "TF1.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1F.h"

using namespace std;
// Funzione per calcolare i coefficienti k1 e k2 con regressione lineare
void regressione_lineare(vector<double> log_h, vector<double> log_err, double &k1, double &k2) {
    int n = log_h.size();
    double sum_x = accumulate(log_h.begin(), log_h.end(), 0.0);
    double sum_y = accumulate(log_err.begin(), log_err.end(), 0.0);
    double sum_xy = 0.0, sum_x2 = 0.0;

    for (int i = 0; i < n; i++) {
        sum_xy += log_h[i] * log_err[i];
        sum_x2 += log_h[i] * log_h[i];
    }

    k2 = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    double q = (sum_y - k2 * sum_x) / n;
    k1 = exp(q);
};


int main() {
    // Parametri
    double max_min =0.1;
    int punti_a_lato=100;
    double D=100*pow(10,-6);
    double lambda=500*pow(10,-9);
    double l=1.;
    F_integrale aborto(0.000001,D,lambda,l);
    double passo=0.1/punti_a_lato;
    // 
    TGraph campo;
    TCanvas c("campo","campo");
    c.SetGridx();
    c.SetGridy();

    for(int i =0;i<punti_a_lato*2;i++){
        double appoggio =(-max_min+(passo*i));
        campo.SetPoint(i,appoggio,aborto.val(appoggio));
    };
    //rooba di root
        campo.Draw("AP");
        campo.SetMarkerStyle(20);
        campo.SetMarkerSize(1);
        campo.SetTitle("traiettoria");
        campo.GetXaxis()->SetTitle("x[m]"); 
        campo.GetYaxis()->SetTitle("A[m]");

        c.SaveAs("traiettoria.pdf");
    //punto 2
    bisezione solutore(1*pow(10,-6));
    double bisezionato=solutore.cercazeri(0.0,0.05,aborto);
    cout <<"il vlaore di ampiezza minima è "<<bisezionato<<" con una lungheza d'onda pari a "<<lambda<<endl;
    // punto 3 
    aborto.anakin.set_lambda(400*pow(10,-9));
    bisezionato=solutore.cercazeri(0.0,0.05,aborto);
    cout <<"il vlaore di ampiezza minima è "<<bisezionato<<" per una lunghezza d'onda "<<400*pow(10,-9) <<endl;
    aborto.anakin.set_lambda(450*pow(10,-9));
    bisezionato=solutore.cercazeri(0.0,0.05,aborto);
    cout <<"il vlaore di ampiezza minima è "<<bisezionato<<" per una lunghezza d'onda "<<450*pow(10,-9) <<endl;



return 0;
};
