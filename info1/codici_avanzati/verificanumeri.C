#include <iostream>
using namespace std;
int main(){
    int x;
    bool primo = true;
    cout << "inserire numero: ";
    cin >> x;
    
    

    for (int i = 2; i <= x - 1 && primo; i++) {
        if(x % i == 0) {
            primo = false;
        }
    }
    if (primo == true) {
        cout << "il numero inserito e' primo" << endl;
    }
    else { 
        cout << "il numero inserito non e' primo" << endl;
    }
    return 0;
}