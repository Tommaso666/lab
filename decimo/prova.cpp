#include "differenziare.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <omp.h>

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "random.h"
#include "TH1F.h"
#include "TH2F.h"
#include "funzioni.h"
#include "funzionivector.h"
#include"prisma.h"


int main(){
    TCanvas can1;
    TCanvas can2;
    TCanvas can3;
    EsperimentoPrisma p(1);
    int nsimul= 100000;


    TH1F ho1("o1","o1",100,1,0);
    TH1F ho2("o2","o2",100,1,0);
    TH1F ho0("o0","o0",100,1,0);
    TH1F ha("A","A",100,1,0);
    TH1F hb("B","B",100,1,0);
    TH2F AB("AB","AB",100,1,0,100,1,0);
    TH1F hn1("n1","n1",100,1,0);
    TH1F hn2("n2","n2",100,1,0);
    TH2F N("NN","NN",100,1,0,100,1,0);
    



    for(int k=0;k< nsimul;k++){
        p.Esegui();
        p.Analizza();
        ha.Fill(p.getAMisurato());
        hb.Fill(p.getBMisurato());
        ho0.Fill(p.getTh0Misurato());
        ho1.Fill(p.getTh1Misurato());
        ho2.Fill(p.getTh2Misurato());
        hn1.Fill(p.getN1Misurato());
        hn2.Fill(p.getN2Misurato());
        AB.Fill(p.getAMisurato(),p.getBMisurato());
        N.Fill(p.getN1Misurato(),p.getN2Misurato());

    };
    can1.Divide(3,1);
    can1.cd(1);
    hb.Draw();
    can1.cd(2);
    ha.Draw();
    can1.cd(3);
    AB.Draw("colz");
    can1.SaveAs("AB.pdf");

    can2.Divide(3,1);
    can2.cd(1);
    hn1.Draw();
    can2.cd(2);
    hn2.Draw();
    can2.cd(3);
    N.Draw("colz");
    can2.SaveAs("N.pdf");

    can3.Divide(3,1);
    can3.cd(1);
    ho0.Draw();
    can3.cd(2);
    ho1.Draw();
    can3.cd(3);
    ho2.Draw();
    can3.SaveAs("teta.pdf");
    
    return 0;
    
}