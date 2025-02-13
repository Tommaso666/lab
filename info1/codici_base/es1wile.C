#include <iostream>
using namespace std;
int main(){
    int n,x,y;
    cout<<"inserire numero";
    cin>>n;
    if(n<0){
        cout<<"inserire numero positivo";
        cin>>n;
        x=n;
        y=n;
        while(x>0){ 
            x=x-1;
            while(y>0){
                y=y-1;
                cout<<"*";
            }
            y=n;
            cout<< endl ;}
        }
        else{ 
            x=n;
            y=n;
            while(x>0){ 
            x=x-1;
            while(y>0){
                y=y-1;
                cout<<"*";
            }
            y=n;
            cout<< endl ;}
        }
    return 0;
}