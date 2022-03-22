#ifndef FILESEND_H
#define FILESEND_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class FileSend : public QObject//直接创建一个class基类选择object
{
    Q_OBJECT
public:
    explicit FileSend(QObject *parent = nullptr);

    //连接服务器
    void connectServer(unsigned short port,QString ip);

    //发送文件
    void sendFile(QString filePath);
private:
    QTcpServer* tcpserver;
    QTcpSocket* tcpsocket;
signals:
    void connectOK();
    void connectClose();
    void curPercent(int percent);

public slots:
};

#endif // FILESEND_H
