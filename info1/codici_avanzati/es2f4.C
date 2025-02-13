#include <iostream>
using namespace std;
int main(){
    int x[10];
    int n,y;
    for (int i=0;i<10;i++){
        cout<<"inserire numero:";
        cin>> x[i] ;
        }
        cout <<"inserire numero:";
        cin>> n;
        y=0;
    for (int i=0;i<10;i++){
        if(n==x[i] ){y=y+1;}
    }
    if (y==0){cout<<"n non appartiene ad x" << endl;}
    else{cout<<"n appartiene alla serie e compare "<< y <<" volte"<< endl;}

}