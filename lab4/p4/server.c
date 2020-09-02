#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <string.h>
#include<limits.h>

int main()
{
    int sfd;

    int buffer[100];

    sfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sfd == -1)
    {
        printf("Server Socket Not Created.\n");
        exit(0);
    }
    else
    {
        printf("Server Socket Created Succefully.\n");

        struct sockaddr_in serveraddr, clientaddr;

        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port = htons(5535);
        serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        int sbind;

        sbind = bind(sfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
        if (sbind == -1)
        {
            printf("Server Bind Error.\n");
            exit(0);
        }
        else
        {
           // printf("Server Binding Succesfully.\n");
            int len = sizeof(clientaddr);
            int r = recvfrom(sfd, (int *)buffer, 100, 0, (struct sockaddr *)&clientaddr, &len);
            int i,max;
            r=r/sizeof(int);
            max=INT_MIN;
            
            for(i=0;i<r;i++)
                if(buffer[i]>max)
                    max=buffer[i];
            len = sizeof(serveraddr);
            sendto(sfd, &max, sizeof(max), 0, (struct sockaddr *)&clientaddr, len);

            close(sfd);
        }
    }

    return 0;
}
