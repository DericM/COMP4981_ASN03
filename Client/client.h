#ifndef CLIENT_H
#define CLIENT_H
#include "connection.h"
#include <QObject>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void start();
    void run();
    QString wrapMessage(QString user, QString message);

signals:
    void recv(QString message);
    void togle(bool state);

public slots:
    void send(QString user, QString message);
    void connect(QString host, int port);

private:
    Connection conn;
    int socket;
    bool connected;
};

#endif // CLIENT_H
