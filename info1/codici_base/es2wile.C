#include <iostream>
using namespace std;
int main(){
    int n,x,y,z;
    cout<<"inserire numero";
    cin>>n;
    while(n<0){
        cout<<"inserire numero positivo";
        cin>>n;
        }
    y=n;
    while(y>0){
                y=y-1;
                cout<<"*";
            }cout<< endl ;
            y=n;
        x=n-2;
        while(x>0){ 
            x=x-1;
            cout<<"*" ;
            z=n-2;
            while(z>0){
                z=z-1;
                cout<<" ";
                }
            cout<<"*"<< endl;}
            while(y>0){
                y=y-1;
                cout<<"*";
            }cout<< endl ;
    
        
    return 0;
}


        
            


        
        
    