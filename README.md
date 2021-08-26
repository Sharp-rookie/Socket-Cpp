#### 网络通信 Socket

&emsp;Socket(套接字)可以看成是两个网络应用程序进行通信时，各自通信连接中的端点，这是一个逻辑上的概念。它是网络环境中进程间通信的API，使用中的每一个套接字都有其类型和一个与之相连进程。通信时其中一个网络应用程序将要传输的一段信息写入它所在主机的 Socket中，该 Socket通过与网卡(NIC)相连的传输介质将这段信息送到另外一台主机的 Socket中，使对方能够接收到这段信息。 Socket是由IP地址和端口结合的，提供向应用层进程传送数据包的机制。socket把复杂的TCP/IP协议封装了起来，只要用好socket相关的函数即可完成网络通信。

<img src="https://gitee.com/lrk612/md_picture/raw/master/img/20210826191343.png" alt="image-20210826190452059" width="30%" />

&nbsp;

#### Socket 类型

&emsp;&emsp;socket主要提供了流（stream）和数据报（datagram）两种通信机制，即流socket和数据报socket。

&emsp;&emsp;流socket基于TCP协议，是一个有序、可靠、双向字节流的通道，传输数据不会丢失、不会重复、顺序也不会错乱。

&emsp;&emsp;数据报socket基于UDP协议，不需要建立和维持连接，可能会丢失或错乱。UDP不是一个可靠的协议，对数据的长度有限制，但是它的速度比较高。

&nbsp;

#### 流Socket 工作流程

&emsp;&emsp;Socket在工作中分为客户端（Client）和服务端（Server）两部分：

<img src="https://gitee.com/lrk612/md_picture/raw/master/img/20210826191344.png" alt="image-20210826190900700" width="60%" />

&nbsp;

##### 服务端工作流程：

1. 创建socket
2. 把IP地址和端口绑定到socket上
3. 设置socket为监听模式
4. 接受客户端的连接请求
5. 与客户端重复通信，直到客户端断开连接
6. 关闭socket，释放资源

&nbsp;

##### 客户端工作流程：

1. 创建socket
2. 向服务端发起连接请求
3. 与服务端通信，数据发送完后断开连接
4. 关闭socket，释放资源

&nbsp;
