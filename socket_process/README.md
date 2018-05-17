## 基于TCP的套接字编程框架

功能说明：  
server端进行监听，client端进行连接，连接成功后进行数据发送，发送的数据从标准输入获取，服务端收到数据后，将收到的数据回写给客户端。

- `server`
  - 实现了server端的代码
- `client`
  - 实现了client端的代码
 

代码编译执行
```
cd server
make
./server
//重新打开一个终端
cd client
make
./client
//进行数据传输，屏幕打印效果如下：
[root@Server:client]# ./client 
hello
hello
hello world
hello world

```