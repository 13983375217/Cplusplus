#include "filesend.h"
#include<QFile>
#include<QFileInfo>
FileSend::FileSend(QObject *parent) : QObject(parent)
{

}

void FileSend::connectServer(unsigned short port, QString ip)
{
    tcpsocket=new QTcpSocket;
    tcpsocket->connectToHost(QHostAddress(ip),port);//connectToHost并不是一个阻塞函数并不能通过它来判断服务器是否连接成功了
    connect(tcpsocket,&QTcpSocket::connected,this,&FileSend::connectOK);//判断是否连接成功
    connect(tcpsocket,&QTcpSocket::disconnected,this,[=](){//如果断开连接就关闭套接字并且释放内存对象
        tcpsocket->close();
        tcpsocket->deleteLater();
        emit connectClose();
    });
}

void FileSend::sendFile(QString path)
{
QFile file(path);
QFileInfo info(path);
int fileSize=info.size();
file.open(QFile::ReadOnly);
while (!file.atEnd()) {
    static int num=0;
    if(num==0){//第一次发送文件大小
        tcpsocket->write((char*)&fileSize,4);//fileSize转换成字符串类型然后给他指定一个大小
    }
    QByteArray line=file.readLine();//按行读取
    num+=line.size();//
    int percent=(num*100/fileSize);
    emit curPercent(percent);

    tcpsocket->write(line);
}

}
