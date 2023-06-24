#include "tcp_net_socket.h"
void* thread_recv_cb(void *data)
{
       int *tmpfd = (int*)data;
       int sfd = *tmpfd;
       char buf[512] = { 0 };
       fd_set ReadSet;
       FD_ZERO(&ReadSet);
       FD_SET(sfd, &ReadSet);
       while (1)
       {
              if (FD_ISSET(sfd, &ReadSet))
              {
                      recv(sfd, buf, sizeof(buf), 0);
                      puts(buf);
                      memset(buf, 0x00, sizeof(buf));
              }
       }
}
void client_start(int argc, char* argv[])
{
       int sfd;
       fd_set WriteSet;
       int ret = 0;
       char msg[32] = { "Hello I am client." };
       //int optval = 1;
       int optval_get;
       int optlen = sizeof(optval_get);
       pthread_t id1;
       int i = 0;
       if (argc < 3)
       {
              printf("param error");
       }
       //发送连接请求
       sfd = tcp_connect(argv[1], atoi(argv[2]));
       ret = pthread_create(&id1, NULL, thread_recv_cb, (void*) & sfd);
       //setsockopt
       //ret = setsockopt(sfd, SOL_SOCKET, SO_PRIORITY, &optval, sizeof(optval));
       //if (0 != ret)
       //{
       //     printf("setsockopt failed! ret:%s\n", strerror(errno));
       //}
       //getsockopt
       ret = getsockopt(sfd, SOL_SOCKET, SO_TYPE, &optval_get, &optlen);
       if (0 != ret)
       {
              printf("getsockopt failed! ret:%s\n", strerror(errno));
       }
       else
       {
              switch (optval_get)
              {
              case 1:
                      printf("IS TCP CONNECT\n");
                      break;
              case 2:
                      printf("IS UDP CONNECT\n");
                      break;
              }
       }
       FD_ZERO(&WriteSet);
       FD_SET(sfd, &WriteSet);
       while (1)
       {
              ret = select(sfd + 1, NULL, &WriteSet,  NULL, NULL);
              if (-1 == ret)
              {
                      perror("select");
              }
              if (FD_ISSET(sfd, &WriteSet))
              {
                      if (i > 0)
                      {
                             scanf("%s", msg);
                      }
                      if ("exit" == msg)
                      {
                             break;
                      }
                      ret = send(sfd, msg, strlen(msg), 0);
                      if (ret > 0)
                      {
                             //printf("send success\n");
                             i++;
                      }
                      else
                      {
                             printf("send failed:%d\n", ret);
                      }
              }
       }
       close(sfd);
}
int main(int argc, char* argv[])
{
       client_start(argc, argv);
       return 0;
}