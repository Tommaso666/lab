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
    // inizio1=inizio;
//punto 1
    double  tempo = 0. ,
            tempo_max = 43. ,
            passo = 0.1;
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
    double omega_d = sqrt(omega*omega - pow(alpha/2.0, 2));
    double x_analitico = exp(-alpha*tempo_max/2) * ( cos(omega_d*tempo_max) + (alpha/(2*omega_d))*sin(omega_d*tempo_max) );

    double errore_commesso = fabs(inizio[0] - x_analitico);
    cout<< "l'errore commesso è pari a "<<errore_commesso <<endl;
//punto 3
    double errore_cercato=0.000050;
    double c= errore_commesso/pow(passo,4); 
    passo=pow(errore_cercato/c,0.25); 
    cout << "Il passo necessario per una precisione di 50e-6 metri è " << passo << endl;
//punto 4
        tempo = 0. ,
        tempo_max = 43. ;
        nstep = int(tempo_max/passo+0.5);
        cout<< "farò questo numero di passi per ogni calcolo " <<nstep<<endl;
    randomGen mygen(4);
    double b =0.003;
    vector<double> errori_con_v;
    int controllo2 = 0;
    for(int i = 0;i<10001;i++){
        controllo2++;
        tempo = 0. ;
        inizio[0]=1;  
        inizio[1] = mygen.gauss(-b,b); 
    //modulo evoluzione del sistema 
        double app2=0;
        int controllo=1;
        for (int step=0; step<nstep; step++) {
            inizio = differenziatore.Passo(tempo,inizio,passo,oscilla);
            app2=inizio[0]; 
            tempo = tempo + passo;
        //  controllo il funzionamanto 
            // if((step % 100)==0){
            //     cout<< "sono alla centinaia numeo "<< controllo <<" del loop numero "<<controllo2 <<endl;
            //     controllo++;
            // }
        };
        x_analitico = ampieza_iniziale * sin(omega * tempo_max) * exp(-alpha * tempo_max);
        errori_con_v.push_back(fabs(inizio[0] - x_analitico));
    };
    double errore_statistico = deviazione_std(errori_con_v);
    cout<<"l'errore totale calcolato è "<< errore_statistico <<endl;
    vector<double> mmincert;
    mmincert.push_back(0.003);
    mmincert.push_back(0.005);
    mmincert.push_back(0.008);
    mmincert.push_back(0.012);
    mmincert.push_back(0.015);
    cout<<"sono al ultimo punto "<<endl;
//punto 5
vector<double> errori_in_v;
errori_in_v.push_back(errore_statistico);
    for(int p=1;p<5;p++){
    for(int i = 0;i<10001;i++){
        controllo2++;
            tempo=0.;
            inizio[0]=1;  
            inizio[1] = mygen.gauss(-mmincert[p],mmincert[p]); 
    //modulo evoluzione del sistema 
        double app2=0;
        int controllo=1;
        for (int step=0; step<nstep; step++) {
            inizio = differenziatore.Passo(tempo,inizio,passo,oscilla);
            app2=inizio[0]; 
            tempo = tempo + passo;
        //  controllo il funzionamanto 
            // if((step % 100)==0){
            //     cout<< "sono alla centinaia numeo "<< controllo <<" del loop numero "<<controllo2 <<endl;
            //     controllo++;
            // }
        };
        x_analitico = ampieza_iniziale * sin(omega * tempo_max) * exp(-alpha * tempo_max);
        errori_con_v.push_back(fabs(inizio[0] - x_analitico));
    };
    
        errore_statistico = deviazione_std(errori_con_v);
        errori_in_v.push_back(errore_statistico);
        cout<<"sono al loop "<<p+1<<"/5"<<endl;
    



    };
    for(int i=0;i<errori_in_v.size();i++){
        cout<< "con un errore sulla velocità di "<<mmincert[i]<<" ho un errore statistico di "<<errori_in_v[i]<<endl;
    }
return 0;
};
