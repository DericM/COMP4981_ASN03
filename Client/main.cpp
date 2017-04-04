/*------------------------------------------------------------------------------------------------------------------
* SOURCE FILE: client.cpp
*   The client will collect user input and format it for sending to the server. It will display incomming
*   messages to the mainwindow for the users.
*
* PROGRAM: Server
*
* FUNCTIONS:
*   main(int argc, char *argv[])
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* NOTES:
*   This file contains the program initialization and entry point.
----------------------------------------------------------------------------------------------------------------------*/
#include "mainwindow.h"
#include <QApplication>
#include "client.h"

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: main
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: main(int argc, char *argv[])
*
* RETURNS: int.
*
* NOTES:
*   program entry point. Connects the mainwindow to the client using QT slots and signals.
----------------------------------------------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Client c;

    QObject::connect(&w, SIGNAL(connect(QString, int)),
                         &c, SLOT(connect(QString, int)));

    QObject::connect(&w, SIGNAL(send(QString, QString)),
                         &c, SLOT(send(QString, QString)));

    QObject::connect(&c, SIGNAL(recv(QString)),
                         &w, SLOT(recv(QString)));

    QObject::connect(&c, SIGNAL(togle(bool)),
                         &w, SLOT(togle(bool)));

    return a.exec();
}
