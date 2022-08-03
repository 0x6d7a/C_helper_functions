#ifndef _MXS_ALGO_H
#define _MXS_ALGO_H

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

typedef signed char             int8_t;   
typedef short int               int16_t;  
typedef int                     int32_t;    
  
typedef unsigned char           uint8_t;  
typedef unsigned short int      uint16_t;  
typedef unsigned int            uint32_t;  


uint16_t peakfinder(uint32_t *buf, uint16_t lbuf, uint16_t *peakInds, uint32_t *peakMags);
void diff(uint32_t *buf, uint16_t lbuf, int32_t *dbuf);
uint16_t signChg(int32_t *buf, uint16_t lbuf, uint16_t *idxBuf);
void genData(uint32_t *buf, uint16_t lbuf, uint16_t *idxBuf, uint16_t lIdxBuf, uint32_t *x, uint16_t *ind);
void arrmax(uint32_t *x, uint16_t l, uint32_t *val, uint16_t *ind);
uint32_t max(uint32_t *x, uint16_t l);
void arrmin(uint32_t *x, uint16_t l, uint32_t *val, uint16_t *ind);
uint32_t min(uint32_t *x, uint16_t l);

#endif