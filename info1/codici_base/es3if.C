#include <iostream>
#include <cmath>
using namespace std;
int main(){
    int n,y,t,r,j,p,h,a=0;
    double z;
     cin>> n;
     n=n-1;
    int x[10];
    //int* x = new int[n];
    for (int i=0;i<n;i++){
        cout<<"inserire numero:";
        cin>> x[i];
        }
    for (int i=0;i<n;i++){
        a=a+x[i];
    }
    n=n+1;
    y=a/n;
    cout<<"media aritmetica:" <<y << endl;
    //funzione varianza
    for (int i=0;i<n;i++){
    a=a+((x[i]-y)*(x[i]-y));}
    z=a/n;
    cout<<"varianza:"<< z << endl;
    z=sqrt(z);
    t=y-z;
    r=y+z;
    j=x[1];
    for (int i=0;i<n;i++){
        if(j>x[i]){j=x[1];}
    }
    cout<<" minimo serie: "<< j <<endl;

    for (int i=0;i<n;i++){
        if(x[i]<t){cout <<"numero che dista piu' della deviazione standard:" << x[i] << endl;}
        if(x[i]>r){cout <<"numero che dista piu' della deviazione standard:" << x[i] << endl;}
    }
    h=0;
    for (int i=0;i<n;i++){
        p=x[i];
        for (int i=0;i<n;i++){
            if(p>x[i]){
                h=h+1;
                cout << h <<"* coppia("<<p<<","<<x[i]<<")" <<endl;
        }

        }


    }
    
    return 0;


    



}