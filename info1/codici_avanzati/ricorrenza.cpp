#include <iostream>
using namespace std
int main () {
    int n,x[5];
    do{
        cout >>"inserire numero"
        cin << n;
        for (int i = 0 ; i<5 ; i++){ if (n=i){x[i]=x[i]+1;}}
    }while (n<0);
    for (int i=0;i<5;i++){cout << i << " compare " << x[i] << "volte" << endl ;}
    return 0;
}