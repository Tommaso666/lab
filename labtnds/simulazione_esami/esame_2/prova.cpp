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

int main(){
    
    // variabili principali 
    RungeKutta differenziatore;
    double  omega =1.15,
            alpha=0.01 ,
            forzante=0.;
    OscillatoreArmonicoforz oscilla (omega,alpha,forzante );
    vector<double> inizio;
    double ampieza_iniziale=1.,
           velocità_iniziale =0.;
    inizio.push_back(ampieza_iniziale);   //condizione iniziale per la posizione
    inizio.push_back(velocità_iniziale);   //condizione iniziale per la velocità   
    inizio1=inizio;
//punto 1
    double  tempo = 0. ,
            tempo_max = 43. ,
            passo = 0.01;
    unsigned int nstep = int(tempo_max/passo+0.5);
    //modulo evoluzione del sistema 
    double app2=0;
    for (int step=0; step<nstep; step++) {
        inizio = differenziatore.Passo(tempo,inizio,passo,oscilla);
        app2=inizio[0]; 
        tempo = tempo + passo;
    };
    cout << "la posizione del nostro oscillatore armonico è :" << inizio[0] << " e la sua velocità nel punto è pari a "<< inizio[1] <<endl;
//punto 2
    double errore_commesso = inizio[0] - ampieza_iniziale*sin(omega*tempo_max)*exp((tempo_max/tempo_max));
    cout<< "l'errore commesso è pari a "<<errore_commesso <<endl;
//punto 3
    double errore_cercato=0.000050;
    double c= errore_commesso/pow(2*passo,4); 
    passo=pow(50e-6/c,0.25); 
    cout << "Il passo necessario per una precisione di 50e-6 metri è " << passo << endl;
//punto 4
    double  tempo = 0. ,
            tempo_max = 43. ,
            passo = 0.01;
    unsigned int nstep = int(tempo_max/passo+0.5);
    randomGen mygen(4);
    double b =0.003;
    vector<double> errori_con_v;
    for(int i = 0;i<10001;i++){
        inizio[0]=1;  
        inizio[1] = mygen.gauss(-b,b); 
    //modulo evoluzione del sistema 
        double app2=0;
        for (int step=0; step<nstep; step++) {
            inizio = differenziatore.Passo(tempo,inizio,passo,oscilla);
            app2=inizio[0]; 
            tempo = tempo + passo;
        };
        errori_con_v.push_back(abs(inizio[0] - ampieza_iniziale*sin(omega*tempo_max)*exp((tempo_max/tempo_max))));
    };
    double errore_statistico = deviazione_std(errori_con_v);
    cout<<"l'errore totale calcolato è "<< errore_statistico <<endl;
    vector<double> mmincert;
    mmincert.push_back(0.003);
    mmincert.push_back(0.005);
    mmincert.push_back(0.008);
    mmincert.push_back(0.012);
    mmincert.push_back(0.015);
//punto 5
vector<double> errori_in_v;
errori_in_v.push_back(errore_statistico);
    for(int p=0;p<5;p++){
        for(int i = 0;i<10001;i++){
            inizio[0]=1;  
            inizio[1] = mygen.gauss(-mmincert[p+1],mmincert[p+1]); 
            vector<double> errori_con_v1;
        //modulo evoluzione del sistema 
            double app2=0;
            for (int step=0; step<nstep; step++) {
                inizio = differenziatore.Passo(tempo,inizio,passo,oscilla);
                app2=inizio[0]; 
                tempo = tempo + passo;
            };
        errori_con_v1.push_back(abs(inizio[0] - ampieza_iniziale*sin(omega*tempo_max)*exp((tempo_max/tempo_max))));
        };
    errori_in_v.push_back(deviazione_std(errori_con_v));
    };
    



}
