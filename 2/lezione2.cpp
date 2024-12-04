
#include"vettore.h"

int main ( int argc, char** argv ) {
//intestazione
if ( argc < 3 ) {
  cout << "Uso del programma : " << argv[0] << " <n_data> <filename> " << endl;
  return -1 ;
}
//variabili
int ndata = atoi(argv[1]);
Vettore b(ndata); 
Vettore a(ndata);

char * filename = argv[2];
double mediana,M,V = 0;

//
importo_txt_v(filename ,b);
duplicavet(b,a);



M=media_v(b);
cout <<"media= "<<M <<endl;
V=varianza_v(b);
cout <<"dev.std = "<< V << endl;
riordinadati_v(a);
mediana=CalcolaMediana_v(a);
cout << "mediana= " <<mediana <<endl;
stampa_txt_v(a);



return 0;

}
