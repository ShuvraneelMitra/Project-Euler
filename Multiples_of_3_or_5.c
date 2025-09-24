#include <stdio.h>

int main() {
    int n = 1000;
    int sum = 0;

    for(int i=0; i<n; i++){
        if((i % 3 == 0) || (i % 5 == 0)) sum += i;
    }
    printf("%d", sum);
}

/*
The above solution is that of O(n) complexity and is one that is
hastily rigged up by an excited student. What he might know, but fails
to acknowledge, is that there exists an O(1) solution:

int sum_Divby(int target, int k){
    int num = target / k;
    return k * (num * (num + 1)) / 2; // Can divide first to prevent overflow
}

int main(){
    printf("%d", sum_Divby(999, 3) + sum_Divby(999, 5) - sum_Divby(999, 15));
}
*/