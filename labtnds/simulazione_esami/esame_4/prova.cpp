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
    capacitor a(4);
    vector<double> capacity_simulated;
    for(int i =0;i<10000;i++){
        a.esegui();
        capacity_simulated.push_back(a.getCapacity_simulated());
    };
    double error_compound=deviazione_std(capacity_simulated);
    double error_percent=(error_compound/a.getCapacity());
    cout<<"con un errore pari al " <<error_compound<<"F il valore del errore percentuale è "<<error_percent*100<<"%"<<endl;

    //punto 2 simulo l'inesistenza i alcuni errori 
    capacity_simulated.clear();
    capacity_simulated.shrink_to_fit();
    a.setErrorResistance(0);
    for(int i =0;i<10000;i++){
        a.esegui();
        capacity_simulated.push_back(a.getCapacity_simulated());
    };
    error_compound=deviazione_std(capacity_simulated);
    error_percent=(error_compound/a.getCapacity());
    cout<<"con un errore pari al " <<error_compound<<"F il valore del errore percentuale è "<<error_percent*100<<"%"<<" ponendo nullo il valore del errore sulla resistenza"<<endl;
    //

    capacity_simulated.clear();
    capacity_simulated.shrink_to_fit();
    a.setErrorResistance(3.);
    a.setErrorTime(0);
    for(int i =0;i<10000;i++){
        a.esegui();
        capacity_simulated.push_back(a.getCapacity_simulated());
    };
    error_compound=deviazione_std(capacity_simulated);
    error_percent=(error_compound/a.getCapacity());
    cout<<"con un errore pari al " <<error_compound<<"F il valore del errore percentuale è "<<error_percent*100<<"%"<<" ponendo nullo il valore del errore sul tempo"<<endl;
    //
    capacity_simulated.clear();
    capacity_simulated.shrink_to_fit();
    a.setErrorVoltageMax(0);
    a.setErrorTime(3.);
    for(int i =0;i<10000;i++){
        a.esegui();
        capacity_simulated.push_back(a.getCapacity_simulated());
    };
    error_compound=deviazione_std(capacity_simulated);
    error_percent=(error_compound/a.getCapacity());
    cout<<"con un errore pari al " <<error_compound<<"F il valore del errore percentuale è "<<error_percent*100<<"%"<<" ponendo nullo il valore del errore sul voltaggio massimo"<<endl;
    //
    capacity_simulated.clear();
    capacity_simulated.shrink_to_fit();
    a.setErrorVoltageMax(3.);
    a.setErrorVoltageMin(0);
    for(int i =0;i<10000;i++){
        a.esegui();
        capacity_simulated.push_back(a.getCapacity_simulated());
    };
    error_compound=deviazione_std(capacity_simulated);
    error_percent=(error_compound/a.getCapacity());
    cout<<"con un errore pari al " <<error_compound<<"F il valore del errore percentuale è "<<error_percent*100<<"%"<<" ponendo nullo il valore del errore sul sul voltaggio minimo"<<endl;
    //punto 3
    TGraph campo;
    TCanvas c("campo","campo");
    c.SetGridx();
    c.SetGridy();
    for(int k=0;k<11;k++){
        capacity_simulated.clear();
        capacity_simulated.shrink_to_fit();
        a.setErrorVoltageMax((k/2.)+2);
        a.setErrorVoltageMin((k/2.)+2);
        for(int i =0;i<10000;i++){
            a.esegui();
            capacity_simulated.push_back(a.getCapacity_simulated());
        };
        error_compound=deviazione_std(capacity_simulated);
        error_percent=(error_compound/a.getCapacity());
        campo.SetPoint(k,(k/2.)+2,error_percent*100);

    };
    // Crea una funzione lineare ("pol1" indica un polinomio di primo grado)
    TF1 *f1 = new TF1("f1", "pol1", campo.GetXaxis()->GetXmin(), campo.GetXaxis()->GetXmax());

    // Effettua la fit sul grafico
    campo.Fit(f1, "R");  // "R" indica che si usa l'intervallo specificato
 
    // Estrai i parametri della retta
    double interceptor = f1->GetParameter(0);  // intercetta
    double Dark_side     = f1->GetParameter(1);  // pendenza
 
    std::cout << "Intercetta: " << interceptor << std::endl;
    std::cout << "Pendenza: " << Dark_side << std::endl;
    campo.Draw("AP");
    campo.SetMarkerStyle(20);
    campo.SetMarkerSize(1);
    campo.SetTitle("traiettoria");
    campo.GetXaxis()->SetTitle("v_err[%]"); 
    campo.GetYaxis()->SetTitle("c_err[%]");
    c.SaveAs("correlazione.pdf");
    //punto 4
    double kenobi=0.;
    double anakin=7.;
    kenobi=(anakin-interceptor)/Dark_side;
    cout<<"per ottenere "<<anakin <<" devo avere un errore di v pari ad "<<kenobi <<endl;




return 0;
};
