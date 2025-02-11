// mie librerie
#include "integratori.h"
#include "rand.h"
#include "funzioni.h"
#include "vectorop.h"
// libvrerie standard
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <omp.h>
// librerie di root

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
    double omega0 = 1.0;        // pulsazione
    double t = 0.0;
    double t_final = 20 * M_PI;   // 10 rivoluzioni: 20π
    double h = 0.001;           // passo di integrazione scelto (puoi modificarlo se necessario)
    
    // Condizioni iniziali per x e y
    // Per l'oscillatore in x: [x, v_x] = [1, 0]
    vector<double> sol = {1.0, 0.0 , 0.0 , 1.0};
        
    // Crea un oscillatore armonico con ω0 = 1
    OscillatoreBidimensionale osc(omega0,0.);
    // Crea l'oggetto RungeKutta
    RungeKutta rk;
    // punto 1
    //root
        TGraph campo;
        TCanvas c("campo","campo");
        c.SetGridx();
        c.SetGridy();
        // Integrazione fino a t_final
        unsigned int index=0;
        while (t < t_final) {
            // Eseguiamo un passo RK4 per il sistema in x
            sol = rk.Passo(t, sol, h, osc);
            // Eseguiamo un passo RK4 per il sistema in y
            t += h;
            campo.SetPoint(index,sol[0],sol[2]);
            index++;
        };
        campo.Draw("AP");
        campo.SetMarkerStyle(20);
        campo.SetMarkerSize(1);
        campo.SetTitle("traiettoria");
        campo.GetXaxis()->SetTitle("x[m]"); 
        campo.GetYaxis()->SetTitle("y[m]");

        c.SaveAs("traiettoria_con_alpha=0.pdf");
        
        double errore_x = fabs(sqrt(sol[0]*sol[0]+sol[2]*sol[2]) - 1.0);
        
        cout << "Dopo 10 rivoluzioni:" << endl;
        cout << "x = " << sol[0] << ", y = " << sol[2] << endl;
        cout << "Errore in x: " << errore_x << endl;
// punto 2

        // root
        TGraph campo1;
        TGraph campo2;
        TCanvas c1("campo","campo");
        c1.Divide(1,2);
        // reset variabili
        t=0;
        sol[0]=1.1,sol[1]=0.,sol[2]=0.,sol[3]=1.1;
        index =0;
        osc.setAlpha(2.);
        //evolutore
        while (t < t_final) {
            // Eseguiamo un passo RK4 per il sistema in x
            sol = rk.Passo(t, sol, h, osc);
            t += h;
            campo1.SetPoint(index,sol[0],sol[2]);
            index++;
        };
        // reset variabili
        t=0;
        sol[0]=1.1,sol[1]=0.,sol[2]=0.,sol[3]=1.1;
        index=0;
        osc.setAlpha(-2.);
        //evolutore
        while (t < t_final) {
            // Eseguiamo un passo RK4 per il sistema in x
            sol = rk.Passo(t, sol, h, osc);
            t += h;
            campo2.SetPoint(index,sol[0],sol[2]);
            index++;
        };






        c1.cd(1);
        c1.SetGridx();
        c1.SetGridy();
        campo1.Draw("AP");
        campo1.SetMarkerStyle(20);
        campo1.SetMarkerSize(1);
        campo1.SetTitle("traiettoria alpha = 2");
        campo1.GetXaxis()->SetTitle("x[m]"); 
        campo1.GetYaxis()->SetTitle("y[m]");
        campo1.SetMarkerStyle(20);  // Imposta lo stile dei marker
        campo1.SetMarkerSize(0.1);
        c1.cd(2);
        c1.SetGridx();
        c1.SetGridy();
        campo2.Draw("AP");
        campo2.SetMarkerStyle(20);
        campo2.SetMarkerSize(1);
        campo2.SetTitle("traiettoria alpha = -2");
        campo2.GetXaxis()->SetTitle("x[m]"); 
        campo2.GetYaxis()->SetTitle("y[m]");
        campo2.SetMarkerStyle(20);  // Imposta lo stile dei marker
        campo2.SetMarkerSize(0.1);

        c1.SaveAs("traiettoria_con_alpha=+-2.pdf");
// punto 3
        TGraph campo3;
        TGraph campo4;
        TCanvas c2("campo","campo");
        osc.setaddizione(1.);
        // reset variabili
        t=0;
        sol[0]=1.1,sol[1]=0.,sol[2]=0.,sol[3]=1.1;
        index =0;
        osc.setAlpha(2.);
        //evolutore
        while (t < t_final) {
            // Eseguiamo un passo RK4 per il sistema in x
            sol = rk.Passo(t, sol, h, osc);
            t += h;
            campo3.SetPoint(index,sol[0],sol[2]);
            double app=sqrt((sol[0]*sol[0])+(sol[2]*sol[2]));
            campo4.SetPoint(index,t,app);
            index++;
        };
        c2.Divide(1,2);
        c2.cd(1);
        c2.SetGridx();
        c2.SetGridy();
        campo3.Draw("AP");
        campo3.SetMarkerStyle(20);
        campo3.SetMarkerSize(1);
        campo3.SetTitle("traiettoria");
        campo3.GetXaxis()->SetTitle("x[m]"); 
        campo3.GetYaxis()->SetTitle("y[m]");
        campo3.SetMarkerStyle(20);  // Imposta lo stile dei marker
        campo3.SetMarkerSize(0.1);

        c2.cd(2);
        c2.SetGridx();
        c2.SetGridy();
        campo4.Draw("AP");
        campo4.SetMarkerStyle(20);
        campo4.SetMarkerSize(1);
        campo4.SetTitle("raggio(tempo)");
        campo4.GetXaxis()->SetTitle("tempo[s]"); 
        campo4.GetYaxis()->SetTitle("raggio[m]");
        campo4.SetMarkerStyle(20);  // Imposta lo stile dei marker
        campo4.SetMarkerSize(0.1);

        c2.SaveAs("traiettoria_con_alpha=2 e addendo 1.pdf");
    

return 0;
};
