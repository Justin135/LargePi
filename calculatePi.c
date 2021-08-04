#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define LIMIT 10

char * addNums(char x[], char y[]);
char * addNums(char x[], char y[]) {
    
    char * sum;
    if(strlen(x) >= strlen(y)) sum = malloc((strlen(x) + 1) * sizeof(char));
    else sum = malloc((strlen(y) + 1) * sizeof(char));
    
    int i = strlen(x) - 1;
    int j = strlen(y) - 1;
    int k = strlen(sum) - 1;
    int d, carry = 0;
    
    while(i >= 0 && j >= 0) {
        
        d = (x[i] - 48) + (y[j] - 48) + carry;
        carry = (d / 10);
        sum[k] = (d % 10) + 48;
        printf("%c ", sum[k]);
        i--;
        j--;
        k--;
    }
    
    while(i >= 0) {
        d = (x[i] - 48) + carry;
        carry = d / 10;
        sum[k] = (d % 10);
        
        i--;
        k--;
    }
    
    while(j >= 0) {
        d = (y[j] - 48) + carry;
        carry = d / 10;
        sum[k] = (d % 10);
        
        j--;
        k--;
    }
    
    return sum;
}

char * calculatePi(int limit);
char * calculatePi(int limit) {
    
    char * pi = malloc(limit * sizeof(char));
    
    return pi;
}

int main(void) {
    
    char * pi = calculatePi(LIMIT);
    
    char num = '9';
    int nums = num - 48;
    
    char x[5] = "12345";
    char y[5] = "23456";
    char * z = addNums(x, y);
    
    printf("\n%s\n", z);
    free(z);
    free(pi);
    
    puts("All good.");
    
    return 0;
}