/*------------------------------------------------------------------------------------------------------------------
* SOURCE FILE: mainwindow.cpp
*   The mainwindow contains the user interface and their callback functions.
*
* PROGRAM: Server
*
* FUNCTIONS:
*   public:
*      explicit MainWindow(QWidget *parent = 0);
*      ~MainWindow();
*   public slots:
*       void updateLog(QString message);
*       void togle(bool state);
*   private slots:
*       void on_start_clicked();
*   signals:
*       void start(int port);
*   private:
*       Ui::MainWindow *ui;
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
* FUNCTION: on_start_clicked()
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: on_start_clicked()
*
* RETURNS: void.
*
* NOTES:
*   Handles start button click events.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::on_start_clicked() {
    int port = ui->port->text().toInt();
    emit start(port);
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: updateLog
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: updateLog(QString message)
*
* RETURNS: void.
*
* NOTES:
*   QT slot that handles requests to update the log.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::updateLog(QString message) {
    ui->log->setText(message);
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
void MainWindow::togle(bool state) {
    ui->port->setEnabled(state);
    (state) ? ui->start->setText("Start") : ui->start->setText("Stop");
}
