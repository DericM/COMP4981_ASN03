#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

#define BUFLEN	1024
#define LISTENQ	5

class Connection
{
public:
    bool socket(int &listen_sd);
    bool setsockopt(int &listen_sd);
    bool bind(int &listen_sd, struct sockaddr_in &server, int &port);
    bool listen(int &listen_sd);
    bool accept(int &listen_sd, int &new_sd, struct sockaddr_in &client_addr);
    bool read(const int &sock, char buf[]);
};

#endif // CONNECTION_H
