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
    const double valore_vero=(3./16.)*(M_E*M_E);
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
            double appogio =0 ;
            appogio=fabs(fabs(Middlepoint.integrale(funzione , a , b , passi_iniziali))-valore_vero);
            errore.SetPoint(punto_numero, passi_iniziali , appogio);
            errori_punto2.push_back(log(appogio));
            passo.push_back(log((b-a)/passi_iniziali));
            punto_numero++;
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
            double appogio =0 ;
            appogio=fabs(fabs(point3.integrale(funzione , a , b , passi_iniziali))-valore_vero);
            errore1.SetPoint(punto_numero, passi_iniziali , appogio);
            punto4.push_back(log(appogio));
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
        unsigned int max = 1000;
        for(int i =0;i<(max+1);i++){
            double appoggio = popolo_di_roma.Integra(funzione,a,b,16,1);
            accumulatoreseriale += appoggio;
            valori_calcolati.push_back(appoggio);
        };
        double valore_integrale =accumulatoreseriale/max;
        double errore_statistico =deviazione_std(valori_calcolati);

    //punto 6
        double errore_appoggio = fabs(fabs(Middlepoint.integrale(funzione , a , b , 16 ))-valore_vero);
        double errore_statistico2=0;
        // vector<double> valori_calcolati1;
        max=0;
        accumulatoreseriale=0;
        double accumulatoreseriale2 = 0;
        do{
            max++;
            // for(int i =0;i<(max+1);i++){
            double appoggio = popolo_di_roma.Integra(funzione,a,b,16,1);
            accumulatoreseriale += appoggio;
            accumulatoreseriale2 += appoggio*appoggio;
            // valori_calcolati1.push_back(appoggio);
            // }
            double valore_integrale = accumulatoreseriale/max;
            // double errore_statistico1 =deviazione_std(valori_calcolati1);
            // errore_statistico2=errore_statistico1;
            errore_statistico2 =  accumulatoreseriale2/max - valore_integrale*valore_integrale;
        }while(errore_statistico2> errore_appoggio );

    // punto 7
        fratta fine_esame;
        b = 2;
        vector <double> punto7;
        double valore_integrale_fratta_middlepoint =fabs(fabs(Middlepoint.integrale(funzione , a , b , 16 ))-valore_vero);
        double valore_integrale_fratta_middleright =fabs(fabs(point3.integrale(funzione , a , b , 16 ))-valore_vero);
        if(valore_integrale_fratta_middlepoint > valore_integrale_fratta_middleright ){
            cout<<"preferisco middleright"<< endl;
            passi_iniziali=2;
            punto_numero=0;
            do{
                double appogio =0 ;
                appogio=fabs(fabs(point3.integrale(funzione , a , b , passi_iniziali))-valore_vero);
                errore.SetPoint(punto_numero, passi_iniziali , appogio);
                punto7.push_back(log(appogio));
                punto_numero++;
                passi_iniziali*=2;
            } while (passi_iniziali<1028);

        }else{
            cout<<"preferisco middleright"<< endl;
            passi_iniziali=2;
            punto_numero=0;
            do{
                double appogio =0 ;
                appogio=fabs(fabs(point3.integrale(funzione , a , b , passi_iniziali))-valore_vero);
                errore.SetPoint(punto_numero, passi_iniziali , appogio);
                punto7.push_back(log(appogio));
                punto_numero++;
                passi_iniziali*=2;
            } while (passi_iniziali<1028);

        }

    
   cout<<"funziono"<<endl;
    // controllo della creazione die tutte le vari classi





}
