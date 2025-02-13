#include  <iostream>
#include  <string>
using namespace std;
int main(){
    string s[10];
    int a=0, x,y;
    for (int i=0; i<10;i++){getline( cin, s[i]);}
   for (int i=0; i<10;i++){
        a=a+s[i].length();
    }
    x=a/10;
    for (int i=0; i < 10;i++){
            if(x<s[i].length()){cout<<"*"<<s[i]<<"*"<<endl;}
            else {cout<< s[i]<<endl;}}
return 0;
}