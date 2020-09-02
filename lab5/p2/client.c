#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    int sfd;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        printf("Error in creating socket.\n");
        exit(0);
    }
    struct sockaddr_in clientAddr, serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8083);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(8087);
    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int sbind;
    sbind = bind(sfd, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
    if (sbind == -1)
    {
        printf("Error in client binding.\n");
        exit(0);
    }
    printf("Client bind successful.\n");

    if (connect(sfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        printf("Error in connecting.\n");
        exit(0);
    }

    int len = sizeof(clientAddr);

    char message[]="welcome kiit";
    send(sfd, message, strlen(message), 0);

    int buffer;
    int recvLen = recv(sfd, &buffer, sizeof(int), 0);

    
    printf("%d\n", buffer);

    return 0;
}
