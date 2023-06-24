#include "tcp_net_socket.h"
#include "utils.h"
#define PORT 8888
/*初始化操作：Socket创建，bind定位，listen建立*/
int tcp_init(const char* ip, int port)
{
       int ret = 0;
       int sfd;
       //设置地址族IPV4、IPV6和端口号。0则自动分配。
       
       struct sockaddr_in serveraddr;
       memset(&serveraddr, 0, sizeof(struct sockaddr));
       serveraddr.sin_family = AF_INET;
       serveraddr.sin_port = htons(port);
       serveraddr.sin_addr.s_addr = inet_addr(ip);
       //创建一个Socket
       
       sfd = socket(AF_INET, SOCK_STREAM, 0);
       PERROR("socket", (COMMON_ERROR == sfd));
       //绑定该Socket
       
       ret = bind(sfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr));
       PERROR_C("bind", (COMMON_ERROR == ret), sfd);
       //监听该Socket
       ret = listen(sfd, 10);
       PERROR_C("listen", (COMMON_ERROR == ret), sfd);
       return sfd;
}
/*用于服务端的接受，接受请求成功返回新的Socket new_fd*/
int tcp_accept(int sfd)
{
       int addrlen;
       int new_fd;
       struct  sockaddr_in clientaddr;
       memset(&clientaddr, 0, sizeof(struct sockaddr));
       addrlen = sizeof(struct sockaddr);
       //接受连接成功则创建新的Socket为new_fd
       new_fd = accept(sfd, (struct sockaddr*)&clientaddr, &addrlen);
       PERROR_C("accept", (COMMON_ERROR == new_fd), sfd);
       printf("%s success connect! \n", inet_ntoa(clientaddr.sin_addr));
       return new_fd;
}
/*用于客户端的连接*/
int tcp_connect(const char* ip, int port)
{
       int sfd;
       int ret = 0;
       struct sockaddr_in serveraddr;
       sfd = socket(AF_INET, SOCK_STREAM, 0);
       PERROR("socket", (COMMON_ERROR == sfd));
       memset(&serveraddr, 0, sizeof(struct sockaddr));
       serveraddr.sin_family = AF_INET;
       serveraddr.sin_port = htons(port);
       serveraddr.sin_addr.s_addr = inet_addr(ip);
       ret = connect(sfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr));
       PERROR_C("connect", (COMMON_ERROR == ret), sfd);
       return sfd;
}