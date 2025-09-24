/*
In this problem I learn about the Fermat factorization method
and its sieve improvement. 
*/
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

// ATTEMPT 1: USING FERMAT'S FACTORIZATION PREEMPTIVELY SINCE N IS HUGE

long long max(long long a, long long b){
    return ((a > b)? a : b);
}

long long Root(long long n){
    /*
    Way to check for a perfect square without any
    floating point hassle 
    */
    
    if (n < 0) return -1;   
    if (n == 0 || n == 1) return n;

    long long low = 1;
    long long high = n;

    long long mid = low + (high - low) / 2;
    long long answer = 0;

    while (low <= high) {
        if(mid * mid == n) return mid;
        else if (mid * mid < n) {
            answer = mid;
            low = mid + 1;
        }
        else high = mid - 1;
        mid = low + (high - low) / 2;
    }
    return answer;
}

long long FermatSieve(long long n){
    // Works for only odd integers
    long long a = ceil(sqrt(n));
    /*
    We know that perfect squares are only 0, 1, 4, 5, 9, 16 mod 20
    and since our N is 3 mod 20, we find that b^2 = a^2 - N must be 
    17, 18, 1, 2, 6, 13 mod 20 out of which only 1 can be a perfect square
    and thus a^2 must be 4 mod 20 which implies we need check only those values 
    of a which are 2, 8, 12 or 18 mod 20 (equivalently, +- 2 and +- 8 mod 20).
    */


    /* 
    Also, when do we stop the algorithm? Note that when a > N, say a = N + k for 
    k >= 0, then a^2 - b^2 = (N + k - b)(N + k + b). Since this already has a 
    factor much greater than N so we cannot really have a^2 - b^2 = N which we
    desire. Thus checking till N will be much more than sufficient.
    */
    while(a <= n){
 
        long long bsquared = (a * a) - n;
        long long r = Root(bsquared);

        if(r * r == bsquared){
            long long x = abs(a - Root(bsquared));
            if(x > 1 && x < n) return x;
            else a++;
        } 
        else a++;
    }
    return n;
}

long long maxPrimeFactor(long long N){
    if(N <= 3) return N;

    long long p1 = FermatSieve(N);
    long long p2 = N / p1;
  
    if (p1 == N) return N;
    long long x = maxPrimeFactor(p1);
    long long y = maxPrimeFactor(p2);
   
    return ((x > y)? x : y);
}

// ATTEMPT 2: ATTEMPT 1 TOOK A HUGE AMOUNT OF TIME SO SWITCHED TO TRADITIONAL METHODS
bool* sieveOfEratosthenes(long long N){

    bool* primes = (bool*) malloc((N + 1) * sizeof(bool));
    for(int i = 0; i <= N; i++) primes[i] = true;

    primes[0] = primes[1] = false;
    for(int p = 2; p <= N; p++){
        if(primes[p]){
            for(int i = p * p; i <= N; i += p){
                primes[i] = false;
            }
        }
    }
    return primes;
}

long long largestPrimeFactor(long long n){
    if(n <= 3) return n;
    bool* primes = sieveOfEratosthenes(n);
    
    long long idx = 1, maxi = 0;
    while(1){
        if(idx > n) break; // We can go up to n because we divide n each time a prime divisor is found
        if(primes[idx] && n % idx == 0){
            maxi = idx;
            n /= idx;
        }
        idx++;
    }
    return (maxi ? maxi : n);
}

// ATTEMPT 3: TOOK SOME INTERNET HELP SINCE THE ARRAY WAS TOO LARGE IN ATTEMPT 2
long long finalsolution(long long n) {
    long long maxPrime = -1;

    while (n % 2 == 0) {
        maxPrime = 2;
        n /= 2;
    }
    for (long long i = 3; i*i <= n; i += 2) {
        while (n % i == 0) {
            maxPrime = i;
            n /= i;
        }
    }
    if (n > 2) maxPrime = n;

    return maxPrime;
}

int main() {
    long long N = 600851475143LL;
    printf("%lld\n", finalsolution(N));
}