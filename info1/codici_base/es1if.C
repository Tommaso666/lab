#include <iostream>
#include <cmath>
using namespace std;
int main(){
    int a,b,c;
    double x,y,d;
    cin>>a >>b >>c;
    d=b*b-4*a*c;
    if(d<0){
        cout<<"non ci sono risultati appartenenti ai reali";
    }
    else{
        x=(-b-sqrt(d))/2*a ;
        y=(-b+sqrt(d))/2*a ;
        cout<<"x(1)"<<x<<" x(2)"<<y<<endl;
        }
        return 0;
}