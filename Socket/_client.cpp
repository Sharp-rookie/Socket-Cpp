#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Using:./client ip port\nExample:./client 127.0.0.1 5005\n\n");
        return -1;
    }

    // 第1步：创建客户端的socket。
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // 第2步：向服务器发起连接请求。
    struct hostent *h;
    h = gethostbyname(argv[1]);

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2])); // 指定服务端的通信端口。
    memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) // 向服务端发起连接清求。
    {
        perror("connect");
        close(sockfd);
        return -1;
    }

    // 第3步：与服务端通信，发送一个报文后等待回复，然后再发下一个报文。
    char buffer[1024];
    //for (int ii = 0; ii < 3; ii++)
    while (1)
    {
        int iret;
        memset(buffer, 0, sizeof(buffer));
        printf("我：");
        scanf("%[^\n]", buffer);
        char c = getchar();
        //sprintf(buffer, "这是第%d个超级女生，编号%03d。", ii + 1, ii + 1);

        iret = send(sockfd, buffer, strlen(buffer), 0); // 向服务端发送请求报文。
        if (iret == 0)
            break;
        //printf("发送：%s\n", buffer);
        memset(buffer, 0, sizeof(buffer));

        iret = recv(sockfd, buffer, sizeof(buffer), 0); // 接收服务端的回应报文。
        //printf("接收：%s\n", buffer);
        if (strcmp(buffer, "bye") == 0)
            break;

        printf("对方：%s\n", buffer);
    }

    // 第4步：关闭socket，释放资源。
    close(sockfd);
}