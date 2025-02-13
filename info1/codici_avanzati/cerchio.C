#include <iostream>
#include <cmath>
using namespace std;

struct punto {
    float x, y;
};

struct cerchio { 
    punto c;
    float r;
};

void leggiPunto (punto& p);
void leggipunti (punto *x, int dim);
float getpos ();
void leggicerchio(cerchio& c);

void stampapunto(punto p);
float dist (punto p, punto q);
bool nelcerchio (punto p, cerchio q);
float maxdist (punto *x, int dim, cerchio );

int main () {
    float z;
    bool appartiene [10] = {false};
    punto x[10];
    leggipunti (x,10);
    cerchio c;
    leggicerchio (c);
    for (int i=0;i<10;i++){
        if(nelcerchio(x[i],c ) == true){ 
            appartiene[i]= true;
            cout <<"coppia ( "<< x[i].x<<", " << x[i].y <<" )" << endl;
        }
    }
    z=maxdist(x ,10 ,c );
    cout << "massima distanza" << z <<endl;
    
    for (int i=0; i<10;i++){
        if (appartiene [i]){
            for(int a=i+1;a<10;a++){
                if(appartiene [a]){
                    if(z== dist(x[i],x[a])){
                        cout <<"coppia"<< x[i].x<<", " << x[i].y;
                        cout <<"coppia"<< x[a].x<<", " << x[a].y;

                    }
                }
            }
        }
    }
    
   
   

    return 0;
}


void leggiPunto (punto& p) {
    cin >> p.x >> p.y;
}

void leggipunti (punto *x, int dim) {
    for (int i = 0; i < dim; i++) {
        cout << "Inserisci coordinate punto " << i+1 << endl;
        leggiPunto (x[i]);
    }
}


float getpos(){ 
    float r ;
    do{
        cout<< "raggio cerchio";
        cin>> r ;
    }while (r<0);
    return r;
   
}

void leggicerchio(cerchio& c){
    cout << " centro cerchio coordinate:";
    leggiPunto (c.c) ;
    c.r = getpos ();
}

float dist (punto p, punto q){
    float d=sqrt(pow((p.x+q.x),2)+pow((p.y+q.y),2));
    return d;
}

bool nelcerchio (punto p, cerchio q){
    bool j;
    if (q.r =dist ( p ,q.c)){j=true;}
    return j;
}

float maxdist (punto *x, int dim, cerchio c ){
    float z=0;
    for(int i=0; i<dim ;i++){
        if (nelcerchio (x[i],c)==true){
            for(int a=0; a<dim ;a++){
                if (nelcerchio (x[a],c)== true)
                    if (z< dist(x[i],x[a])){z= dist(x[i],x[a]);
    }
    

    }}
    

}
return z;
}

