
#include <iostream> 
#include <string>
using namespace std;
int main(){
    bool z=true;
    int y,n;
    n=0;
    string s;
    cout<< "isnerire una parola senza maiuscole:";
    cin >> s;
    y=s.length();
    while ((y/2)!=n){
        if (z=true){
        if(s[n]=s[y-n]){z=true;}
        else{z=false;}
        n=n+1;}
        else{break;}
    }
    if (z == true) {
        cout<< " parola palindroma" << endl;
    }
    else { 
        cout<< " parola non palindroma" << endl;
    }
    return 0;
}