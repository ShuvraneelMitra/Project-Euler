/*
We note that by Binet's Formula, F_n = (phi^n + phi^(-n))/sqrt(5) which is
less than double of phi^n. This means that F_n will reach 4M for n at most 
log_phi(4M), or at most 32. Thus we only need an array with size at most 32. 
*/

#include <stdio.h>
#define MAXSIZE 32

int main() {
    long long fib[MAXSIZE];
    fib[0] = 1;
    fib[1] = 2;
    long long sum = 2;
    
    for (int i = 2; i < MAXSIZE; i++) {
        fib[i] = fib[i-1] + fib[i-2];
        if (fib[i] > 4000000) break;
        if (fib[i] % 2 == 0) sum += fib[i];
    }
    // Note that all the indices of type 3n + 1 with 0-indexing contain
    // even Fibonacci numbers.
    
    printf("%lld\n", sum);
    return 0;
}