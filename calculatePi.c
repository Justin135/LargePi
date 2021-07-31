#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LIMIT 10

char * calculatePi(int limit);
char * calculatePi(int limit) {
    
    char * pi = malloc(limit * sizeof(char));
    char digit = '\0';
    double d = 0;
    
    for(int k = 0;k < limit;k++) {
        
        d = (1 / pow(16, k))
            * ((4.0 / ((8.0 * k) + 1))
            - (2.0 / ((8.0 * k) + 4))
            - (1 / ((8.0 * k) + 5))
            - (1 / ((8.0 * k) + 6))
            );
        
        printf("%lf\n", d);
    }
    
    return pi;
}

int main(void) {
    
    char * pi = calculatePi(LIMIT);
    return 0;
}