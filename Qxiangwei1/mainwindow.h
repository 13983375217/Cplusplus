#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
static QByteArray dataQbyte,dataQbyte1;
static QString ip,ip1;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QUdpSocket *udpsocket;
    QUdpSocket *udpsocket1;
    QUdpSocket *m_UDPReceiver;
    QUdpSocket *m_UDPReceiver1;
    void RecvPortSet(unsigned short port, QString ip);

    void calculate1();
public slots:
   //void on_sendBtn_clicked();
    void processPendingDatagram();
    void processPendingDatagram1();
    void calculate();
    //void sendInfomation(QString str,QString str1);
     void sendInfomation(int Mx,int Mq);
     void sendInfomation1(int Mx,int Mq);
private slots:
    void on_pushButton_clicked();

    void on_clear_clicked();
    void on_updata_clicked();


    void on_updata_2_clicked();

    void on_changIp_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_updata_3_clicked();

    void on_changIp_2_clicked();

    void on_updata_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_clear_2_clicked();

signals:
   //void sendMsg(QString str,QString str1);
   void sendMsg(int Mx,int Mq);
   void sendMsg1(int Mx,int Mq);
   void sendDatagram(QByteArray datagram);
   void connectStart(unsigned short,QString);
   void sendPort(unsigned short port);
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
