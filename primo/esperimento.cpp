#include "funzioni.h"

int main ( int argc, char** argv ) {
//intestazione
if ( argc < 3 ) {
  cout << "Uso del programma : " << argv[0] << " <n_data> <filename> " << endl;
  return -1 ;
}
//variabili
int ndata = atoi(argv[1]);
double* data = new double[ndata];
char * filename = argv[2];
double*vcopy = new double[ndata];
double mediana,M,V = 0;
bool funziona, imp;



//

imp=importo_txt(filename,data,ndata);
for ( int k = 0 ; k < ndata ; k ++ ) vcopy[k] = data[k];

if(imp){cout<< "dati importati"<<endl;}
M=media(data,ndata);
cout <<"media= "<<M <<endl;
V=varianza(data,ndata);
cout <<"dev.std = "<< V << endl;
funziona=riordinaschifo(vcopy,ndata);
if(funziona) cout <<"riordinato " << endl;
mediana=CalcolaMediana(vcopy,ndata);
cout << "mediana= " <<mediana <<endl;
stampa_txt(vcopy,ndata);

delete [] data,vcopy;
return 0;

}
