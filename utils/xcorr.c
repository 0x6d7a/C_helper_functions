#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void separate(void)
{
    printf("##########\n");
}


int xcorr(float *x1, float *x2, float *y, int size_1, int size_2, int size_y)
{
    if(size_y != size_1 + size_2 -1)
    {
        return -1;
    }
    else
    {
        int k=0;
        int i=0;
        for(k=0;k<size_y;k++){
            *(y+k) = 0;
            for(i=(0>k+1-size_1?0:k+1-size_1);i<=(k<size_2-1?k:size_2-1);i++){
                *(y+k) +=(*(x1+k-i)) *(*(x2+size_2-1-i));
            }
        }
        return 0;
    }
}

int main(int argc, char const *argv[])
{

    float x[21] = {-11.8454,-10.9080,-16.6661,-25.2124,-24.8385,-24.5294,-24.9492,-23.3069,8.1482,19.5922,21.0827,13.3732,-8.6912,-27.0151,-26.4308,-21.1915,-28.2717,-25.5113,-14.8906,-12.6445,-17.4180};
    float y[21] = {-16.6661,-25.2124,-24.8385,-24.5294,-24.9492,-23.3069,8.1482,19.5922,21.0827,13.3732,-8.6912,-27.0151,-26.4308,-21.1915,-28.2717,-25.5113,-14.8906,-12.6445,-17.4180,-17.4180,-17.4180};

    float z[39] = {0};

    xcorr(x, y, z, 20, 20, 39);
    for (int i = 0; i < 39; ++i)
    {
        printf("%f\n", z[i]);
    }
    return 0;
}
