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
    if (fork() > 0)
        return 0;

    if (argc != 2)
    {
        printf("Using:./server port\nExample:./server 5005\n\n");
        return -1;
    }

    // 第1步：创建服务端的socket。
    int listenfd;                               //文件描述符，0-标准输入、1-标准输出、2-标准错误
    listenfd = socket(AF_INET, SOCK_STREAM, 0); //socket返回的是一个文件描述符，函数参数固定，表示使用IPv4地址簇、TCP协议

    // 第2步：把服务端用于通信的地址和端口绑定到socket上。
    struct sockaddr_in servaddr; // 服务端地址信息的数据结构。
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;                // 协议族，在socket编程中只能是AF_INET。
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 任意ip地址。
    servaddr.sin_port = htons(atoi(argv[1]));     // 指定通信端口。
    //servaddr.sin_addr.s_addr = inet_addr("192.168.190.134"); // 指定ip地址。
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // 第3步：把socket设置为监听模式。
    listen(listenfd, 5);

    // 第4步：接受客户端的连接。
    int clientfd;                             // 用于向客户端发送报文的socket。
    int socklen = sizeof(struct sockaddr_in); // struct sockaddr_in的大小
    struct sockaddr_in clientaddr;            // 客户端的地址信息。
    clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, (socklen_t *)&socklen);
    printf("客户端（%s）已连接。\n\n", inet_ntoa(clientaddr.sin_addr));

    // 第5步：与客户端通信，接收客户端发过来的报文后，回复ok。
    char buffer[1024];
    while (1)
    {
        int iret;
        memset(buffer, 0, sizeof(buffer));
        iret = recv(clientfd, buffer, sizeof(buffer), 0); // 接收客户端的请求报文。
        if (iret == 0 || strcmp(buffer, "bye") == 0)
        {
            printf("对方：%s\n", buffer);
            sleep(1);
            send(clientfd, buffer, strlen(buffer), 0);
            printf("我：bye\n对方已断开连接\n");
            //printf("\nbye\n");
            break;
        }
        printf("对方：%s\n", buffer);
        //printf("接收：%s\n", buffer);

        //strcpy(buffer, "ok");
        printf("我：");
        memset(buffer, 0, sizeof(buffer));
        scanf("%[^\n]", buffer);
        char c = getchar();
        send(clientfd, buffer, strlen(buffer), 0); // 向客户端发送响应结果。
        //printf("发送：%s\n", buffer);
    }

    // 第6步：关闭socket，释放资源。
    close(listenfd);
    close(clientfd);
}