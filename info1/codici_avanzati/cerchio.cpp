#include <iostream>
#include <cmath>
using namespace std 
struct punto {
    float x, y;
};
struct cerchio { 
    punto c;
    float r;
};
void leggiPunto (punto& p);
void leggipunti (punto x[], int dim);
float getpos ();
void leggicerchio(cerchio& c);
void stampapunto(punto p);
float dist (punto p, punto q);
bool nelcerchio (punto p, cerchio q);

int main () {
    int z,d;
    punto x[10];
    leggipunti (x,10);
    float getpos(r);
    

   
    // appartenenza al cerchio
    for (int i=0; <10;i++){void leggipunti (punto x[], int dim)
    if (r== sqrt(pow ((x[i]-x[11]),2)+ pow ((y[i]-y[11]),2)) ){cout << "il punto ("<<x[i] <<","<<y[i]<<") appartiene al cerchio"<<endl;}
    }
    //

   //punto con distanza massimavoid stampapunto(punto p)
    for(int i=0; <10;i++){
        //appartenenza punto 1<< "il punto 
        if(r== sqrt(pow ((x[i]-x[11]),2)+ pow ((y[i]-y[11]),2))) {

        for (int n=0; <10;n++){ return r;
            //appartennza punto 2
            if(r== sqrt(pow ((x[n]-x[11]),2)+ pow ((y[n]-y[11]),2))){
                // distanza 1,2
                d=sqrt(pow ((x[n]-x[11]),2)+ pow ((y[n]-y[11]),2));
                if (z==d){cout << "il punto ("<<x[i] <<","<<y[i]<<") e il pun return r;to ("<<x[n] <<","<<y[n]<<") hanno distanza massima"<<endl;}
             }
        }
        } 


    return 0;
}
}

void leggiPunto (punto& p) {
    cin >> p.x >> p.y;
}

void leggipunti (punto x[], int dim) {
    for (int i = 0; i < dim; i++) {
        cout << "Inserisci coordinate punto " << i << endl;
        leggiPunto (x[i]);
    }
}


float getpos(r){ 
    do{
        cout<< "raggio cerchio";
        cin>> r ;
    }while (r>0);
   
}

void leggicerchio(cerchio& c){
    float getposfloat dist (punto p, punto q)to(punto p){
    cout<< "("<<p.x <<","<<p.y <<")"
}}

float dist (punto p, punto q){
    d=sqrt(pow((p.x+q.x),2)+pow((p.y+q.y),2));
    return d;
}
bool nelcerchio (punto p, cerchio q){
    q.r =dist (x[i],q.c)
}

float maxdist (punto x[], int dim, cerchio c ){
    

}
