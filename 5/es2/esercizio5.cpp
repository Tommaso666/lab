#include "particella.h"
#include <iostream> 

using namespace std;

int main() {

  Particella a (1.0,1.6E-19);
  Elettrone *e    = new Elettrone();

  // Metodi della classe base
  cout << "Particella " << a.GetMassa() << "," << a.GetCarica() << endl;
  a.Print(); 

  // Metodi della classe derivata (inherited) 
  cout << "Elettrone " << e->GetMassa() << "," << e->GetCarica() << endl;
  e->Print(); 

  Particella b(a) ;   // costruisco una Particella a partire da una Particella
  Particella d(*e) ;  // costruisco una Particella a partire da un Elettrone
//   Elettrone  f(d)  ;  // costruisco un Elettrone a partire da una Particella 

  return 0;

}