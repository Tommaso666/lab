#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

bool riordinaschifo(double*,int);
double CalcolaMediana(double*,int);
void stampa_txt(bool*,int);
double importo_txt(char,double*,int);
int main (int argc, char** argv) {
// intestazione di lettura file
if ( argc < 3 ) {
  cout << "Uso del programma : " << argv[0] << " <n_data> <filename> " << endl;
  return -1 ;
}
int ndata = atoi(argv[1]);
double* data = new double[ndata];
char * filename = argv[2];
//importo file
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
    //funzione media
    double y,x,z =0;
    
    for ( int k = 0 ; k < ndata ; k++ ) {
        x=x+data[k];
    }
    y=x/ndata;
     cout<<"media aritmetica:" <<y << endl;
       double a=0;
    //funzione varianza
    for (int i=0;i<ndata;i++){
     

    a=a+((data[i]-y)*(data[i]-y));}
    z=a/ndata;
    
    z=sqrt(z);
    cout<<"varianza:"<< z << endl;
    //riordino


double * vcopy = new double[ndata];
for ( int k = 0 ; k < ndata ; k ++ ) vcopy[k] = data[k];



bool p=riordinaschifo(vcopy,ndata);
if(p>0){cout<< "riordinato" <<endl;}
//mediana
double mediana = 0;
mediana=CalcolaMediana(vcopy,ndata);


cout << "Mediana = " << mediana << endl;
//stampa su foglio

ofstream fout("files_uscita.txt");
for ( int k = 0 ; k < ndata ; k ++ ){
  fout<<vcopy[k]<<endl;
}
fout.close();



    delete [] data,vcopy;
    
 return 0;
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
void stampa_txt(bool*y,int x){
  ofstream fout("files_uscita.txt");
    for ( int k = 0 ; k < x ; k ++ ){
    fout<<y[k]<<endl;
    }
fout.close();

}
double importo_txt(char filename,double* data,int ndata){
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
  return data[] ;

}