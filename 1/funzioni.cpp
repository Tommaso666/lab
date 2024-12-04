#include "funzioni.h"

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
bool riordinaschifo(double* x,int y){
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
void stampa_txt(double*y,int x){
  ofstream fout("files_uscita.txt");
    for ( int k = 0 ; k < x ; k ++ ){
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