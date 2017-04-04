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

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <QDebug>

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: socket
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: socket(int &listen_sd)
*
* RETURNS: bool.
*
* NOTES:
*   Opens a given TCP socket and return false on error, true on success.
----------------------------------------------------------------------------------------------------------------------*/
bool Connection::socket(int &listen_sd){
    if ((listen_sd = ::socket(AF_INET, SOCK_STREAM, 0)) == -1){
        qDebug() <<  "Cannot Create Socket!" << endl;
        return false;
    }
    return true;
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: setsockopt
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: setsockopt(int &listen_sd)
*
* RETURNS: bool.
*
* NOTES:
*   Sets socket option SO_REUSEADDR on a given socket. Return true on success.
----------------------------------------------------------------------------------------------------------------------*/
bool Connection::setsockopt(int &listen_sd) {
    int arg = 1;
    if (::setsockopt (listen_sd, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) == -1){
        qDebug() << "setsockopt failed" << endl;
        return false;
    }
    return true;
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: setsockopt
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: bind(int &listen_sd, struct sockaddr_in &server, int &port)
*
* RETURNS: bool.
*
* NOTES:
*   wraper for bind. Binds a given socket to an adress and port. Return true on success.
----------------------------------------------------------------------------------------------------------------------*/
bool Connection::bind(int &listen_sd, struct sockaddr_in &server, int &port) {
    bzero((char *)&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any client

    if (::bind(listen_sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        qDebug() << "bind error" << endl;
        return false;
    }
    return true;
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: listen
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: listen(int &listen_sd)
*
* RETURNS: bool.
*
* NOTES:
*   Wrapper for the listen function.
----------------------------------------------------------------------------------------------------------------------*/
bool Connection::listen(int &listen_sd){
    ::listen(listen_sd, LISTENQ);
    return true;
}

/*------------------------------------------------------------------------------------------------------------------
* FUNCTION: accept
*
* DATE: March 22, 2017
* REVISIONS: (Date and Description)
*
* DESIGNER:   Deric Mccadden / Mark Tattrie
* PROGRAMMER: Deric Mccadden / Mark Tattrie
*
* INTERFACE: accept(int &listen_sd, int &new_sd, struct sockaddr_in &client_addr)
*
* RETURNS: bool.
*
* NOTES:
*   Wrapper for the accept function. Accept an incoming connection and assigns it its own socket.
*   Returns true on success.
----------------------------------------------------------------------------------------------------------------------*/
bool Connection::accept(int &listen_sd, int &new_sd, struct sockaddr_in &client_addr) {
    socklen_t client_len = sizeof(client_addr);
    if ((new_sd = ::accept(listen_sd, (struct sockaddr *) &client_addr, &client_len)) == -1) {
        qDebug() << "accept error" << endl;
        return false;
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
* INTERFACE: read(const int &sock, char buf[])
*
* RETURNS: bool.
*
* NOTES:
*   Wrapper for the read function. Attempts to read a packet from the socket.
----------------------------------------------------------------------------------------------------------------------*/
bool Connection::read(const int &sock, char buf[]){
    int n;
    char *bp = buf;
    int bytes_to_read = BUFLEN;
    while ((n = ::read(sock, bp, bytes_to_read)) > 0)
    {
        bp += n;
        bytes_to_read -= n;
    }
    if(bytes_to_read == BUFLEN){
        return false;
    }
    return true;
}



