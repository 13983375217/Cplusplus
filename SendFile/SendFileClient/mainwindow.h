#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void connectStart(unsigned short,QString);
    void sendfildpath(QString path);
private slots:
    void on_connetServer_clicked();

    void on_selFile_clicked();

    void on_sendFileBtn_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
