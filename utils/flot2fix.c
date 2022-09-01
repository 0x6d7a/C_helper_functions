#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <stdio.h>
#include <math.h>
#define FIXED_BIT 12

unsigned short int float2fix(float n)
{
    unsigned short int int_part = 0, frac_part = 0;
    int i;
    float t;

    int_part = (int)floor(n) << FIXED_BIT;
    n -= (int)floor(n);

    t = 0.5;
    for (i = 0; i < FIXED_BIT; i++) {
        if ((n - t) >= 0) {
            n -= t;
            frac_part += (1 << (FIXED_BIT - 1 - i));
        }
        t = t /2;
    }

    return int_part + frac_part;
}

int main(){  
    float n = 12.437;
    printf("%d", float2fix(n));
    return 0;  
}  