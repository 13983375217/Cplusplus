#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QByteArray>
#include<QString>
#include <QUdpSocket>
#include <QtMath>
#include <QDebug>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


   ui->setupUi(this);

   ui->ip->setText("181.81.81.70");
   //ui->ip_2->setText("181.81.81.80");
   ui->ip_2->setText("10.0.50.58");
   ui->RecPort->setText("1553");
   ui->port->setText("24576");

   ui->RecPort_2->setText("1552");
   ui->port_2->setText("24577");

   ip=ui->ip->text();
   ip1=ui->ip_2->text();

   ui->DAC2->setText("0.5");
   ui->DAC3->setText("0.5");

   ui->DAC2_2->setText("0.5");
   ui->DAC3_2->setText("0.5");

   ui->XSpinBox->setSingleStep(0.01);
   ui->YSpinBox_2->setSingleStep(0.0001);
   ui->XSpinBox->setRange(0,360);
   ui->YSpinBox_2->setRange(0,1);
   ui->XSpinBox->setDecimals(2);
   ui->YSpinBox_2->setDecimals(4);

   ui->XSpinBox_2->setSingleStep(0.01);
   ui->YSpinBox_3->setSingleStep(0.0001);
   ui->XSpinBox_2->setRange(0,360);
   ui->YSpinBox_3->setRange(0,1);
   ui->XSpinBox_2->setDecimals(2);
   ui->YSpinBox_3->setDecimals(4);


   setWindowTitle("计算测试");
   udpsocket=new QUdpSocket(this);//创建一个udpsocket来发送数据
   udpsocket1=new QUdpSocket(this);
   m_UDPReceiver = new QUdpSocket(this);//m_UDPReceiver创建一个套接字来接受数据
   m_UDPReceiver1 = new QUdpSocket(this);//m_UDPReceiver创建一个套接字来接受数据
   connect(this,&MainWindow::sendMsg,this,&MainWindow::sendInfomation);
   connect(this,&MainWindow::sendMsg1,this,&MainWindow::sendInfomation1);


}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::on_sendBtn_clicked()
//{
//   // udpsocket->close();
//   unsigned short port=ui->port->text().toUShort();
//   QString ip=ui->ip->text();
//    qDebug()<<ip;
//   // udpsocket->bind(port,QUdpSocket::ShareAddress);//发送数据这个一开始就绑定24576端口
//    udpsocket->writeDatagram(dataQbyte,dataQbyte.size(),QHostAddress(ip),port);
//     // udpsocket->writeDatagram(dataQbyte,QHostAddress("181.81.81.80"),24576);
//      ui->sendData->append(dataQbyte.toHex().toUpper());
//      // ui->sendData->append(dataQbyte);
//      //dataQbyte.clear();清除数据之后只能单击发送

//}
//void MainWindow::sendInfomation(QString str,QString str1){
void MainWindow::sendInfomation(int Mx,int Mq){

    QByteArray datagram ;
    QString pad_value=qRound((ui->setsub->text()).toDouble()*2);
//    double pad_value_2=pad_value.toDouble()*2;
//    int pad_value_3=qRound(pad_value_2);

    datagram[0] = 0xD1;//16进制编码存入char 一个char占一个字节 一个字节存储8位无符号数，储存的数值范围为0-255。
    datagram[1] = 0xA2;

    datagram[2] = 0xFF;
    datagram[3] = 0x20;

    datagram[4] = 0x62;
    datagram[5] = 0x4A;
    datagram[6] = 0x00;
    datagram[7] = pad_value.toInt()&0xFF;//衰减值 与0xFF就是它本身但是会转换成16进制 左右两边要求同为int

    datagram[8] = 0xDA;
    datagram[9] = 0xC1;

    datagram[10]= 0x00;
    datagram[11]= 0x00;
    datagram[12]= (Mx>>8)&0xFF;//右移操作符右移八位吧Mx的值的二进制 低地址8位移过去比如 1111 1110 1111 1101 右移八位变成
                               //0000 000 1111 1110左移同理 因为datagram[i]一个为char[] 占一个字节超过255的数就存放不下来
                               //需要吧高低地址用移位操作分成两半分别存放 再按要求看是低地址在前还是高地址在前
    datagram[13]= Mx&0xFF;

    datagram[14]= 0xDA;
    datagram[15]= 0xC2;
    datagram[16]= 0x00;
    datagram[17]= 0x00;
    datagram[18]= 0x33;
    datagram[19]= 0x33;

    datagram[20]= 0xDA;
    datagram[21]= 0xC3;
    datagram[22]= 0x00;
    datagram[23]= 0x00;
    datagram[24]= 0x33;
    datagram[25]= 0x33;

    datagram[26]= 0xDA;
    datagram[27]= 0xC4;
    datagram[28]= 0x00;
    datagram[29]= 0x00;
    datagram[30]= (Mq>>8)&0xFF;
    datagram[31]= Mq&0xFF;
    dataQbyte=datagram;
   // qDebug()<<datagram;
    unsigned short port=ui->port->text().toUShort();
    udpsocket->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    udpsocket->writeDatagram(dataQbyte,dataQbyte.size(),QHostAddress(ip),port);
    ui->sendData->append(dataQbyte.toHex().toUpper());
   // qDebug()<<ip;
}
void MainWindow::sendInfomation1(int Mx,int Mq){

    QByteArray datagram1 ;
    QString pad_value=(ui->setsub_2->text());
    double pad_value_2=pad_value.toDouble()*2;//衰减值*2
    int pad_value_3=qRound(pad_value_2);
    datagram1[0] = 0xD1;//16进制编码存入char 一个char占一个字节 一个字节存储8位无符号数，储存的数值范围为0-255。
    datagram1[1] = 0xA2;

    datagram1[2] = 0xFF;
    datagram1[3] = 0x20;

    datagram1[4] = 0x62;
    datagram1[5] = 0x4A;
    datagram1[6] = 0x00;
    datagram1[7] = pad_value_3&0xFF;//衰减值 与0xFF就是它本身但是会转换成16进制 左右两边要求同为int

    datagram1[8] = 0xDA;
    datagram1[9] = 0xC1;

    datagram1[10]= 0x00;
    datagram1[11]= 0x00;
    datagram1[12]= (Mx>>8)&0xFF;//右移操作符右移八位吧Mx的值的二进制 低地址8位移过去比如 1111 1110 1111 1101 右移八位变成
                               //0000 000 1111 1110左移同理 因为datagram[i]一个为char[] 占一个字节超过255的数就存放不下来
                               //需要吧高低地址用移位操作分成两半分别存放 再按要求看是低地址在前还是高地址在前
    datagram1[13]= Mx&0xFF;

    datagram1[14]= 0xDA;
    datagram1[15]= 0xC2;
    datagram1[16]= 0x00;
    datagram1[17]= 0x00;
    datagram1[18]= 0x33;
    datagram1[19]= 0x33;

    datagram1[20]= 0xDA;
    datagram1[21]= 0xC3;
    datagram1[22]= 0x00;
    datagram1[23]= 0x00;
    datagram1[24]= 0x33;
    datagram1[25]= 0x33;

    datagram1[26]= 0xDA;
    datagram1[27]= 0xC4;
    datagram1[28]= 0x00;
    datagram1[29]= 0x00;
    datagram1[30]= (Mq>>8)&0xFF;
    datagram1[31]= Mq&0xFF;
    dataQbyte1=datagram1;
    //qDebug()<<datagram;
    unsigned short port=ui->port_2->text().toUShort();
    udpsocket1->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    udpsocket1->writeDatagram(dataQbyte1,dataQbyte1.size(),QHostAddress(ip1),port);
    ui->sendData_2->append(dataQbyte1.toHex().toUpper());
    //qDebug()<<ip;
}

void MainWindow::processPendingDatagram()
{

    while(m_UDPReceiver->hasPendingDatagrams())  //拥有等待的数据报
       {
          QByteArray datagram; //拥于存放接收的数据报

          //让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
          datagram.resize(m_UDPReceiver->pendingDatagramSize());

          //接收数据报，将其存放到datagram中
          m_UDPReceiver->readDatagram(datagram.data(),datagram.size());

          char* b=datagram.data();
          QString str,DAC1,DAC2,DAC3,DAC4;
//          qDebug()<<"char* b"<<b;
//          qDebug()<<"char* b[21]"<<b[21];
//          qDebug()<<"char* b[22]"<<b[22];

          //衰减值
          str.append(b[21]);
          str.append(b[22]);

          //DAC1
          DAC1.append(b[36]);
          DAC1.append(b[37]);
          DAC1.append(b[39]);
          DAC1.append(b[40]);

          //DAC2
          DAC2.append(b[54]);
          DAC2.append(b[55]);
          DAC2.append(b[57]);
          DAC2.append(b[58]);

          //DAC4
          DAC4.append(b[90]);
          DAC4.append(b[91]);
          DAC4.append(b[93]);
          DAC4.append(b[94]);
          bool ok;
          double tmp = str.toInt(&ok,16);
          double tmp1 = DAC1.toInt(&ok,16);
          double yi=((tmp1/65535)*2.5)-0.5;
          double tmp2 = DAC4.toInt(&ok,16);
          double  yq=((tmp2/65535)*2.5)-0.5;
          double y=sqrt(yi*yi+yq*yq);

          double x=(acos(yq/y)/M_PI)*180;//acos返回值在-pi/2到pi/2;
          if(0<(yi/y)&&0<(yq/y)){
              ui->RecvDAC1_1->setText(QString("%1").arg(x, 0, 'f', 6));
          }else if(0<(yi/y)&&(yq/y)<0){
              ui->RecvDAC1_1->setText(QString("%1").arg(x, 0, 'f', 6));
          }
          else {
              ui->RecvDAC1_1->setText(QString("%1").arg(360-x, 0, 'f', 6));
          }


          qDebug()<<"str"<<str<<"str1"<<DAC1<<"str2"<<DAC4;
          qDebug()<<"tmp"<<tmp<<"tmp1"<<tmp1<<"tmp2"<<tmp2;
          //将数据报内容显示出来
          ui->recvData->append(datagram);

          ui->recvData->append("衰减值的值为");
          ui->recvData->append(QString("%1").arg(tmp*0.5, 0, 'f', 6));
          ui->RecvPad_Value1->setText(QString("%1").arg(tmp*0.5, 0, 'f', 6));
          ui->recvData->append("衰减值的两倍为");
          ui->recvData->append(QString("%1").arg(tmp, 0, 'f', 6));

          ui->recvData->append("DAC1的值为");
          ui->recvData->append(QString("%1").arg(tmp1, 0, 'f', 6));


          ui->recvData->append("DAC4的值为");
          ui->recvData->append(QString("%1").arg(tmp2, 0, 'f', 6));
          ui->RecvDAC4_1->setText(QString("%1").arg(y, 0, 'f', 6));

          ui->recvData->append("yi的值为");
          ui->recvData->append(QString("%1").arg(yi, 0, 'f', 6));

          ui->recvData->append("yq的值为");
          ui->recvData->append(QString("%1").arg(yq, 0, 'f', 6));


       }

}
void MainWindow::processPendingDatagram1()//处理接收到数据
{

    while(m_UDPReceiver1->hasPendingDatagrams())  //拥有等待的数据报
       {
           //拥于存放接收的数据报
          QByteArray datagram1;

          //让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
          datagram1.resize(m_UDPReceiver1->pendingDatagramSize());
          //接收数据报，将其存放到datagram中
          m_UDPReceiver1->readDatagram(datagram1.data(),datagram1.size());

          char* b=datagram1.data();
          QString str,DAC1,DAC2,DAC3,DAC4;
//          qDebug()<<"char* b"<<b;
//          qDebug()<<"char* b[21]"<<b[21];
//          qDebug()<<"char* b[22]"<<b[22];

          //衰减值
          str.append(b[21]);
          str.append(b[22]);

          //DAC1
          DAC1.append(b[36]);
          DAC1.append(b[37]);
          DAC1.append(b[39]);
          DAC1.append(b[40]);

          //DAC2
          DAC2.append(b[54]);
          DAC2.append(b[55]);
          DAC2.append(b[57]);
          DAC2.append(b[58]);

          //DAC4
          DAC4.append(b[90]);
          DAC4.append(b[91]);
          DAC4.append(b[93]);
          DAC4.append(b[94]);
          bool ok;
          double tmp = str.toInt(&ok,16);
          double tmp1 = DAC1.toInt(&ok,16);
          double yi=((tmp1/65535)*2.5)-0.5;
          double tmp2 = DAC4.toInt(&ok,16);
          double  yq=((tmp2/65535)*2.5)-0.5;
          double y=sqrt(yi*yi+yq*yq);

          double x=(acos(yq/y)/M_PI)*180;//acos返回值在-pi/2到pi/2;
          if(0<(yi/y)&&0<(yq/y)){
              ui->RecvDAC1_2->setText(QString("%1").arg(x, 0, 'f', 6));
          }else if(0<(yi/y)&&(yq/y)<0){
              ui->RecvDAC1_2->setText(QString("%1").arg(x, 0, 'f', 6));
          }
          else {
              ui->RecvDAC1_2->setText(QString("%1").arg(360-x, 0, 'f', 6));
          }


          qDebug()<<"str"<<str<<"str1"<<DAC1<<"str2"<<DAC4;
          qDebug()<<"tmp"<<tmp<<"tmp1"<<tmp1<<"tmp2"<<tmp2;
          //将数据报内容显示出来
          ui->recvData_2->append(datagram1);

          ui->recvData_2->append("衰减值的值为");
          ui->recvData_2->append(QString("%1").arg(tmp*0.5, 0, 'f', 6));
          ui->RecvPad_Value2->setText(QString("%1").arg(tmp*0.5, 0, 'f', 6));
          ui->recvData_2->append("衰减值的两倍为");
          ui->recvData_2->append(QString("%1").arg(tmp, 0, 'f', 6));

          ui->recvData_2->append("DAC1的值为");
          ui->recvData_2->append(QString("%1").arg(tmp1, 0, 'f', 6));


          ui->recvData_2->append("DAC4的值为");
          ui->recvData_2->append(QString("%1").arg(tmp2, 0, 'f', 6));
          ui->RecvDAC4_2->setText(QString("%1").arg(y, 0, 'f', 6));

          ui->recvData_2->append("yi的值为");
          ui->recvData_2->append(QString("%1").arg(yi, 0, 'f', 6));

          ui->recvData_2->append("yq的值为");
          ui->recvData_2->append(QString("%1").arg(yq, 0, 'f', 6));



          qDebug()<<datagram1.length();
       }

}

void MainWindow::calculate(){
//    double x=180.235466;//相位
//    double y=0.17;//幅度
    double n,Yi,Yq;
    double Ni,Nq;
    int Mx,Mt;
    double x=ui->XSpinBox->text().toDouble();//相位
    double y=ui->YSpinBox_2->text().toDouble();//幅度
    double pad_value=ui->setsub->text().toDouble();//衰减值

    double DAC2=ui->DAC2->text().toDouble();//DAC2
    double DAC3=ui->DAC3->text().toDouble();//DAC3
    if((x >=0 && x <=360)&&(y >=0 && y <=DAC2&& y <=DAC3)&&(pad_value >=0 && pad_value <=31.5))
    {
        n=(x/180)*M_PI;//n为弧度制转化为的度数
         qDebug()<<"弧度的值为"<<n;
        ui->caclulator->append("Yi的值为");
         Yi=sin(n)*y;//*sqrt(2)*0.5;//
        ui->caclulator->append(QString("%1").arg(Yi, 0, 'f', 6));
        ui->caclulator->append("Yq的值为");
         Yq=cos(n)*y;//*sqrt(2)*0.5;//
        ui->caclulator->append(QString("%1").arg(Yq, 0, 'f', 6));
        ui->caclulator->append("Ni的值为");
        Ni=((Yi+DAC2)/2.5)*65535;//1为DAC2 DAC3的值
        ui->caclulator->append(QString("%1").arg(Ni, 0, 'f', 6));
        ui->caclulator->append("Nq的值为");
        Nq=((Yq+DAC3)/2.5)*65535;
        ui->caclulator->append(QString("%1").arg(Nq, 0, 'f', 6));
        Mx=qRound(Ni);
        QString str = QString::number(Mx,16);
        ui->caclulator->append(str);
        Mt=qRound(Nq);
        QString str1 = QString::number(Mt,16);
        ui->caclulator->append(str1);
        emit sendMsg(Mx,Mt);//发出计算结果的信号

    }
    else
    {
        QMessageBox::information(this,"警告","函数值非法请清除后重新输入...");//提示框参数为对象 提示框名字 和内容
    }


}
void MainWindow::calculate1(){
//    double x=180.235466;//相位
//    double y=0.17;//幅度
    double n,Yi,Yq;
    double Ni,Nq;
    int Mx,Mt;
    double x=ui->XSpinBox_2->text().toDouble();//相位
    double y=ui->YSpinBox_3->text().toDouble();//幅度
    double pad_value=ui->setsub_2->text().toDouble();//衰减值

    double DAC2=ui->DAC2_2->text().toDouble();//DAC2
    double DAC3=ui->DAC3_2->text().toDouble();//DAC3
    if((x >=0 && x <=360)&&(y >=0 && y <=DAC2&& y <=DAC3)&&(pad_value >=0 && pad_value <=31.5))
    {
        n=(x/180)*M_PI;//n为弧度制转化为的度数

        ui->caclulator_2->append("Yi的值为");
         Yi=sin(n)*y;//*sqrt(2)*0.5;//
        ui->caclulator_2->append(QString("%1").arg(Yi, 0, 'f', 6));
        ui->caclulator_2->append("Yq的值为");
         Yq=cos(n)*y;//*sqrt(2)*0.5;//
        ui->caclulator_2->append(QString("%1").arg(Yq, 0, 'f', 6));
        ui->caclulator_2->append("Ni的值为");
        Ni=((Yi+DAC2)/2.5)*65535;//1为DAC2 DAC3的值
        ui->caclulator_2->append(QString("%1").arg(Ni, 0, 'f', 6));
        ui->caclulator_2->append("Nq的值为");
        Nq=((Yq+DAC3)/2.5)*65535;
        ui->caclulator_2->append(QString("%1").arg(Nq, 0, 'f', 6));
        Mx=qRound(Ni);
        QString str = QString::number(Mx,16);
        ui->caclulator_2->append(str);
        Mt=qRound(Nq);
        QString str1 = QString::number(Mt,16);
        ui->caclulator_2->append(str1);
        emit sendMsg1(Mx,Mt);//发出计算结果的信号

    }
    else
    {
        QMessageBox::information(this,"警告","函数值非法请清除后重新输入...");//提示框参数为对象 提示框名字 和内容
    }


}





void MainWindow::on_pushButton_clicked()//这个是计算的按钮
{
    calculate();//按下之后直接调用calculate进行计算
}

void MainWindow::on_clear_clicked()
{
ui->YSpinBox_2->clear();
ui->XSpinBox->clear();
ui->setsub->clear();
ui->caclulator->clear();

}

void MainWindow::on_updata_clicked()
{
    m_UDPReceiver->close();//每次重新指定端口之后需要关闭套接字
    unsigned short RecvPort=ui->RecPort->text().toUShort();
    m_UDPReceiver->bind(RecvPort,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    connect(m_UDPReceiver,&QUdpSocket::readyRead,this,&MainWindow::processPendingDatagram);

}
void MainWindow::RecvPortSet(unsigned short port, QString ip){

}

void MainWindow::on_updata_2_clicked()
{
    udpsocket->close();//每次重新指定端口之后需要关闭套接字
    unsigned short port=ui->port->text().toUShort();
    udpsocket->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);

}
void MainWindow::on_updata_4_clicked()
{
    m_UDPReceiver1->close();//每次重新指定端口之后需要关闭套接字
    unsigned short RecvPort=ui->RecPort_2->text().toUShort();
    m_UDPReceiver1->bind(RecvPort,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    connect(m_UDPReceiver1,&QUdpSocket::readyRead,this,&MainWindow::processPendingDatagram1);
}

void MainWindow::on_changIp_clicked()
{
    ip=ui->ip->text();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->sendData->clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->recvData->clear();
}

void MainWindow::on_updata_3_clicked()
{
    udpsocket1->close();//每次重新指定端口之后需要关闭套接字
    unsigned short port=ui->port_2->text().toUShort();
    udpsocket1->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
}

void MainWindow::on_changIp_2_clicked()
{
     ip1=ui->ip_2->text();
}


void MainWindow::on_pushButton_6_clicked()
{
    calculate1();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->sendData_2->clear();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->recvData_2->clear();
}

void MainWindow::on_clear_2_clicked()
{
    ui->YSpinBox_3->clear();
    ui->XSpinBox_2->clear();
    ui->setsub_2->clear();
    ui->caclulator_2->clear();
}
