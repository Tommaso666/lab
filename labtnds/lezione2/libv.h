#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "vettore.h"
using namespace std;

void importo_txt_v(char*,Vettore &);
void duplicavet(Vettore & , Vettore & );
double media_v(const Vettore &);
double varianza_v(const Vettore &);
void riordinadati_v(Vettore &);
double CalcolaMediana_v(const Vettore &);
void stampa_txt_v(const Vettore &, ofstreaam & );