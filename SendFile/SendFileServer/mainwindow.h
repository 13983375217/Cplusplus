#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QTcpServer>
#include <QMainWindow>
#include<QTcpSocket>
#include"mytcpserver.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//QTcpSocket*m_tcp;
QTcpServer*m_tcp;
//MyTcpServer*m_tcp;
signals:

private slots:
    void on_setListen_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
