/*
We need to find LCM(1, 2, ..., n). Use
LCM(a, b, c) = LCM(LCM(a, b), c) and LCM(a, b) = ab/HCF(a, b)
*/
#include <stdio.h>

int gcd(int a, int b) {
    while(a > 0 && b > 0) {
        if(a > b) {
            a = a % b;
        }
        else {
            b = b % a; 
        }
    }
    if(a == 0) {
        return b;
    }
    return a;
}

int main(){
    int n = 20;
    long long lcm = 1;
    for(int i=1; i<=n; i++){
        lcm = (lcm * i) / gcd(lcm, i);
    }
    printf("%lld", lcm);
}