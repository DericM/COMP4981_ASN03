/*------------------------------------------------------------------------------------------------------------------
* SOURCE FILE: connection.cpp
*   The is class represents a connection instance. It contains methods and functions for initializing and
*   maintaining a TCP connection.
*
* PROGRAM: Server
*
* FUNCTIONS:
*       bool socket(int &listen_sd);
*       bool setsockopt(int &listen_sd);
*       bool bind(int &listen_sd, struct sockaddr_in &server, int &port);
*       bool listen(int &listen_sd);
*       bool accept(int &listen_sd, int &new_sd, struct sockaddr_in &client_addr);
*       bool read(const int &sock, char buf[]);
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* NOTES:
*   This file contains wrappers for the sys/sockets.h socket functions.
----------------------------------------------------------------------------------------------------------------------*/
#include "connection.h"

#include <QString>
#include <QDebug>
#include <errno.h>
#include <string>

using std::string;

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: write
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: write(int &socket, QString message)
*
* RETURNS: bool.
*
* NOTES:
*   Wrapper for the write function. Attempts to write a packet to the socket. Returns true on success.
----------------------------------------------------------------------------------------------------------------------*/
bool Connection::write(int &socket, QString message){
    char *bp, sbuf[BUFLEN];
    int bytes_to_send = BUFLEN;
    int n = 0;

    bp = sbuf;

    std::string str = message.toStdString();
    strncpy(sbuf, str.c_str(), BUFLEN);

    while(bytes_to_send > 0){
        n = ::write(socket, bp, bytes_to_send);
        if(n == -1){
            qDebug() << "write() failed with error " << errno << endl;
            return false;
        }
        bp += n;
        bytes_to_send -= n;
        qDebug() << "bytes_to_send " << bytes_to_send << endl;
    }

    return true;
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: read
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: read(const int &sock)
*
* RETURNS: QString.
*
* NOTES:
*   Wrapper for the read function. Attempts to read a packet from the socket. Returns the packet contents.
----------------------------------------------------------------------------------------------------------------------*/
QString Connection::read(int &socket){
    char  *bp, rbuf[BUFLEN];
    int bytes_to_read = BUFLEN;
    int n = 0;

    bp = rbuf;
    while (bytes_to_read > 0)
    {
        n = ::recv(socket, bp, bytes_to_read, 0);
        bp += n;
        bytes_to_read -= n;
    }
    QString receive(rbuf);
    return receive;
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: socket
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: socket(int &socket)
*
* RETURNS: bool.
*
* NOTES:
*   Wrapper for the socket function. Attempts to open a scoket. Returns true on success.
----------------------------------------------------------------------------------------------------------------------*/
bool Connection::socket(int &socket){
    if ((socket = ::socket(AF_INET, SOCK_STREAM, 0)) == -1){
        qDebug() << "Cannot Create Socket!" << endl;
        return false;
    }
    return true;
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
* INTERFACE: connect(int &socket, string host, int port)
*
* RETURNS: bool.
*
* NOTES:
*   Wrapper for the connect function. Attempts to connect a socket to an address and port. Returns true on success.
----------------------------------------------------------------------------------------------------------------------*/
bool Connection::connect(int &socket, string host, int port){
    struct sockaddr_in server;
    hostent  *hp;

    bzero((char *)&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if ((hp = gethostbyname(host.c_str())) == NULL)
    {
        qDebug() <<  "Unknown server address" << endl;
        return false;
    }
    bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);

    if (::connect(socket, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        qDebug() <<  "Can't connect to server" << endl;
        return false;
    }
    return true;
}

