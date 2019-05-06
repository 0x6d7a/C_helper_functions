// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define PORT 7800
#define SIZE 256

int main(int argc, char const *argv[])
{
    /* Parameter Initialization */
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *ip = "192.168.0.28";
    char *hello = "Hello from client";
    char pcm[3] = {0x01, 0x02, 0xFF};
    char buffer[1024] = {0};

    /* Connection generation */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\nError: Socket creation failed.");
        return -1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0)
    {
        printf("\nError: Invalid address/ Address not supported.");
        return -1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nError: Connection Failed.");
        return -1;
    }

    /* Open cdev*/
    int i, value;
    int fid = open("/dev/maxus0", O_RDWR);
    if(fid <0)
        printf("\nError: Maxus device open failure.");
    else
    {
        value = read(fid, buff, SIZE);
        printf("\nInfo: %d numbers read from max device.", value);
        for(i=0; i < value; i++)
            printf("%d\n", buff[i]);
    }
    sleep(5);
    send(sock , buff , value * sizeof(char) , 0);
    close(fid);
    return 0;
}
