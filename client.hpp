#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int sock = 0, valread_client;
struct sockaddr_in serv_addr;

int start_client(char *ip)
{
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    return 0;
}

void to_server(const char *message)
{
    send(sock, message, strlen(message), 0);
}

char buffer_client[1024] = {0};

char *from_server()
{
    for (int i = 0; i < 1024; i++)
    {
        buffer_client[i] = 0;
    }
    valread_client = read(sock, buffer_client, 1024);
    return buffer_client;
}
