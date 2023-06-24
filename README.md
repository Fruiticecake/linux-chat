# linux-chat
use linux socket to create a chat room

# 环境
Linux环境

# 架构

### socket封装
> 为了便于使用在tcp_net_socket.c中封装了tcp_init、tcp_accept、tcp_connect函数，
- tcp_init包含服务端的socket创建，bind绑定以及listen监听。
- tcp_connect 用于客户端发送连接请求
- tcp_accept 用于服务端接受连接请求

### 客户端
客户端中加了一个线程用于接受服务端传来的消息。---- 避免发送消息时阻塞

### 服务端
采用select监听服务端的描述符用于实现循环高性能服务。
监听到连接请求会接受连接。
连接成功后会分配相应的空间保存描述符。
监听到其他描述符有可读信息，进行接受并转发给其他客户端。

# 使用

### 服务端编译:
`gcc -o tcp_net_server -I ./inc/ ./src/tcp_net_server.c ./src/tcp_net_socket.c`
### 客户端编译
`gcc -o tcp_net_client -I ./inc/ ./src/tcp_net_client.c ./src/tcp_net_socket.c`
### 运行服务端
`./tcp_net_server ip地址 端口号`
### 运行客户端 可运行多个

`./tcp_net_client ip地址 端口号`  这里的ip地址和端口号与服务端相同

# 效果

### 客户端
![图片加载失败](https://github.com/Fruiticecake/images/blob/main/linux-chat/client.png?raw=true)

每个客户端会有属于自己的ID，其他客户端发送消息时会收到消息。

### 服务端
![图片加载失败](https://github.com/Fruiticecake/images/blob/main/linux-chat/server.png?raw=true)

服务端会显示所有客户端发送的消息，并进行一个转发。