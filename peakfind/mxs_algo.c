#include "mxs_algo.h"

uint16_t peakfinder(uint32_t *buf, uint16_t lbuf, uint16_t *peakInds, uint32_t *peakMags)
{
    uint32_t leftMin, minMag, tempMag, sel;
    uint16_t lIdxBuf, lx, tempLoc, maxPeaks;
    uint8_t foundPeak;

    uint32_t *dbuf = (uint32_t *)malloc(sizeof(uint32_t) * lbuf);
    uint16_t *idxBuf = (uint16_t *)malloc(sizeof(uint32_t) * lbuf);

    sel = (max(buf, lbuf) - min(buf, lbuf)) >> 2;

    diff(buf, lbuf, dbuf);

    for(uint16_t i =1; i < lbuf; i++)
    {
        if(dbuf[i] == 0)
            dbuf[i] = INT_MIN;
    }

    lIdxBuf = signChg(dbuf, lbuf, idxBuf);
    
    uint32_t *x = (uint32_t *)malloc(sizeof(uint32_t) * (lIdxBuf + 2));
    uint32_t *dx = (uint32_t *)malloc(sizeof(uint32_t) * (3));
    uint16_t *ind = (uint16_t *)malloc(sizeof(uint16_t) * (lIdxBuf + 2));

    lx = lIdxBuf + 2;
    
    genData(buf, lbuf, idxBuf, lIdxBuf, x, ind);

    minMag = min(x, lx);
    leftMin = minMag;
    tempMag = minMag;
    foundPeak = 0;

    diff(x, 3, dx);

    if(dx[1] <= 0)
    {
        if(dx[1] * dx[2] > 0)
        {
            x[1] = 0;
            ind[1] = 0;
            lx--;
        }
    }
    else
    {
        if(dx[1] * dx[2] > 0)
        {
            x[0] = 0;
            ind[0] = 0;
            lx--;
        }
    }
    
    
    uint16_t ii;

    ii = (x[0] >= x[1]) ? 0 : 1;

    maxPeaks = (lx%2==0) ? lx >>1 : (lx>>1) + 1;

    uint16_t *peakLoc = (uint16_t *)malloc(maxPeaks * sizeof(uint16_t));
    uint32_t *peakMag = (uint32_t *)malloc(maxPeaks * sizeof(uint32_t));

    uint16_t cInd = 0;
    
    while (ii < lx)
    {
        if(foundPeak)
        {
            tempMag = minMag;
            foundPeak = 0;
        }

        if(x[ii] > tempMag && x[ii] > leftMin + sel)
        {
            tempLoc = ii;
            tempMag = x[ii];
        }

        if(ii == lx)
            break;

        ii++;

        if(foundPeak == 0 && tempMag > sel + x[ii])
        {
            foundPeak = 1;
            leftMin = x[ii];
            peakLoc[cInd] = tempLoc;
            peakMag[cInd] = tempMag;
            cInd++;
        }
        else if(x[ii] < leftMin)
        {
            leftMin = x[ii];
        }
    }

    if(x[lx-1] > tempMag && x[lx - 1] > leftMin + sel)
    {
        peakLoc[cInd] = lx-1;
        peakMag[cInd] = x[lx - 1];
        cInd++;
    }
    else if(!foundPeak && tempMag > minMag)
    {
        peakLoc[cInd] = tempLoc;
        peakMag[cInd] = tempMag;
        cInd++;
    }

    if(cInd > 0)
    {
        for (uint16_t i = 0; i < cInd; i++)
        {
            peakInds[i] = ind[peakLoc[i]];
            peakMags[i] = peakMag[i];
        }       
    }

    

    free(dbuf);
    free(idxBuf);
    free(x);
    free(dx);
    free(ind);
    free(peakLoc);
    free(peakMag);

    return cInd;
}

void diff(uint32_t *buf, uint16_t lbuf, int32_t *dbuf)
{
    dbuf[0] = 0;

    for (uint16_t i = 1; i < lbuf; i++)
    {
        dbuf[i] = buf[i] - buf[i-1];
    }

}

uint16_t signChg(int32_t *buf, uint16_t lbuf, uint16_t *idxBuf)
{
    uint16_t kk = 0;
    for (uint16_t i = 1; i < lbuf-1; i++)
    {
        
        if(buf[i]*buf[i+1]< 0)
        {
            idxBuf[kk++] = i;
        }
    }

    return kk;
}

void genData(uint32_t *buf, uint16_t lbuf, uint16_t *idxBuf, uint16_t lIdxBuf, uint32_t *x, uint16_t *ind)
{
    x[0] = buf[0];
    x[lIdxBuf + 1] = buf[lbuf - 1];

    ind[0] = 0;
    ind[lIdxBuf + 1] = lbuf - 1;

    for (uint16_t i = 0; i < lIdxBuf; i++)
    {
        x[i+1] = buf[idxBuf[i]];
        ind[i+1] = idxBuf[i];
    }
    
}

void arrmax(uint32_t *x, uint16_t l, uint32_t *val, uint16_t *ind)
{
    *val = x[0];
    
    for (uint16_t i = 1; i < l; i++)
    {
        if(x[i] >= *val)
        {
            *val = x[i];
            *ind = i;
        }
    }

}

uint32_t max(uint32_t *x, uint16_t l)
{
    uint32_t maxval = x[0];
    for (uint16_t i = 1; i < l; i++)
    {
        if(x[i] >= maxval)
        {
            maxval = x[i];
        }
    }

    return maxval;
    
}

void arrmin(uint32_t *x, uint16_t l, uint32_t *val, uint16_t *ind)
{
    *val = x[0];
    
    for (uint16_t i = 1; i < l; i++)
    {
        if(x[i] <= *val)
        {
            *val = x[i];
            *ind = i;
        }
    }
}

uint32_t min(uint32_t *x, uint16_t l)
{
    uint32_t minval = x[0];
    for (uint16_t i = 1; i < l; i++)
    {
        if(x[i] <= minval)
        {
            minval = x[i];
        }
    }

    return minval;
    
}