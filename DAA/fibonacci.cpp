#include <bits/stdc++.h>
using namespace std;

int recursive(int n){
    if(n<=0) return 0;
    if(n==1) return n;
    return recursive(n-1) + recursive(n-2);
}
int iterative(int n){
    if(n<=0) return 0;
    if(n==1) return n;
    int f1 = 0,f2 = 1;
    for(int i=2;i<=n;i++){
        int temp = f1+f2;
        f1 = f2;
        f2 = temp;
    }
    return f2;
}

int main(){
    int n = 4;
    cout << iterative(n) << endl;
    cout << recursive(n) << endl;
    return 0;
}