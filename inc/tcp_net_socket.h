#ifndef __TCP_NET_SOCKET_H__
#define __TCP_NET_SOCKET_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#define COMMON_ERROR  -1
#define PERROR(err, ret) \
    do { \
           perror(err); \
        if (ret) { \
            exit(EXIT_FAILURE); \
        } \
    } while (0)
#define PERROR_C(err, ret, sfd) \
    do { \
        perror(err); \
        if (ret) { \
            close(sfd); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)
#define PERROR_CC(err, ret, sfd, cfd) \
    do { \
        perror(err); \
        if (ret) { \
            close(sfd); \
            close(cfd); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)
/*初始化操作：Socket创建，bind定位，listen建立*/
extern int tcp_init(const char* ip, int port);
/*用于服务端的接受，接受请求成功返回新的Socket new_fd*/
extern int tcp_accept(int sfd);
/*用于客户端的连接*/
extern int tcp_connect(const char* ip, int port);
#endif //__TCP_NET_SOCKET_H__