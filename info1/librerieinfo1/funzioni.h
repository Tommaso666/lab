#ifndef __dati__
#define __dati__ 
#include<algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
double media(double*, int);
double varianza(double*, int);
bool riordinadati(double*,int);
double CalcolaMediana(double*,int );
void stampa_txt(double*,int,char* filename);
bool importo_txt(char*,double*,int);
unsigned int righefiles(const char* filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Errore: Impossibile aprire il file\n";
        return 0;
    }

    unsigned int count = 0;
    string line;
    while (getline(fin, line)) {
        count++;
    }

    fin.close();  // Non obbligatorio, ma buona pratica
    return count;
}

double media(double* x, int z){
    double y,l=0;
    
    for ( int k= 0 ; k < z ; k++ ) {
        l=l+x[k];
    }
    y=l/ z;

     return y;

}
double varianza(double* x, int n){
    double y,a,z =0;
    y=media(x,n);
    for (int i=0;i<n;i++){

    a=a+((x[i]-y)*(x[i]-y));
    };
  
    
    z=sqrt(a/n);

return z;

}

double CalcolaMediana(double*y,int x){
double mediana;
if ( x%2 == 0 ) {    
  //se pari
  mediana = (y[ x/2 -1  ] + y[ x/2 ] ) /2.;    

}else {
  mediana = y[x/2];    
}// se dispari


return mediana;
}
bool riordinadati(double* x,int y){
  int imin = 0;
  double min = 0;
  for (int j=0; j<y-1; j++) {  
   imin = j;
   min=x[imin];
   for (int i=j+1; i<y; i++) {
    if ( x[i]<min ) {                                             
       min  = x[i];
       imin = i;
    }
  }                           
  double c=x[j];
  x[j]=x[imin];
  x[imin]=c;
 
}
 return 1;
}   
void stampa_txt(double*y,int x,char* filename){
  ofstream fout(filename);
    for ( int k = 0 ; k < x ; k ++ ){
    // sia qua che in fin per avere piu dimensioni si può scrivere <<x<<y<<z
    fout<<y[k]<<endl;
    }
fout.close();

}
bool importo_txt(char* filename,double* data,int ndata){
      ifstream fin(filename);

    if ( !fin ) { 
      cout << "Cannot open file " << filename << endl;    
      exit(33);
    } else {
      for ( int k = 0 ; k < ndata ; k++ ) {
        fin >> data[k] ;
        if ( fin.eof() ) { 
          cout << "End of file reached exiting" << endl; 
          exit(33) ;      
        }    
      }        
    }
  return 1  ;

}

//per importare righe di coordinate di tipo char di cui è fornito un inizio 
/*
char* importo(int size){
char* caratteri = new char[size];
for(int k=0;k<size+1;k++){
  double data;
  fin >> data;
  caratteri[k]=data;
  };
};
*/
#endif //__dati__