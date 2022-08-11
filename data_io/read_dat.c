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

int main()
{
    uint8_t *buf = readData("1.dat");
    
    for (uint32_t i = 0; i < 100; i+=2)
    {
        printf("%2X %2X\n", buf[i], buf[i+1]);
    }
    
    
}
