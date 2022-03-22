#ifndef RECVFILE_H
#define RECVFILE_H
#include<QThread>
#include<QTcpSocket>
class RecvFile : public QThread//基类改成QThread包括
{
    Q_OBJECT
public:
    //explicit RecvFile(qintptr sock,QObject *parent = nullptr);
    explicit RecvFile(QTcpSocket*tcp,QObject *parent = nullptr);
    QTcpSocket*tcp;
    QTcpSocket*m_tcp;
protected:
    void run() override;//添加从父类继承过来的虚函数
signals:
     void over();
public slots:
};

#endif // RECVFILE_H
