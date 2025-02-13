


#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <omp.h>
#include<fstream>

#include"random.h"
#include "funzioni.h"
#include "funzionivector.h"
#include "differenziare.h"
int main(){
// TApplication app("app",0,0);


    seno f(1,1);
    vector<int> cases;
    int n_max=10000; 
    double pimez=(M_PI/2);
    IntegratoreMedia coso(1);
    vector<double> devst;
    int m=100;
    for(int k=0;k<6;k++){
        double app =0;
        if((k+1)%2){app=m*2;}else{app=m*5;};
        cases.push_back(app);
        m=app;
    };


  // #pragma omp parallel for
    for ( int k = 0 ; k < cases.size() ; k++ ) {     // ciclo sui casi da studiare

    string nomefiles = "numeri_a_"+to_string(k)+"_punti.txt";
    cout << "Integro con punti = " << cases[k] << endl;
    vector<double> vettoreapp;
    for ( int j = 0 ; j < n_max ; j++ ){ 
      double appoggio=coso.Integra(f,0,pimez,cases[k],0.5);
        vettoreapp.push_back(appoggio);
    };
    stampa_txt_v(vettoreapp,nomefiles.c_str());

  };



 


return 0;

};
