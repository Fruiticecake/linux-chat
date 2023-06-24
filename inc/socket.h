#ifndef __SOCKET_H__
#define __SOCKET_H__
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
typedef struct
{
       char* h_name;         /*正式主机名*/
       char** h_aliases;     /*主机别名*/
       int h_addrtype;              /*主机地址类型*/
       int h_length;         /*主机地址字节长度*/
       char** h_addr_list;   /*主机的IP地址列表*/
}socket_hostent;
#define h_addr h_addr_list[0];
#endif // !__SOCKET_H__
