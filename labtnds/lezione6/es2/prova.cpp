#include "funzioni.h"
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    seno f(1,1);  // Dichiarazione dell'oggetto tangente
    middlepoint a;
    // valore del integrale
  
    double pimez = M_PI / 2;
    cout<<"il valore del integrale è : "<< a.integrale(f,0,pimez,2000)<<endl;


    return 0;
}
