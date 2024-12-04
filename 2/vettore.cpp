#include"vettore.h"

void importo_txt_v(char* filename,Vettore & a){
      ifstream fin(filename);
        double data ;
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
void stampa_txt_v(const Vettore & y ){
    ofstream fout("files_uscita.txt");
    for ( int k = 0 ; k < y.getn() ; k ++ ){
    fout<<y.getcomponent(k)<<endl;
    }
fout.close();

}