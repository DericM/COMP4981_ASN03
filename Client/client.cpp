/*------------------------------------------------------------------------------------------------------------------
* SOURCE FILE: client.cpp
*   The client will collect messages from the user interface and send them to the server. The client will receive
*   messages from the server and display them to the userinterface using QT signals and slots.
*
* PROGRAM: Client
*
* FUNCTIONS:
*   public:
*       explicit Client(QObject *parent = 0);
*       void start();
*       void run();
*       QString wrapMessage(QString user, QString message);
*   signals:
*       void recv(QString message);
*       void togle(bool state);
*   public slots:
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
*   This file contains the client logic. See connection.cpp for the worker functions.
*   The Client object is designed to facilitate communication with the user interface.
----------------------------------------------------------------------------------------------------------------------*/
#include "client.h"
#include "connection.h"
#include <thread>
#include <QTime>

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: Client
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: Client(QObject *parent)
*
* NOTES:
*   Constructor
----------------------------------------------------------------------------------------------------------------------*/
Client::Client(QObject *parent) : QObject(parent)
{
    connected = false;
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: connect
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: connect(QString host, int port)
*
* RETURNS: void
*
* NOTES:
*   Establishes a new connection to the server and starts the main client thread.
----------------------------------------------------------------------------------------------------------------------*/
void Client::connect(QString host, int port){
    if(connected){
        connected = false;
        emit togle(true);
        return;
    }

    if(!conn.socket(socket)){
        emit recv(QString("Can't connect to socket."));
        return;
    }
    if(!conn.connect(socket, host.toStdString(), port)){
        emit recv(QString("Can't connect to server."));
        return;
    }

    emit togle(false);
    connected = true;
    std::thread(&Client::run, this).detach();
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: run
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: run(QString host, int port)
*
* RETURNS: void
*
* NOTES:
*   The main client receive loop. Gets messages from the server and displays them to the user interface.
----------------------------------------------------------------------------------------------------------------------*/
void Client::run(){
    while(connected){
        QString message = conn.read(socket);
        emit recv(message);
    }
    close(socket);
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: send
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: send(QString user, QString message)
*
* RETURNS: void
*
* NOTES:
*   Sends new messages to the server.
----------------------------------------------------------------------------------------------------------------------*/
void Client::send(QString user, QString message){
    if(!connected){
        emit recv(QString("No connection."));
        return;
    }

    QString send = wrapMessage(user, message);

    emit recv(send);
    if(!conn.write(socket, send))
        connected = false;
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: wrapMessage
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: wrapMessage(QString user, QString message)
*
* RETURNS: QString
*
* NOTES:
*   Generates message wrappers. Appends username and time. Returns the ready to send packet.
----------------------------------------------------------------------------------------------------------------------*/
QString Client::wrapMessage(QString user, QString message){
    QString send;
    QString stime = QTime::currentTime().toString("HH:mm:ss");
    send.append(stime);
    send.append(" - ");
    send.append("[");
    send.append(user);
    send.append("]: ");
    send.append(message);
    return send;
}


