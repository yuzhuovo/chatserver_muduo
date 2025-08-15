#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>
#include "usermodel.hpp"
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
#include "redis.hpp"
using namespace std;
using namespace muduo;
using namespace muduo::net;

#include "json.hpp"
using json = nlohmann::json;

// 表示处理消息的事件回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;

class ChatService
{
public:
    // 获得单例对象的接口函数
    static ChatService *instance();
    // 登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp);
    // 注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp);
    // 处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);
    // 一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp);
    // 服务器异常业务重置方法
    void reset();
    // 添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp);

    // 创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 获得消息对应的处理器
    MsgHandler getHandler(int msgid);
    // 从redis消息队列中获取订阅的消息
    void handleRedisSubscribeMessage(int, string);

private:
    ChatService();

    // 存储消息id和其对应的业务处理方法
    unordered_map<int, MsgHandler> _msgHandlerMap;
    // 数据操作类对象
    UserModel _userModel;

    OfflineMsgModel _offlineMsgModel;
    //存储用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnMap;
    // 定义互斥锁
    mutex _connMutex;

    GroupModel _groupModel;
    
    FriendModel _friendModel;

    Redis _redis;
};

#endif