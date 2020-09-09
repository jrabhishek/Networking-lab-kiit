#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<limits.h>

int main()
{
    int sfd;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        printf("Error in creating socket.\n");
        exit(0);
    }
    struct sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8083);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int sbind;
    sbind = bind(sfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (sbind == -1)
    {
        printf("Error in server binding.\n");
        exit(0);
    }
    printf("Server bind successful.\n");

    if (listen(sfd, 5))
    {
        printf("Listen limit reached.\n");
        exit(0);
    }

    int buffer[100];
    struct sockaddr_in clientAddr;
    int len = sizeof(clientAddr);

    int nfd = accept(sfd, (struct sockaddr *)&clientAddr, &len);
    if (nfd == -1)
    {
        printf("Error in accepting.\n");
        exit(0);
    }

    int recvLen = recv(nfd, buffer, 100, 0);
    
    int l = recvLen/sizeof(int);
    int i=0,sum=0;

    printf("elements are:\n");
    for (i = 0; i < l; i++)
    {
        printf("%d\n",buffer[i]);
        sum +=buffer[i];
            
     }
    send(nfd, &sum, sizeof(sum), 0);
    close(nfd);


   
    return 0;
}
