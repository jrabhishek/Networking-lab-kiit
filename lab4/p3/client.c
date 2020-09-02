#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    int cfd;

    cfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (cfd == -1)
    {
        printf("Client Socket Not Created.\n");
        exit(0);
    }
    else
    {
        printf("Client Socket Created Succefully.\n");

        struct sockaddr_in serveraddr, clientaddr;

        clientaddr.sin_family = AF_INET;
        clientaddr.sin_port = htons(8080);
        clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port = htons(5535);
        serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        int len = sizeof(serveraddr);

        int sbind;

        sbind = bind(cfd, (struct sockaddr *)&clientaddr, sizeof(clientaddr));

        if (sbind == -1)
        {
            printf("Client Bind Error.\n");
            exit(0);
        }
        else
        {
            printf("Client Binding Succesfully.\n");
            printf("Enter the size of array ");
            int n,i;
            scanf("%d",&n);
            printf("enter the elements in array");
            int a[n],buffer[100];
            for(i=0;i<n;i++)
                scanf("%d",&a[i]);
            sendto(cfd, (int *)a, sizeof(a), 0, (struct sockaddr *)&serveraddr, len);

    
                
            close(cfd);
        }
    }

    return 0;
}
