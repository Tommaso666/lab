#include<iostream>
#include<cmath>
#include <fstream>
#include <string>

use name space std;
struct punto {
    float x, y;
};

struct cerchio { 
    punto c;
    float r;
};

int numerinelfile(const char* f)
void caricacodici( int* x,int dim)
void caricacerchi( cerchio* x ,int dim)
bool esistecodice( cerchio c ,int*x , int dim)
int screma(cerchio*x ,int dim , int *c ,int dim_c)
float dist (float x1 ,float y1, float x2, float y2)
void stampa(cerchio c)
void stampasufile(ofstream &out,cerchio c ,float d)