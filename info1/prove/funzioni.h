#ifndef __funzioni__
#define __funzioni__

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

struct carico {
    double peso;
    int nstep;
    string T[15]; // Uso di string invece di char*
};

struct carrello {
    char id;
    int x, y;
    int a;
    carico c;
};

// Funzioni dichiarate
bool importo_txtc(const char*, carrello*, int);
bool importo_txt_carico(const char*, carico*, int);
int quanto(const char* filename);
bool riordinacarichi(carico*, int);
bool riordinacarichi_carrelli(carrello*, int);
void stampa_txt(double*, int, const char*);




//===================================================================================================================================================================================================0
// corpo
//=================================================================================================================================================================================================

// Funzione per leggere il numero di righe nel file
int quanto(const char* filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Errore nell'apertura del file " << filename << endl;
        exit(EXIT_FAILURE);
    }
    int count = 0;
    string line;
    while (getline(fin, line)) {
        count++;
    }
    return count;
}

// Funzione per importare i carrelli dal file
bool importo_txtc(const char* filename, carrello* data, int ndata) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Errore nell'apertura del file " << filename << endl;
        return false;
    }
    for (int i = 0; i < ndata; i++) {
        fin >> data[i].id >> data[i].a;
        data[i].x = 0;
        data[i].y = 0;
        if (fin.eof()) break;
    }
    return true;
}

// Funzione per importare i carichi dal file
bool importo_txt_carico(const char* filename, carico* data, int ndata) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Errore nell'apertura del file " << filename << endl;
        return false;
    }
    for (int i = 0; i < ndata; i++) {
        fin >> data[i].peso >> data[i].nstep;
        for (int j = 0; j < data[i].nstep; j++) {
            fin >> data[i].T[j];
        }
        if (fin.eof()) break;
    }
    return true;
}

// Funzione per riordinare i carichi in base al peso
bool riordinacarichi(carico* x, int y) {
    for (int i = 0; i < y - 1; i++) {
        for (int j = 0; j < y - i - 1; j++) {
            if (x[j].peso > x[j + 1].peso) {
                swap(x[j], x[j + 1]);
            }
        }
    }
    return true;
}

// Funzione per riordinare i carrelli in base all'autonomia
bool riordinacarichi_carrelli(carrello* x, int y) {
    for (int i = 0; i < y - 1; i++) {
        for (int j = 0; j < y - i - 1; j++) {
            if (x[j].a > x[j + 1].a) {
                swap(x[j], x[j + 1]);
            }
        }
    }
    return true;
}

// Funzione per stampare dati su file
void stampa_txt(double* y, int x, const char* filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Errore nell'apertura del file " << filename << endl;
        return;
    }
    for (int i = 0; i < x; i++) {
        fout << y[i] << endl;
    }
    fout.close();
}

#endif //__funzioni__