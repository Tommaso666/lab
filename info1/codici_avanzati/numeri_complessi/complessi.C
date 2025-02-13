#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;
struct complesso{
    float r;
    float i;
};

int contarighe(const char* f);
int contaRighe( const char* );
complesso coniugato( complesso );
complesso somma( complesso, complesso );
double modulo( complesso );
void stampa( complesso );
void stampaFile( ofstream&, complesso );
complesso prodotto( complesso, complesso );
void swap( complesso&, complesso& );
int screma( complesso*, int );
void ordina( complesso*, int );


int main (){
    int k = contaRighe( "complessi.in" );
    //controllo files
    if ( k == -1 ) {
		cout << "File di input inesistente!" << endl;
		return -1;
	}
	if ( k == 0 ) {
		cout << "File di input vuoto!" << endl;
		return -1;
	}
    //APERTURA ARRAY DINAMICO
    complesso* C = new complesso[k];
    //lettura file
    ifstream in;
	in.open("complessi.in");

	for( int i = 0; i < k; i++ ){
		in >> C[i].r >> C[i].i;
        }

	in.close();

    //creazione file out
    ofstream out;
	out.open("complessi.out");
    
    //stampa numeri sul foglio in base alle condizioni
    cout << endl << "Coniugato dei complessi con modulo superiore a 3" << endl;
	out << "Coniugato dei complessi con modulo superiore a 3" << endl;
    complesso sm ={0,0}
    //stampa numeri con modulo superiore a n e somma numeri minori di m
    for ( int i = 0; i < k; i++ ) {
		if ( modulo( C[i] ) > 3 ) {
			stampa( coniugato( C[i] ) );
			cout << endl;
			stampaFile( out, coniugato( C[i] ) );
			out << endl;
		}
		if ( C[i].r < 0 )
			sm = somma( sm, C[i] );
	}
    //stampa numeri sul foglio in base alle condizioni
    cout << endl << "Somma dei complessi con parte reale negativa" << endl;
	stampa( sm );
	cout << endl;
	out << endl << "Somma dei complessi con parte reale negativa" << endl;
	stampaFile( out, sm );
	out << endl;
    // altri ordini e fine programma
    complesso prod = prodotto( prodotto( C[0], C[1] ), C[2] );
	cout << endl << "Prodotto dei primi tre complessi" << endl;
	stampa( prod );
	cout << endl;
	out << endl << "Prodotto dei primi tre complessi" << endl;
	stampaFile( out, prod );
	out << endl;
	
	int s = screma( C, k );
	
	ordina( C, s + 1 );
	
	cout << endl << "Primi tre complessi dopo scrematura e ordinamento" << endl;
	out << endl << "Primi tre complessi dopo scrematura e ordinamento" << endl;
	for ( int i = 0; i < 3; i++ ) {
		stampa( C[i] );
		cout << endl;
		stampaFile( out, C[i] );
		out << endl;
	}
	
	cout << endl << "Ultimi tre complessi dopo scrematura e ordinamento" << endl;
	out << endl << "Ultimi tre complessi dopo scrematura e ordinamento" << endl;
	for ( int i = 3; i > 0; i-- ) {
		stampa( C[s - i] );
		cout << endl;
		stampaFile( out, C[s - i] );
		out << endl;
	}

	out.close();	




return 0;    
};






//conta righe
int contarighe(const char* f){
    ifsream in;
    in.open("f");
    if(!in){
        cout << "errore di lettura" <<endl;
        return -1;
    }
    string s;
    int k ;
    getline (in,s)
    while (! in.eof()){
    k++;
    getline (in,s)
    }
return k;
}
complesso coniugato(complesso a) {
    complesso s = {a.r,-a.i};
    return s;
}
//scrematura
void swap( complesso& a, complesso& b ) {
	complesso t = a;
	a = b;
	b = t;
}

int screma( complesso* X, int d ) {
	int t = d - 1;
	for ( int i = 0; i <= t; i++ )
		if ( X[i].r < 0 ) {
			swap( X[i], X[t] );
			i--;
			t--;
		}
	return t;
}
// operazioni sui complessi
complesso somma( complesso a, complesso b ) {
	complesso s = {a.r + b.r, a.i + b.i};
	return s;
}

complesso prodotto( complesso a, complesso b ) {
	complesso s = {a.r*b.r-a.i*b.i, a.r*b.i+a.i*b.r};
	return s;
}

double modulo( complesso a ) {
	return sqrt(a.r*a.r + a.i*a.i);
} 
// comando di stampa numeri complessi
void stampa( complesso a ) {
	cout << a.r << "\t\t";
	if ( a.i < 0 )
		cout << "- i" << -a.i;
	else
		cout << "+ i" << a.i;
}

void stampaFile( ofstream& o, complesso a ) {
	o << a.r << "\t\t" << a.i;
}
//ordina array affinchè x[n]<x[m] sia sempre vera
void ordina( complesso* X, int d ) {
	for ( int i = 0; i < d - 1; i++ )
		for ( int j = i + 1; j < d; j++ )
			if ( X[j].r < X[i].r )
				swap( X[i], X[j] );
}
