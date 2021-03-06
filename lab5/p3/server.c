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

    char buffer[100];
    struct sockaddr_in clientAddr;
    int len = sizeof(clientAddr);

    int nfd = accept(sfd, (struct sockaddr *)&clientAddr, &len);
    if (nfd == -1)
    {
        printf("Error in accepting.\n");
        exit(0);
    }

    int recvLen = recv(nfd, buffer, 100, 0);

    buffer[recvLen] = '\0';
    printf("%s\n", buffer);
    int i,ispall=0;
    char message[100] = "String is  pallindrome";
    for(i=0;i<recvLen/2;i++){
        if(buffer[i]!=buffer[recvLen-1-i])
        {
            ispall =1;
            break;
        }
    }

    
    if(ispall==1)
      strcpy(message,"string is not pallindrome");
    
    send(nfd, message, strlen(message), 0);
    return 0;
}
