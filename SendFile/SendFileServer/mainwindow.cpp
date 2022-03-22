#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QThread>
#include<QTcpSocket>
#include<QTcpServer>
#include"filesend.h"
#include<QMessageBox>
#include<QFileDialog>
#include"recvfile.h"//添加子线程头文件
#include<QThread>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug()<<"服务器主线程"<<QThread::currentThread();

   m_tcp=new QTcpServer(this);//监听套接字
   // m_tcp=new MyTcpServer(this);
    //connect(m_tcp,&MyTcpServer::newDescriptor,this,[=](qintptr sock){
    connect(m_tcp,&QTcpServer::newConnection,this,[=]{
       QTcpSocket* tcp= m_tcp->nextPendingConnection();//通信套接字tcp
        //QT版本不一样可能会导致tcp这个用于通信的套接字对象输出错误日志

        //要和子线程通信就要吧和子线程通信的这个套接字传递到子线程中
        //有两种方式一种是通过信号槽的方式一种是通过转递参数的方式
        //创建子线程
        RecvFile *recv=new RecvFile(tcp);
       // RecvFile *recv=new RecvFile(sock);//以参数的形式吧tcp传给recv对象
        recv->start();



        connect(recv,&RecvFile::over,this,[=]{
            recv->exit();
            recv->wait();
            recv->deleteLater();
            QMessageBox::information(this,"文件接收","文件接收完毕");
        });
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setListen_clicked()
{
//  QString ip=ui->ip->text();
    unsigned short port=ui->port->text().toUShort();
    m_tcp->listen(QHostAddress::Any,port);
}
