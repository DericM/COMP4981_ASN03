/*------------------------------------------------------------------------------------------------------------------
* SOURCE FILE: server.cpp
*   The server will receive incomming connections from clients and store them in a map with the socket as the key.
*   The sockets will be routinely checked for incoming messages. Copies of new messages will be sent out to all
*   other active connections.
*
* PROGRAM: Server
*
* FUNCTIONS:
*   public:
*       explicit Server(QObject *parent = 0);
*       void run(int port);
*       void logConnections();
*   signals:
*       void updateLog(QString message);
*       void togle(bool state);
*   public slots:
*       void start(int port);
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* NOTES:
*   This file contains the server logic. See connection.cpp for the worker functions.
*   The Server object is designed to facilitate communication with the user interface.
----------------------------------------------------------------------------------------------------------------------*/
#include "server.h"
#include "connection.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <QDebug>
#include <map>
#include <thread>

using std::string;

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: Server
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: Server(QObject *parent)
*
* NOTES:
*   Constructor
----------------------------------------------------------------------------------------------------------------------*/
Server::Server(QObject *parent) : QObject(parent) {
    running = false;
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: start
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: start(int port)
*
* RETURNS: void.
*
* NOTES:
*   Starts the program or lets the current thread fall through if it is already running.
----------------------------------------------------------------------------------------------------------------------*/
void Server::start(int port) {
    if(running){
        emit togle(true);
        running = false;
        return;
    }
    emit togle(false);
    running = true;
    std::thread(&Server::run, this, port).detach();
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
* INTERFACE: run(int port)
*
* RETURNS: void.
*
* NOTES:
*   Contains the main server loop and logic.
*       Opens/ binds and then listens to a inbound socket.
*       As new connections come in, it creates a socket for each and stores them in a map.
*       Loops through each active socket and receives new messages.
*       Sends messages back out to all other stored connections.
----------------------------------------------------------------------------------------------------------------------*/
void Server::run(int port) {
    Connection c;
    int listen_sd, new_sd, max_sd;
    int nready;
    struct sockaddr_in server, client_addr;
    char buf[BUFLEN];
    fd_set rset, allset;

    if(!c.socket(listen_sd))
        return;
    if(!c.setsockopt(listen_sd))
        return;
    if(!c.bind(listen_sd, server, port))
        return;
    if(!c.listen(listen_sd))
        return;

    max_sd = listen_sd;	// initialize
    FD_ZERO(&allset);
    FD_SET(listen_sd, &allset);

    while (running) {
        rset = allset;// structure assignment
        nready = select(max_sd + 1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(listen_sd, &rset)) { // new client connection
            c.accept(listen_sd, new_sd, client_addr);

            string value(inet_ntoa(client_addr.sin_addr));
            clients.emplace(new_sd, value);

            FD_SET (new_sd, &allset); // add new descriptor to set

            if (new_sd > max_sd)
                max_sd = new_sd;// for select

            if (--nready <= 0)
                continue;
        }

        logConnections();

        for(auto& sockfd: clients) {
            if (FD_ISSET(sockfd.first, &rset)) {
                if(!c.read(sockfd.first, buf)) {
                    qDebug() << " Remote Address:  " << sockfd.second.c_str() << " closed connection" << endl;
                    close(sockfd.first);
                    FD_CLR(sockfd.first, &allset);
                    clients.erase(sockfd.first);
                    continue;
                }
                for(auto& sockout: clients) {
                    if(sockfd.first == sockout.first)
                        continue;
                    write(sockout.first, buf, BUFLEN);
                }
                if (--nready <= 0)
                    break;
            }
        }
    }
    for(auto& sd: clients) {
        close(sd.first);
        FD_CLR(sd.first, &allset);
        clients.erase(sd.first);
    }
    close(listen_sd);
}


/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: logConnections
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: logConnections()
*
* RETURNS: void.
*
* NOTES:
*   Creates a message from the ipaddresses of each client and sends it the the mainwindow using the update log signal.
----------------------------------------------------------------------------------------------------------------------*/
void Server::logConnections(){
    QString message;
    for (auto& c : clients) {
        message.append(c.second.c_str());
        message.append("\n");
    }
    emit updateLog(message);
}



