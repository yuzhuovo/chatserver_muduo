# chatserver_muduo
基于muduo库的集群聊天服务器

1. 实现了基于多Reactor模型和线程池的TCP连接和任务分发接口，支持高并发通信;
2. 用json协议作为客户端与服务器的通信协议;
3. 配置Nginx的负载均衡实现服务器集群;
4. 基于Redis的发布-订阅功能实现跨服务器消息通信;
5. 使用Mysql数据库存储数据。

编译方法

第一种方法：

在build目录下

1. rm -rf *
2. cmake..
3. make

第二种方法：

在chatserver_muduo目录下

./autobuild.sh

生成可执行文件在bin目录下

客户端

./ChatClient

服务端

./ChatServer
