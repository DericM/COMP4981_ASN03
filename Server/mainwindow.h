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
    void updateLog(QString message);
    void togle(bool state);

private slots:
    void on_start_clicked();

signals:
    void start(int port);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
