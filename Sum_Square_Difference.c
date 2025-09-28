#include <stdio.h>

int main() {
    /*
    Simplify (n(n+1)/2)*2 - (n(n+1)(2n+1)/6)
    */
   long long n = 100;
   printf("%lld", ((n-1)*n*(n+1)*(3*n+2))/12);
}