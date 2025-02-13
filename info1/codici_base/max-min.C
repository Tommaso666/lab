#include <iostream>
using namespace std;
int main(){
    int z,x,y;
    cout <<"inserire numeri  ";
    cin >> x;
    z=x;
    y=x;
    while(x!=0){
    if(z<x){z=x;}
    else{if(x<y){y=x;}}
    cout <<"inserire numeri  ";
    cin >> x;}
    cout << "max " << z <<" "<< "min " << y <<endl;
    return 0;
}