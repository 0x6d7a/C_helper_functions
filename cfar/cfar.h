#ifndef _CFAR_H
#define _CFAR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))


typedef signed char             int8_t;   
typedef short int               int16_t;  
typedef int                     int32_t;    
  
typedef unsigned char           uint8_t;  
typedef unsigned short int      uint16_t;  
typedef unsigned int            uint32_t;   

// extern uint32_t l_kernel[CFAR_LEN];
// extern uint32_t r_kernel[CFAR_LEN];

void ca(uint32_t *buf, uint16_t len, uint8_t guard, uint8_t noise, uint32_t l_bound, uint32_t *threshold, uint32_t *noise_floor);
void caso(uint32_t *buf, uint16_t len, uint8_t guard, uint8_t noise, uint32_t l_bound, uint32_t *l_win, uint32_t *r_win, uint32_t *threshold, uint32_t *noise_floor);
void cago(uint32_t *buf, uint16_t len, uint8_t guard, uint8_t noise, uint32_t l_bound, uint32_t *l_win, uint32_t *r_win, uint32_t *threshold, uint32_t *noise_floor);
void os_cfar();
void cfar_window(uint32_t *signal, uint16_t len, uint8_t guard_len, uint8_t noise_len, uint32_t *l_win, uint32_t *r_win, uint32_t *l_kernel, uint32_t *r_kernel);
void conv1d_same(uint32_t *signal, uint16_t len, uint32_t *weight, uint16_t w_len, uint32_t *output);
void conv1d_full(uint32_t *signal, uint16_t len, uint32_t *weight, uint16_t w_len, uint32_t *output);
void findCFARPeak(uint32_t *buf, uint16_t len, uint32_t *thr, uint32_t *maxval, uint16_t *maxind);


#endif