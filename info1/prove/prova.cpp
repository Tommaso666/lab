#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include "funzioni.h"
using namespace std;


int main() {
    ofstream fout("datiout.dat");
    int ndata = 25;
    int ndata1 = 25;
    const string file = "carrelli.dat";
    const string file2 = "carichi.dat";

    ndata=quanto(file.c_str());
    ndata1=quanto(file2.c_str());
    // Punto 1a: Importo carrelli
    carrello* c = new carrello[ndata];
    if (!importo_txtc(file.c_str(), c, ndata)) {
        cout << "Errore nel caricamento dei carrelli." << endl;
        return 1;
    }
    fout << "Ho caricato un totale di carrelli pari a " << ndata << endl;
    cout << "Ho caricato un totale di carrelli pari a " << ndata << endl;

    // Punto 1b: Stampa informazioni sui carrelli
    for (int i = 0; i < 3; i++) {
        cout << "Il carrello " << i + 1 << " ha posizione iniziale (" << c[i].x << ";"
             << c[i].y << ") ed autonomia di " << c[i].a << endl;
        fout << "Il carrello " << i + 1 << " ha posizione iniziale (" << c[i].x << ";"
             << c[i].y << ") ed autonomia di " << c[i].a << endl;
    }
 cout<<endl<<endl;
    // Punto 2a: Importo carichi
    carico* car = new carico[ndata1];
    if (!importo_txt_carico(file2.c_str(), car, ndata1)) {
        cout << "Errore nel caricamento dei carichi." << endl;
        return 1;
    }
    fout << "Ho caricato un totale di carichi pari a " << ndata1 << endl;
    cout << "Ho caricato un totale di carichi pari a " << ndata1 << endl;

    // Punto 2b: Peso totale dei carichi
    double peso_totale = 0.0;
    for (int i = 0; i < ndata; i++) {
        peso_totale += car[i].peso;
    }
    cout << "In totale devono spostare " << peso_totale << " kg" << endl;
    fout << "In totale devono spostare " << peso_totale << " kg" << endl;
 cout<<endl<<endl;
  fout<<endl<<endl;
    // Punto 2c: Riordino carichi
    riordinacarichi(car, ndata);

    for (int i = 0; i < 3; i++) {
        cout << "Il carico " << i + 1 << " ha massa " << car[i].peso
             << " , distanza " << car[i].nstep << " e percorso: ";
        fout << "Il carico " << i + 1 << " ha massa " << car[i].peso
             << " , distanza " << car[i].nstep << " e percorso: ";
        for (const auto& t : car[i].T) {
            cout << t << " ";
            fout << t << " ";
        }
                cout << endl;
        fout << endl;
    }
 cout<<endl<<endl;
 fout<<endl<<endl;

    // Punto 3: Assegno i carichi ai carrelli
    for (int i = 0; i < ndata; i++) {
        c[i].c = car[i];
    }

    for (int i = 0; i < 3; i++) {
        cout << "Il carrello " << i + 1 << " ha posizione iniziale (" << c[i].x << ";"
             << c[i].y << ") ed autonomia di " << c[i].a
             << " il carico ha massa " << c[i].c.peso
             << " , distanza " << c[i].c.nstep << " e percorso: ";
        fout << "Il carrello " << i + 1 << " ha posizione iniziale (" << c[i].x << ";"
             << c[i].y << ") ed autonomia di " << c[i].a
             << " il carico ha massa " << c[i].c.peso
             << " , distanza " << c[i].c.nstep << " e percorso: ";
        for (const auto& t : c[i].c.T) {
            cout << t << " ";
            fout << t << " ";
        }
        cout << endl;
        fout << endl;
    }
 cout<<endl<<endl;
  fout<<endl<<endl;
    // Punto 4: Filtra carrelli buoni e cattivi
    int ngood = 0;
    for (int i = 0; i < ndata; i++) {
        if (c[i].a >= c[i].c.nstep) {
            ngood++;
        }
    }

    carrello* cgood = new carrello[ngood];
    carrello* cbad = new carrello[ndata - ngood];

    int good_index = 0, bad_index = 0;
    for (int i = 0; i < ndata; i++) {
        if (c[i].a >= c[i].c.nstep) {
            cgood[good_index++] = c[i];
        } else {
            cbad[bad_index++] = c[i];
        }
    }
 cout<<endl<<endl;
  fout<<endl<<endl;
    // Stampo i carrelli buoni
    for (int i = 0; i < ngood; i++) {
        cout << "Il carrello " << i + 1 << " ha posizione iniziale (" << cgood[i].x << ";"
             << cgood[i].y << ") ed autonomia di " << cgood[i].a
             << " il carico ha massa " << cgood[i].c.peso
             << " , distanza " << cgood[i].c.nstep << " e percorso: ";
        fout << "Il carrello " << i + 1 << " ha posizione iniziale (" << cgood[i].x << ";"
             << cgood[i].y << ") ed autonomia di " << cgood[i].a
             << " il carico ha massa " << cgood[i].c.peso
             << " , distanza " << cgood[i].c.nstep << " e percorso: ";
        for (const auto& t : cgood[i].c.T) {
            cout << t << " ";
            fout << t << " ";
        }
        cout << endl;
        fout << endl;
    }
    cout<<endl<<endl;
     fout<<endl<<endl;
    // Stampo i carrelli cattivi
    for (int i = 0; i < ndata - ngood; i++) {
        cout << "Il carrello " << i + 1 << " ha posizione iniziale (" << cbad[i].x << ";"
             << cbad[i].y << ") ed autonomia di " << cbad[i].a
             << " il carico ha massa " << cbad[i].c.peso
             << " , distanza " << cbad[i].c.nstep << " e percorso: ";
        fout << "Il carrello " << i + 1 << " ha posizione iniziale (" << cbad[i].x << ";"
             << cbad[i].y << ") ed autonomia di " << cbad[i].a
             << " il carico ha massa " << cbad[i].c.peso
             << " , distanza " << cbad[i].c.nstep << " e percorso: ";
        for (const auto& t : cbad[i].c.T) {
            cout << t << " ";
            fout << t << " ";
        }
        cout << endl;
        fout << endl;
    }

    // Libero la memoria allocata dinamicamente
    delete[] c;
    delete[] car;
    delete[] cgood;
    delete[] cbad;

    fout.close();
    return 0;
}

