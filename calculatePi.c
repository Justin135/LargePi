#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define LIMIT 10
#define MAX(a, b) (( a > b ) ? a : b) // Get the max of two numbers.
#define MIN(a, b) (( a > b ) ? b : a) // Get the min of two numbers.

char * addNums(char x[], char y[]);
char * addNums(char x[], char y[]) {
    
    long long int length = MAX(strlen(x), strlen(y)) + 1; // Get the max length of the strings.
    char * sum = (char *) malloc((length + 1) * sizeof(char)); // Allocate the memory for the new sum variable.
    
    if(sum == NULL) {
        exit(1); // malloc didn't work. Memory not allocated.
    }
    
    memset(sum, '0', length * sizeof(char)); // Allocates and sets memory to '0'.
    sum[length] = '\0'; // Manually set the null terminator.
    
    int i = strlen(x) - 1;
    int j = strlen(y) - 1;
    int k = strlen(sum) - 1;
    int d, carry = 0;
    
    // Iterate through both numbers.
    while(i >= 0 && j >= 0) {
        d = (x[i] - 48) + (y[j] - 48) + carry;
        carry = (d / 10);
        sum[k] = (d % 10) + 48;
        i--;
        j--;
        k--;
    }
    
    // Will run if the first number is larger than the second.
    while(i >= 0) {
        d = (x[i] - 48) + carry;
        carry = d / 10;
        sum[k] = (d % 10) + 48;
        
        i--;
        k--;
    }
    
    // Will run if the second number is larger than the first.
    while(j >= 0) {
        d = (y[j] - 48) + carry;
        carry = d / 10;
        sum[k] = (d % 10) + 48;
        
        j--;
        k--;
    }
    
    sum[0] = carry + 48; // Set the leftmost digit to the carry.
    return sum;
}

char * subtractNums(char x[], char y[]);
char * subtractNums(char x[], char y[]) {
    
    long long int length = MAX(strlen(x), strlen(y)); // Get the max length of the strings.
    char * minus = (char *) malloc((length + 1) * sizeof(char)); // Allocate the memory for the new sum variable.
    
    if(minus == NULL) {
        exit(1); // malloc didn't work. Memory not allocated.
    }
    
    
    memset(minus, '0', length * sizeof(char)); // Allocates and sets memory to '0'.
    minus[length] = '\0'; // Manually set the null terminator.
    
    int i = strlen(x) - 1;
    int j = strlen(y) - 1;
    int k = strlen(minus) - 1;
    int d, borrow = 0;
    
    // Iterate through both numbers.
    while(i >= 0 && j >= 0) {
        d = (x[i] - 48) - (y[j] - 48) - borrow;
        
        if(d < 0) {
            borrow = 1;
            d += 10;
        }
        else {
            borrow = 0;
        }
        minus[k] = (d) + 48;
        
        i--;
        j--;
        k--;
    }
    
    // If there are still more digits in the first number.
    while(i >= 0) {
        minus[k] = x[i];
        i--;
        k--;
    }
    
    minus[0] -= borrow;
    
    /*
    if(minus[0] == '0') {
        
        int num0 = 1; // Count the number of 0s.
        for(int i = 1;minus[i] != '0';i++) {
            num0++;
        }
        
        char * new_minus = (char *) malloc((length - num0 + 1) * sizeof(char));
        
        for(int i = num0;i < length;i++) {
            new_minus[i] = minus[i];
        }
        
        new_minus[length - num0] = '\0';
        
        free(minus);
        return new_minus;
    }
    */
    
    return minus;
}

char * exponent10(long long int n);
char * exponent10(long long int n) {
    
    char * value = (char *) malloc((n + 2) * sizeof(char)); // Allocate n + 2 (1 for \0 and 1 for the first digit being 1);
    
    memset(value, '0', (n + 1) * sizeof(char));
    value[n + 1] = '\0';
    value[0] = '1';
    
    return value;
}

char * multiply(char x[], int n);
char * multiply(char x[], int n) {
    
    long long int length = (strlen(x) + floor(log10(n)) + 1); // Length of new array.
    char * product = (char *) malloc((length + 1) * sizeof(char));
    
    if(product == NULL) {
        exit(1); // malloc didn't work. Memory not allocated.
    }
    
    memset(product, '!', length * sizeof(char)); // Set all values to '!'
    product[length] = '\0'; // Manually set the null terminator.
    
    int k = strlen(product) - 1;
    int i = strlen(x) - 1;
    int prod = 0;
    int carry = 0;
    int tempN = n; // Used for the multiplication so as to not overwrite the original n.
    
    while(k >= 0) {
        
        prod = 0; // Initialize product.
        tempN = n; // Reinitialize tempN.
        
        for(int j = 0;tempN != 0;j++) {
            
            if((i + j) < 0) {
                tempN /= 10;
                continue;
            }
            
            if((k + j) >= length) 
                break;
            
            prod += ((x[i + j] - 48) * (tempN % 10)); // Carry out the multiplication with the (j+1)th rightmost digit of n.
            tempN /= 10; // Divide tempN by 10.
        }
        
        prod += carry;
        carry = (prod / 10); // Get the carryover.
        product[k] = (prod % 10) + 48;
        i--;
        k--;
    }
    
    product[0] = carry + 48; // Set the leftmost digit to the carry.
    return product;
}

char * intDivision(char x[], long long int n);
char * intDivision(char x[], long long int n) {
    
    unsigned long long int drawdown = 0;
    int sub = 0;
    
    long long int length = strlen(x); // Length of new array.
    char * quotient = (char *) malloc((length + 1) * sizeof(char));
    memset(quotient, '!', length * sizeof(char)); // Set all values to '!'
    quotient[length] = '\0'; // Manually set the null terminator.
    
    long long int k = 0;
    
    for(long long int i = 0;i < length;i++) {
        
        drawdown *= 10; // Multiply current drawdown by 10.
        drawdown += (x[i] - 48); // Add next digit.
        
        if(drawdown >= n) {
            
            // drawdown / n can be accomplished.
            quotient[k] = ((drawdown / n) + 48); // Save quotient value.
            k++; // Increment k.
            sub = n * (drawdown / n);
            drawdown -= sub; // Carry out long division subtraction.
            
            printf("%d\t\t%c\n", (drawdown / n), quotient[k - 1]);
        }
        
        printf("D%d\n", drawdown);
    }
    
    printf("%s\n", quotient);
   
    if(k < length) {
        
        char * new_quotient = (char *) malloc((k + 1) * sizeof(char));
        
        for(int i = 0;i < k;i++) {
            new_quotient[i] = quotient[i];
        }
        
        new_quotient[k] = '\0';
        
        free(quotient);
        return new_quotient;
    }
    
    return quotient;
}


int main(void) {
    
    char a[] = "72345";
    char b[] = "2346";
    
    char * c = subtractNums(a, b);
    char * d = multiply(a, 123);
    
    printf("%s\n", c);
    printf("%s\n", d);
    
    free(c);
    free(d);
    
    return 0;
}