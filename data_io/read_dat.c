#include <stdlib.h>
#include <stdio.h>
#include <string.h>

uint8_t *readData(const char *f)
{
    FILE* stream = fopen(f, "r");

    if(stream == NULL)
    {
        printf("Open failed.\n");
        return NULL;
    }

    /* Get the file size in bytes */

    fseek(stream, 0L, SEEK_END);
    uint32_t sz = ftell(stream);
    fseek(stream, 0L, SEEK_SET);

    printf("File size %lu Bytes.\n", sz);

    /* Read dat file into buffer */

    uint8_t *buf = (uint8_t *)malloc(sz * sizeof(uint8_t));

    for (uint32_t i = 0; i < sz; i++)
    {
        fread(buf+i, sizeof(char), sizeof(char), stream);
    }
    
    return buf;
    free(buf);
}

uint16_t *readData16(const char *f)
{
    FILE* stream = fopen(f, "r");

    if(stream == NULL)
    {
        printf("Open failed.\n");
        return NULL;
    }

    /* Get the file size in bytes */

    fseek(stream, 0L, SEEK_END);
    uint32_t sz = ftell(stream);
    fseek(stream, 0L, SEEK_SET);

    printf("File size %lu 16-bits.\n", sz >> 1);

    /* Read dat file into buffer */

    uint16_t *buf = (uint16_t *)malloc((sz >> 1) * sizeof(uint16_t)); // sz >> 1 to conver to 16-bit size

    /* Read in 16-bit */
    
    int n = 1;

    for (uint32_t i = 0; i < (sz >> 1); i++)
    {
        fread(buf+i, sizeof(uint16_t), 1, stream);
        
        // little endian if true
        if(*(char *)&n == 1)
            buf[i] = ((buf[i] & 0x00FF) << 8) | (buf[i] >> 8);
    }
    
    return buf;
    free(buf);
}

int main()
{
    uint16_t *buf = readData16("1.dat");

    /* Print in 8-bit */    
    // for (uint32_t i = 0; i < 100; i+=2)
    // {
    //     printf("%02X%02X\n", buf[i], buf[i+1]);
    // }

    /* Print in 16-bit */    
    for (uint32_t i = 0; i < 100; i++)
    {
        printf("%04X\n", buf[i]);
    }
    
    
}
