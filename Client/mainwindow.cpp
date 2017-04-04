/*------------------------------------------------------------------------------------------------------------------
* SOURCE FILE: mainwindow.cpp
*   The mainwindow contains the user interface and their callback functions.
*
* PROGRAM: Server
*
* FUNCTIONS:
*   public:
*       explicit MainWindow(QWidget *parent = 0);
*       ~MainWindow();
*   public slots:
*       void recv(QString message);
*       void togle(bool state);
*   private slots:
*       void on_send_clicked();
*       void on_connect_clicked();
*       void on_save_clicked();
*   signals:
*       void send(QString user, QString message);
*       void connect(QString host, int port);
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* NOTES:
*   This file contains the user interface functions and methods.
----------------------------------------------------------------------------------------------------------------------*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: MainWindow
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: MainWindow(QWidget *parent)
*
* NOTES:
*   Constructor
----------------------------------------------------------------------------------------------------------------------*/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: ~MainWindow
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: ~MainWindow(QWidget *parent)
*
* NOTES:
*   Destructor
----------------------------------------------------------------------------------------------------------------------*/
MainWindow::~MainWindow() {
    delete ui;
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: recv
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: recv(QString message)
*
* RETURNS: void.
*
* NOTES:
*   QT slot that handles signals to append messages to the log.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::recv(QString message){
    ui->log->append(message);
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: togle
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: togle(bool state)
*
* RETURNS: void.
*
* NOTES:
*   QT slot that handles signals to togle the ui fields off when the program is connected to a port.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::togle(bool state){
    ui->host->setEnabled(state);
    ui->port->setEnabled(state);
    (state) ? ui->connect->setText("Connect") : ui->connect->setText("Disconnect");
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: on_send_clicked()
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: on_send_clicked()
*
* RETURNS: void.
*
* NOTES:
*   Handles send button click events.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::on_send_clicked() {
    QString message = ui->input->toPlainText();
    QString user = ui->user->text();
    emit send(user, message);
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: on_connect_clicked()
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: on_connect_clicked()
*
* RETURNS: void.
*
* NOTES:
*   Handles connect button click events.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::on_connect_clicked() {
    QString host = ui->host->text();
    int port = ui->port->text().toInt();
    emit connect(host, port);
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: on_save_clicked()
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: on_save_clicked()
*
* RETURNS: void.
*
* NOTES:
*   Handles save button click events. Saves a copy of the log to a file.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::on_save_clicked() {
    QString filename = QFileDialog::getSaveFileName(this, "Save File", "/home/chat.txt", "Text Files (*.txt)");
    QFile handle(filename);

    if (handle.open(QFile::ReadWrite)) {
        QTextStream out(&handle);
        out << ui->log->toPlainText();
    }
    handle.close();
}
