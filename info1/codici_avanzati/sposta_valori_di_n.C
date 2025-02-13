#include <iostream>
using namespace std;
int main() {
    int z, y, p,x[10];
    for (int i=0;i<10;i++){
        cout<<"inserire numero:";
        cin>> x[i];
        }
        do { cout<<" inserire p:";
        cin>> p;}while (p<0);
        for(int n = 0 ; n<p ; n++){
            y=x[0];
            x[0]=x[10];
            for (int i=1;i,9;i++){
                z=x[i+1];
                x[i]=y;
                y=z;
            }
        }
     for (int i=0;i< 10 ;i++){
        cout << x[i] << " ";
    
     }
     cout<< endl;
     return 0 ;  
}