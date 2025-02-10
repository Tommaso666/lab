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
    double valore_vero=(3./16.)*(M_E*M_E);
    Xcubo funzione;
    vector<double> errori_punto2;
    vector<double> passo;
    vector<double> punto4;
    double a= 0.;
    double b= sqrt(M_E);

    // punto uno

        unsigned int passi_iniziali = 2;
        middlepoint Middlepoint ;
    
        // root mio caro
        TCanvas c("errore trend", "errore trend");
        c.cd();
        c.SetGridx();
        c.SetGridy();
        c.SetLogy();
        c.SetLogx();
        TGraph errore;
        int punto_numero=0;
        do{
            double passo1 =(b-a)/passi_iniziali;
            double appogio =0 ;
            double appoggio = Middlepoint.integrale(funzione , a , b , passi_iniziali);
            appogio=fabs(fabs(appoggio)-valore_vero);
            errore.SetPoint(punto_numero, passo1 , appogio);
            errori_punto2.push_back(log(appogio));
            passo.push_back(log(passo1));
            punto_numero++;
            
            cout<<"il valore del integrale è "<< appoggio <<" con un numero di passi paro a "<<passi_iniziali <<" con un passo di integegrazione di "<< passo1 <<" ed un errore di "<<appogio <<endl;
            passi_iniziali*=2;
        } while (passi_iniziali<1028);
        // rendiamo bello il grafico
        errore.SetMarkerStyle(20);  // Imposta lo stile dei marker
        // errore.GetMarkerSize(0.3);
        errore.SetTitle("Andamento dell'Errore;numero di passi; Errore");
        errore.Draw("AP");          // Disegna con punti e assi
        c.SaveAs("errore.pdf");

    //punto 2
        double k1 =0 , k2 = 0;
        regressione_lineare(passo,errori_punto2,k1,k2);
        cout << "\nStima dei coefficienti:" << endl;
        cout << "k1 = " << k1 << endl;
        cout << "k2 = " << k2 << endl;
        

    // punto 3
        middleright point3 ;
        passi_iniziali=2;
        // root mio caro
        TCanvas c1("errore trend", "errore trend");
        c1.cd();
        c1.SetGridx();
        c1.SetGridy();
        c1.SetLogy();
        c1.SetLogx();
        TGraph errore1;
        punto_numero=0;
        do{ 
            double passo1 =(b-a)/passi_iniziali;
            double appogio =0 ;
            double appoggio = point3.integrale(funzione , a , b , passi_iniziali);
            appogio=fabs(fabs(appoggio)-valore_vero);
            errore1.SetPoint(punto_numero, passo1 , appogio);
            punto4.push_back(log(appogio));
            cout<<"il valore del integrale con middleright è "<< appoggio <<" con un numero di passi paro a "<<passi_iniziali <<" con un passo di integegrazione di "<< passo1 <<" ed un errore di "<<appogio <<endl;
            punto_numero++;
            passi_iniziali*=2;
        } while (passi_iniziali<1028);
        // rendiamo bello il grafico
        errore1.SetMarkerStyle(20);  // Imposta lo stile dei marker
        // errore1.GetMarkerSize(0.3);
        errore1.SetTitle("Andamento dell'Errore ; numero di passi ; Errore");
        errore1.Draw("AP");          // Disegna con punti e assi
        c1.SaveAs("errore_middleright.pdf");
    
    // punto 4
        double k1_1 =0 , k2_1 = 0;
        regressione_lineare(passo,punto4,k1_1,k2_1);

        cout << "\nStima dei coefficienti:" << endl;
        cout << "k1 = " << k1_1 << endl;
        cout << "k2 = " << k2_1 << endl;
        
    // punto 5
        vector<double> valori_calcolati;
        IntegratoreMedia popolo_di_roma(4);
        double accumulatoreseriale = 0;
        unsigned int max = 1000,
                    n_punti=16;
        for(int i =0;i<(max+1);i++){
            double appoggio = popolo_di_roma.Integra(funzione,a,b,n_punti,1);
            accumulatoreseriale += appoggio;
            valori_calcolati.push_back(appoggio);
        };
        double valore_integrale =accumulatoreseriale/max;
        double errore_statistico =deviazione_std(valori_calcolati);
        cout <<"il valore dell'integrale è "<<valore_integrale<< " con un errore di "<<errore_statistico <<endl;

    //punto 6
        double k=errore_statistico*sqrt(n_punti);
        double errore_appoggio = fabs(fabs(Middlepoint.integrale(funzione , a , b , 16 ))-valore_vero);
        cout<<"punto ad un errore di "<<errore_appoggio<<endl;
        max= (k*k)/(errore_appoggio*errore_appoggio);
        cout<<"ho avuto bisogno di "<<max<<" passaggi"<<endl;
    // punto 7
        
        fratta fine_esame;
        vector<double> passi_7;
        b = 2.;
        vector <double> punto7;
        //non avendo un valore vero ne creo uno con un  altro metodo 
        valore_vero = M_PI/2;
            cout<<"preferisco middlepoint siccome midleright darebbe inf"<< endl;
            passi_iniziali=2;
            punto_numero=0;
            do{
                double passo2 =(b-a)/passi_iniziali;
                double appogio =0 ;
                double appoggio=fabs(Middlepoint.integrale(fine_esame , a , b , passi_iniziali));
                appogio=fabs(appoggio-valore_vero);
                errore.SetPoint(punto_numero, passi_iniziali , appogio);
                punto7.push_back(log(appogio));
                cout<<"il valore del integrale è "<< appoggio <<" con un numero di passi paro a "<<passi_iniziali <<" con un passo di integegrazione di "<< passo2 <<" ed un errore di "<<appogio <<endl;
            
                punto_numero++;
                passi_iniziali*=2;
                passi_7.push_back(log(passo2));
            } while (passi_iniziali<1028);

        
        double k1_2 =0 , k2_2 = 0;
        regressione_lineare(passi_7,punto7,k1_2,k2_2);

        cout << "\nStima dei coefficienti:" << endl;
        cout << "k1 = " << k1_2 << endl;
        cout << "k2 = " << k2_2 << endl;
    
    //cout<<"funziono"<<endl;
    // controllo della creazione die tutte le vari classi





}
