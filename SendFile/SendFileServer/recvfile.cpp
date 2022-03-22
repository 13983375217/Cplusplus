#include "recvfile.h"
#include<QThread>
#include<QFile>
//RecvFile::RecvFile(qintptr sock,QObject *parent) : QThread(parent)//创建一个子线程继承Object类手动改基类为QThread
RecvFile::RecvFile(QTcpSocket*tcp,QObject *parent) : QThread(parent)
{
    //吧传递进来的地址保存下来
    m_tcp=tcp;

   // m_tcp=new QTcpSocket;
    //m_tcp->setSocketDescriptor(sock);
}

void RecvFile::run()
{
    qDebug()<<"服务器子线程"<<QThread::currentThread();
    QFile *file=new QFile("recv.txt");//创建一个QFile对象
    file->open(QFile::WriteOnly);

    //接受数据
    connect(m_tcp,&QTcpSocket::readyRead,this,[=]{
        //现在我们就可以使用用于通信的套接字对象了
            static int count=0;
            static int total=0;
           if (count==0)
           {
                m_tcp->read((char*)total,4);//读四个字节吧文件大小读出来
            }
           //读出剩余的数据

          QByteArray data= m_tcp->readAll();
          count+=data.size();
          file->write(data);//写入磁盘文件

          if(count==total){
              m_tcp->close();
              m_tcp->deleteLater();
              file->close();
              file->deleteLater();
              emit over();
          }

          qDebug()<<data;



    });

    exec();
    //进入时间循环 线程进入后台 只要有事件触发那么就会处理

}
