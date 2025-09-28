/*
By the prime number theorem, pi(x) ~ x/ln x
so if we want pi(x) = 10001 then we approximately solve for x/ln x to get an idea
for the upper bound. WolframAlpha gives x ~ 116684 so we keep x = 120000 for safety
and construct a Sieve of Eratosthenes.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool* sieveOfEratosthenes(long long N){

    bool* primes = (bool*) malloc((N + 1) * sizeof(bool));
    for(int i = 0; i <= N; i++) primes[i] = true;

    primes[0] = primes[1] = false;
    for(long long p = 2; p <= N; p++){
        if(primes[p]){
            for(long long i = p * p; i <= N; i += p){
                primes[i] = false;
            }
        }
    }
    return primes;
}

int main() {
    long long N = 120000;
    int target = 10001;
    bool* primes = sieveOfEratosthenes(N);
    long long count = 0;
    for(long long i=0; i<=N && count < target; i++){
        if(primes[i]) count++;
        if(count == target) printf("%d", i);
    }
    free(primes);
}