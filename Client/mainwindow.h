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

public slots:
    void recv(QString message);
    void togle(bool state);

private slots:
    void on_send_clicked();

    void on_connect_clicked();

    void on_save_clicked();

signals:
    void send(QString user, QString message);
    void connect(QString host, int port);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
