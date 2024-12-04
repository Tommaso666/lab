#ifndef __vettore__
#define __vettore__

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>


using namespace std;

//classe
template <typename T> class Vettore{
    public:
    Vettore(){
        m_N=0;
        m_v=NULL;
    };
    Vettore(int n){
          m_N=n;
        m_v = new double [n];
        for(int k=0;k<n;k++) m_v[k]=0;
    };
    ~Vettore(){delete[]m_v;};
    unsigned int getn() const{return m_N;}; //dimensione del vettore
    void setcomponent(int k,T val){m_v[k] =val;}; //valore del vettore
    T getcomponent(int k)const{return m_v[k] ;}; //dimmi il valore alla posizione k
    
    

    private:
    unsigned int m_N;
    T* m_v;




};

//funzioni

template <typename T> Vettore<T> importo_txt_v(char*,Vettore &);
template <typename T> Vettore<T> duplicavet(Vettore & , Vettore & );
double media_v(const Vettore &);
double varianza_v(const Vettore &);
void riordinadati_v(Vettore &);
double CalcolaMediana_v(const Vettore &);
template <typename T> void stampa_txt_v(const Vettore &,char* filename) ;





//==========================================================================================================================================================
//testo funzioni
//==========================================================================================================================================================









void importo_txt_v(char* filename,Vettore & a){
      ifstream fin(filename);
        T data ;
    if ( !fin ) { 
      cout << "Cannot open file " << filename << endl;    
      exit(33);
    } else {
      for ( int k = 0 ; k < a.getn() ; k++ ) {
       
        fin >> data;
        a.setcomponent( k , data );
        if ( fin.eof() ) { 
          cout << "End of file reached exiting" << endl; 
          exit(33) ;      
        }    
      }        
    }
    return a;

}

void duplicavet(Vettore & a,Vettore & b){
    for(int i=0;i<a.getn();i++){;
      b.setcomponent(i,a.getcomponent(i));
    };
  
}
double media_v( const Vettore & a){
    double y,l=0;
    
    for ( int k= 0 ; k < a.getn() ; k++ ) {
        l=l+a.getcomponent(k);
    }
    y=l/ a.getn();

     return y;
}
double varianza_v(const Vettore  & x){
    double y,a,z =0;
    y=media_v(x);
    for (int i=0;i<x.getn();i++){

    a=a+((x.getcomponent(i)-y)*(x.getcomponent(i)-y));
    };
  
    
    z=sqrt(a/x.getn());

return z;

}
void riordinadati_v(Vettore & x) {
    int imin;
    double min;
    int n = x.getn();  // Ottieni la dimensione del vettore
    
    for (int j = 0; j < n - 1; j++) {
        imin = j;  // Supponiamo che il minimo sia l'elemento corrente
        min = x.getcomponent(j);  // Inizializza min con il valore alla posizione j
        
        // Cerca il valore minimo nel resto del vettore
        for (int i = j + 1; i < n; i++) {
            if (x.getcomponent(i) < min) {
                min = x.getcomponent(i);  // Aggiorna il minimo
                imin = i;  // Aggiorna l'indice del minimo
            }
        }
        
        // Scambia l'elemento corrente con l'elemento minimo trovato
        double temp = x.getcomponent(j);
        x.setcomponent(j, x.getcomponent(imin));
        x.setcomponent(imin, temp);
    }
}

  
double CalcolaMediana_v(const Vettore & y){
double mediana;
if ( y.getn()%2 == 0 ) {    
  //se pari
  mediana = (y.getcomponent( y.getn()/2 -1  ) + y.getcomponent( y.getn()/2 ) ) /2.;    

}else {
  mediana = y.getcomponent(y.getn()/2);    
}// se dispari


return mediana;
}
 void stampa_txt_v( const Vettore<T> & v , char* filename ) {
//nme file output
   char outfilename[1024];
    const char * suffix = "_out";
    int i;
    for (i = 0; filename[i]; i++)
    outfilename[i] = filename[i];
    for (int j = 0; suffix[j]; i++, j++)
    outfilename[i] = suffix[j];
    outfilename[i] = 0;
//funzione effettiva
    ofstream out(outfilename);
    if ( !out ) {
    cerr << "Non posso creare il file " << filename << endl;
    return;
    }
    for (int i=0; i<v.GetN(); i++) out << v.GetComponent(i) << endl;
    out.close();
    return;
}









#endif //__vettore__
