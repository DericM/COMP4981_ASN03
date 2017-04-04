/*------------------------------------------------------------------------------------------------------------------
* SOURCE FILE: server.cpp
*   The server will receive incomming connections from clients and send them back out to all other connected clients.
*   This is effectively a chat room.
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
#include "server.h"

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
*   program entry point. Connects the mainwindow to the server using QT slots and signals.
----------------------------------------------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Server s;

    QObject::connect(&s, SIGNAL(updateLog(QString)),
                         &w, SLOT(updateLog(QString)));

    QObject::connect(&s, SIGNAL(togle(bool)),
                         &w, SLOT(togle(bool)));

    QObject::connect(&w, SIGNAL(start(int)),
                         &s, SLOT(start(int)));

    return a.exec();
}
