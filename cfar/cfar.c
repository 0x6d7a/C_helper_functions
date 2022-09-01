#include "cfar.h"


void populate(uint32_t *buf, uint16_t len, uint32_t val)
{
    for (uint16_t i = 0; i < len; i++)
    {
        buf[i] = val;
    }
    
}

void fill(uint32_t *buf, uint16_t start, uint16_t end, uint32_t val)
{
    for (uint16_t i = start; i < end; i++)
    {
        buf[i] = val;
    }
    
}

void scale(uint32_t *buf, uint16_t len, uint32_t val)
{
    for (uint16_t i = 0; i < len; i++)
    {
        buf[i] = buf[i] * val;
    }
    
}

void divide(uint32_t *buf, uint16_t len, uint32_t val)
{
    for (uint16_t i = 0; i < len; i++)
    {
        buf[i] = buf[i] / val;
    }
    
}

void ca(uint32_t *buf, uint16_t len, uint8_t guard, uint8_t noise, uint32_t l_bound, uint32_t *threshold, uint32_t *noise_floor)
{
    uint16_t kernel_len = 1 + 2 * guard + 2 * noise;
    uint32_t *kernel = (uint32_t *)malloc(kernel_len * sizeof(uint32_t));

    populate(kernel, kernel_len, 1);
    fill(kernel, noise, noise + 2 * guard + 1, 0);

    conv1d_same(buf, len, kernel, kernel_len, noise_floor);

    divide(noise_floor, len, 2 * noise);

    for (uint16_t i = 0; i < len; i++)
    {
        threshold[i] = noise_floor[i] + l_bound;
    }

}

void caso(uint32_t *buf, uint16_t len, uint8_t guard, uint8_t noise, uint32_t l_bound, uint32_t *l_win, uint32_t *r_win, uint32_t *threshold, uint32_t *noise_floor)
{
    uint8_t edge_cells = guard + noise;


    for (uint16_t i = 0; i < len; i++)
    {
        noise_floor[i] = MIN(l_win[i], r_win[i]);
    }

    for (uint16_t i = 0; i < edge_cells; i++)
    {
        noise_floor[i] = r_win[i];
        noise_floor[len - i] = l_win[len - i];
    }

    for (uint16_t i = 0; i < len; i++)
    {
        threshold[i] = noise_floor[i] + l_bound;
    }


}

void cago(uint32_t *buf, uint16_t len, uint8_t guard, uint8_t noise, uint32_t l_bound, uint32_t *l_win, uint32_t *r_win, uint32_t *threshold, uint32_t *noise_floor)
{
    uint8_t edge_cells = guard + noise;


    for (uint16_t i = 0; i < len; i++)
    {
        noise_floor[i] = MAX(l_win[i], r_win[i]);
    }

    for (uint16_t i = 0; i < edge_cells; i++)
    {
        noise_floor[i] = r_win[i];
        noise_floor[len - i] = l_win[len - i];
    }

    for (uint16_t i = 0; i < len; i++)
    {
        threshold[i] = noise_floor[i] + l_bound;
    }
}

void os_cfar()
{

}

void cfar_window(uint32_t *signal, uint16_t len, uint8_t guard_len, uint8_t noise_len, uint32_t *l_win, uint32_t *r_win, uint32_t *l_kernel, uint32_t *r_kernel)
{
    for (uint8_t i = 0; i < noise_len; i++)
    {
        r_kernel[i] = 1;
        l_kernel[guard_len * 2 + noise_len * 2 - i] = r_kernel[i];
    }    

    conv1d_same(signal, len, l_kernel, 1 + 2 * guard_len + 2 * noise_len, l_win);

    conv1d_same(signal, len, r_kernel, 1 + 2 * guard_len + 2 * noise_len, r_win);

    for (uint8_t i = 0; i < len; i++)
    {
        l_win[i] = l_win[i] / noise_len;
        r_win[i] = r_win[i] / noise_len;
    }
    
}

void conv1d_same(uint32_t *signal, uint16_t len, uint32_t *weight, uint16_t w_len, uint32_t *output)
{
    uint16_t i, k, j;
	
	if (w_len % 2)
		j = (w_len - 1) >> 1;
	else
		j = w_len >> 1;

    for (i = j; i < len + j; i++)
    {
        uint16_t kmin, kmax;

        output[i] = 0;

        kmin = (i >= w_len - 1) ? i - (w_len - 1) : 0;
        kmax = (i < len - 1) ? i : len - 1;

        for (k = kmin; k <= kmax; k++)
        {
            output[i - j] += signal[k] * weight[i - k];
        }   
    }
}

void conv1d_full(uint32_t *signal, uint16_t len, uint32_t *weight, uint16_t w_len, uint32_t *output)
{
    uint16_t lconv = len + w_len - 1;
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

void findCFARPeak(uint32_t *buf, uint16_t len, uint32_t *thr, uint32_t *maxval, uint16_t *maxind)
{

    for (uint16_t i = 0; i < len; i++)
    {
        if (buf[i] > thr[i])
        {
            if (buf[i] > *maxval)
            {
                *maxval = buf[i];
                *maxind = i;
            }
               
        }
        
    }    
}