#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent) : QTcpServer(parent)
{

}
//客户端发送新连接这个函数就被自动调用了
void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    emit newDescriptor(socketDescriptor);
}
