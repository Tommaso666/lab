#include <iostream>
using namespace std;
int main(){
    int n,y,x;
    n=0;
    y=0;
    cin>> x;
    while(n!=x){
        n=n+1;
        while(y!=x){
            y=y+1;
            cout<<n*y <<" ";
        }cout << endl;
        y=0;
    }
return 0;
}