#include "tcp_net_socket.h"
void server_start(int argc, char* argv[])
{
       int sfd;
       int ret = 0;
       int fd[1000] = { 0 };
       int MaxFd, i = 0, j;
       fd_set ReadFd, tmpfd;
       char buf[64] = { 0 };
       struct timeval timeout = { 5, 0 };
       if (argc < 3)
       {
              printf("param error");
       }
       //tcp初始化
       sfd = tcp_init(argv[1], atoi(argv[2]));
       FD_ZERO(&ReadFd);
       FD_SET(sfd, &ReadFd);
       MaxFd = sfd;
       while (1)
       {
              tmpfd = ReadFd;
              ret = select(MaxFd + 1, &tmpfd, NULL, NULL, NULL);
              PERROR("select", (COMMON_ERROR == ret));
              //有连接请求
              if (FD_ISSET(sfd, &tmpfd))
              {
                      //选择可用的fd标记位
                      for (j = 0; j < i; j++)
                      {
                             if (0 == fd[j])
                             {
                                    break;
                             }
                      }
                      //接受连接
                      fd[j] = tcp_accept(sfd);
                      PERROR("tcp_accept", (COMMON_ERROR == ret));
                      //更新最大描述符，并新的文件描述符添加到集合
                      
                      if (MaxFd < fd[j])
                      {
                             MaxFd = fd[j];
                      }
                      FD_SET(fd[j], &ReadFd);
                      //setsockopt
                      ret = setsockopt(fd[j], SOL_SOCKET, SO_RCVTIMEO, (char*) &  timeout, sizeof(struct timeval));
                      PERROR("setsockopt", (COMMON_ERROR == ret));
                      if (j == i)
                      {
                             i++;
                      }
              }
              else
              {
                      for (j = 0; j < i; j++)
                      {
                             if (FD_ISSET(fd[j], &tmpfd))
                             {
                                    char msg[128] = "User ";
                                    int tmp = j;
                                    ret = recv(fd[j], buf, sizeof(buf), 0);
                                    PERROR("recv", (COMMON_ERROR == ret));
                                    //处理客户端意外中断
                                    if (0 == ret)
                                    {
                                           FD_CLR(fd[j], &tmpfd);
                                           i--;
                                    }
                                    //向其他客户端转发信息
                                    msg[5] = j + '0';
                                    msg[6] = ':';
                                    strcat(msg, buf);
                                    puts(msg);
                                    for (j = 0; j < i; j++)
                                    {
                                           if (tmp != j)
                                           {
                                                  ret = send(fd[j], msg, strlen(msg),  0);
                                                  PERROR("send", (COMMON_ERROR ==  ret));
                                           }
                                    }
                                    memset(buf, 0, sizeof(buf));
                                    memset(buf, 0, sizeof(msg));
                                    break;
                             }
                      }
              }
       }
       close(sfd);
}
int main(int argc, char* argv[])
{
       server_start(argc, argv);
       return 0;
}