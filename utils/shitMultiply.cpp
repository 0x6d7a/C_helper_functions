#include<stdio.h>

union Float {
    float f;
    int i;
};

float shiftMultiply(float x, int n) {
    union Float val;
    val.f = x;
    int exponent = (val.i >> 23) & 0xFF;
    exponent += n;
    val.i &= ~(0xFF << 23); 
    val.i |= (exponent & 0xFF) << 23; 
    return val.f;
}

float multi(float a,int n) {
    float rst = 0.0;
    if (n == 0) {    
        return 0;
    }
    int binary[64];  
    int i = 0;
    while (n > 0) {
        binary[i] = n & 1;  
        n = n >> 1;  
        i++;
        if (binary[i - 1] == 1) {
            rst += shiftMultiply(a, i-1);
        }
    }
    return rst;

}

int main() {
    printf("%f", multi(1.556, 3));
    
	return 0;
}

