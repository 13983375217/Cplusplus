#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QThread>
#include"filesend.h"
#include<QMessageBox>
#include<QFileDialog>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug()<<"客户端主线程"<<QThread::currentThread();

    ui->port->setText("8989");
    ui->ip->setText("10.0.50.58");
    ui->progressBar->setRange(0,100);//设置进度条
    ui->progressBar->setValue(0);//设置进度条初始值
    //setWindowTitle("雷达模拟器");

    QThread* t=new QThread;//创建一个线程对象
    //创建任务对象
    FileSend * worker=new FileSend;//创建一个新的FileSend类对象来将他移动到worker
    worker->moveToThread(t);//吧工作的类对象移动到子线程里面去 这样任务函数在执行的时候就能在子线程里面执行了

    connect(this,&MainWindow::connectStart,worker,&FileSend::connectServer);//connectStart传递ip和port到connectServer

    connect(this,&MainWindow::sendfildpath,worker,&FileSend::sendFile);//把信号发送到sendFile函数 传递路径

    connect(worker,&FileSend::connectOK,this,[=](){
       QMessageBox::information(this,"服务器","连接成功....");
    });

    connect(worker,&FileSend::connectClose,this,[=](){
        t->quit();
        t->wait();
        worker->deleteLater();
        t->deleteLater();

    });

    t->start();//线程启动了不代表线程里面的函数执行了需要手动调用让工作的函数开始执行

    connect(worker,&FileSend::curPercent,ui->progressBar,&QProgressBar::setValue);//吧发送过来百分比发送到QProgressBar

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connetServer_clicked()
{

QString ip=ui->ip->text();
unsigned short port=ui->port->text().toUShort();
emit connectStart(port,ip);

}

void MainWindow::on_selFile_clicked()
{
    QString path=QFileDialog::getOpenFileName();//QFileDialog调用他的静态方法就可以得到磁盘文件的绝对路径
    if(path.isEmpty()){
         QMessageBox::information(this,"选择的","文件不能为空....");
        return;
    }
    ui->FilePath->setText(path);//把得到的路径设置到文本框里
}

void MainWindow::on_sendFileBtn_clicked()
{
   emit sendfildpath(ui->FilePath->text());//发送这个信号把拿到的路径发送到子线程worker里面需要一个槽函数连接
}
