#include "filesend.h"
#include<QFile>
#include<QFileInfo>//可以直接得到文件大小
FileSend::FileSend(QObject *parent) : QObject(parent)
{

}

void FileSend::connectServer(unsigned short port, QString ip)
{
    m_tcp=new QTcpSocket;
    m_tcp->connectToHost(QHostAddress(ip),port);//connectToHost并不是一个阻塞函数并不能通过它来判断服务器是否连接成功了
    connect(m_tcp,&QTcpSocket::connected,this,&FileSend::connectOK);//判断是否连接成功
    connect(m_tcp,&QTcpSocket::disconnected,this,[=](){//如果断开连接就关闭套接字并且释放内存对象
        m_tcp->close();
        m_tcp->deleteLater();
        emit connectClose();
    });
}

void FileSend::sendFile(QString path)
{

QFile                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        file(path);
file.open(QFile::ReadOnly);

QFileInfo info(path);
int fileSize=info.size();//fileSize就是这个文件的总字节数

while (!file.atEnd()) {
    static int num=0;
    if(num==0){//第一次发送文件大小 先把文件的大小发送给服务器
        m_tcp->write((char*)&fileSize,4);//fileSize转换成字符串类型然后给他指定一个大小
    }
    QByteArray line=file.readLine();//按行读取
    num+=line.size();
    int percent=(num*100/fileSize);
    m_tcp->write(line);
    emit curPercent(percent);
}

}
