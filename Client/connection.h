#ifndef CONNECTION_H
#define CONNECTION_H
#include <QString>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

using std::string;

#define BUFLEN			    1024

class Connection
{
public:
    bool socket(int &socket);
    bool connect(int &socket, string host, int port);

    bool write(int &socket, QString message);
    QString read(int &socket);

private:
};

#endif // CONNECTION_H
