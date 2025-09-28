/*
Multiplying an n-digit number with another gives us either a (2n - 1)-digit 
number or a (2n)-digit number. We start by analysing 2n digit numbers, since
they are obviously bigger. A (2n)-digit palindrome necessarily takes the form

10^(2n-1)*a_(2n-1) + 10^(2n-2)*a_(2n-2) + ,,, + 10^n * a_n + 
    10^(n-1)*a_n + ... + 10*a_(2n-2) + a_(2n-1)

= (10^(2n-1) + 1)a_(2n-1) + (10^(2n-2) + 10)a_(2n-2) + ... + (10^n + 10^(n-1))a_n
= sum_{i = n}^(2n-1) (10^i + 10^(2n-1-i))*a_i where a_i = 0, 1, ..., 9

Couldn't think of a good algorithm and found nothing of note online, so here goes 
a brute force:
*/

#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int n){
    int n_copy = n;
    int rev = 0;
    while(n) {
        int digit = n % 10;
        rev = rev*10 + digit;
        n /= 10;
    }
    return (rev == n_copy);
}

int Root(int n){
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

int main(){
    int N = 999 * 999;
    bool flag = false;
    while(N--){
        int root = Root(N);
        for(int i=2; i<=root; i++){
            if(isPalindrome(N) && N % i == 0 && (100 <= N/i) && (N/i <= 999)){
                printf("%d", N);
                flag = true;
                break;
            }
        }
        if(flag) break;
    }
}

/*
I mean, the official solution tells us to do brute force, so all is good I guess

A nice solution from the forum:

You can also do this with pen and paper.  You have a number:

(100a + 10b + c)(100d + 10e + f) 

Which is a palindrone.  This factors out to:

                   100cd + 10ce + cf +
          1000bd + 100be + 10bf +
10000ad + 1000ae + 100af

Assuming the first digit is 9, then cf must be equal to nine.
Also, both a and d must then be equal to nine.  The only ways
to make the last digit of the product of two integers 9 would
be if those integers were either of:

1 and 9
3 and 3
7 and 7

So, both numbers must start with 9, end with either 1, 3, 7,
or 9, and one of them must be divisible by 11.  The only 
numbers divisible by 11 from 900 - 1000 are:

902
[b]913[/b]
924
935
946
[b]957[/b]
968
[b]979[/b]
990

You can discard all of those that do not end in either 1, 3,
7, or 9, and you are left with:

913
957
979

So now the presumed answer is either:

(900 + 10 + 3)(900 + 10x + 3)
(900 + 50 + 7)(900 + 10x + 7)
(900 + 70 + 9)(900 + 10x + 1)

Factoring all those out, you get:

810000 + 9000x + 2700 + 9000 + 100x + 30 + 2700 + 30x + 9
824439 + 9130x

Now, for the first digit 824439 + 9130x to be 9, x must be 9
(if x were 8, then 824439 + 9130x = 897479, and the first
digit is 8).  And so you have 913 * 993, which is the answer.
You can factor the others out to see if they produce a bigger
answer, which they don't.
*/