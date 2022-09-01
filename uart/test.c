#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cserial.h"

int main(int argc, char const *argv[])
{
	char *portname = "/dev/ttyUSB1";
	int fd = UARTOpen(portname);
	UARTInit(fd, 1000000, 0);
    char buf;
    unsigned char b[4];
    union {
      float F;
      unsigned char b[4];
    } u;
    int n;
    int i;
    for(i = 0; i < 1000000; i++){
      n = read(fd, &buf, 1);
      if(buf == 0x23) {
        n = read(fd, &b, 4);
        u.b[3] = b[0];
        u.b[2] = b[1];
        u.b[1] = b[2];
        u.b[0] = b[3];
        printf("%f\n", u.F);
      }
    }
 
  return 0;
}
