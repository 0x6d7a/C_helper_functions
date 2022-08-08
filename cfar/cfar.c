#include "cfar.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

void ca(uint32_t buf, uint16_t len, uint8_t guard, uint8_t noise, uint32_t l_bound)
{

}

void caso(uint32_t buf, uint16_t len, uint8_t guard, uint8_t noise, uint32_t l_bound)
{

}

void cago(uint32_t buf, uint16_t len, uint8_t guard, uint8_t noise, uint32_t l_bound)
{

}

void os()
{

}

void conv1d(uint32_t signal, uint16_t len, uint32_t weight, uint16_t w_len, uint8_t mode, uint32_t output)
{
    uint16_t lconv = len + weight - 1;
    uint16_t i, k;

    for (i = 0; i < lconv; i++)
    {

    }

}

void conv1d_full(uint32_t signal, uint16_t len, uint32_t weight, uint16_t w_len, uint8_t mode, uint32_t output)
{
    uint16_t lconv = len + weight - 1;
    uint16_t i, k;

    for (i = 0; i < lconv; i++)
    {
        uint16_t kmin, kmax;

        output[i] = 0;

        kmin = (i >= w_len - 1) ? i - (w_len - 1) : 0;
        kmax = (i < len - 1) ? i : len - 1;

        for (k = kmin; k <= kmax; k++)
        {
            output[i] += signal[k] * weight[i - k];
        }   
    }

}