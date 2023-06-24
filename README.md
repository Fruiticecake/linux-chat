# linux-chat
use linux socket to create a chat room

# 环境
Linux环境

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