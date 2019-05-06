// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define PORT 7900
#define SIZE 256

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";

    float a = 9.81f;
    float b = 10.11;
    float c = 10.12;
    float d = 10.13;
    float e = 10.14;
    float f = 10.15;
    float g = 10.16;

    // char pcm[sizeof(float)];
    // int len = snprintf(pcm, 256, "%f,%f,%f,%f,%f,%f,%f", a, b,c,d,e,f,g);
    // printf("%d len\n", len);
    // memcpy(pcm, &a, sizeof(float));
    unsigned char const * const pcm = (unsigned char const *)&f;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "0.0.0.0", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    sleep(5);
    // send(sock , hello , strlen(hello) , 0 );
    printf("%x\n", pcm);
    int vallen = send(sock , pcm , sizeof(float) , 0 );
    printf("Hello message sent with %d length\n", vallen);
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}
