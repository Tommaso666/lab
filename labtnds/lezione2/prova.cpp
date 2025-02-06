
#include <iostream>

#include "vettore.h"

using namespace std;

int main ( ) {

  // costruttore senza argomenti ==>> crea un vettore di dimenione nulla 

  Vettore vnull ;
  cout << "Vettore vnull : dimensione = " << vnull.GetN() << endl;
  for ( unsigned int k = 0 ; k < vnull.GetN() ; k++ ) cout << vnull.GetComponent(k) << " " ;
  cout << endl;

  // construttore con intero : costruisco un OGGETTO di tipo vettore di lunghezza 10

  Vettore v(10);
  cout << "Vettore v : = dimensione = " << v.GetN() << endl;
  for ( unsigned int k = 0 ; k < v.GetN() ; k++ ) cout << v.GetComponent(k) << " " ;
  cout << endl;
  int comp = 3;
  cout << "Componente " << comp << " = " << v.GetComponent(comp) << endl;

  v.SetComponent(comp,-999) ;

  for ( unsigned int k = 0 ; k < v.GetN() ; k++ ) cout << v.GetComponent(k) << " " ;
  cout << endl;

  // anche come puntatore

  Vettore * vp = new Vettore(10);
  cout << "Vettore vp : = dimensione = " << vp->GetN() << endl;
  for ( unsigned int k = 0 ; k < vp->GetN() ; k++ ) cout << vp->GetComponent(k) << " " ;
  cout << endl;    

  delete vp;

  return 0;

}