#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <string>

using std::string;

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void run(int port);
    void logConnections();

signals:
    void updateLog(QString message);
    void togle(bool state);

public slots:
    void start(int port);

private:
    std::map<int, string> clients;
    bool running;
};

#endif // SERVER_H
