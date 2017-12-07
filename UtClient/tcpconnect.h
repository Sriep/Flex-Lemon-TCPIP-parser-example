#ifndef FPGACONNECT_H
#define FPGACONNECT_H

#include <QAbstractSocket>
#include <QTcpSocket>
#include <QSctpSocket>

#include <QUdpSocket>
#include <QObject>
#include <QString>
#include <QDataStream>
#include <QStringList>
#include <QFile>

class QNetworkSession;
class Client;
class TcpConnect : public QObject
{
    Q_OBJECT
public:
    explicit TcpConnect(Client *parent);
    void sendCommand(const QString &value);

    void setPort(const quint16 &value);
    void setIp(const QString &value);
    void logMessage(QString message);

    QString getLastResponse() const;

public slots:
    void writeMessage();
private slots:

    void messageSent(qint64);
    void readResponse();
    void displayError(QAbstractSocket::SocketError);
signals:
    void responseRead();
private:
    void connectServer();

    Client *client;
    QString logFile;

    QStringList commandList;
    QString nextMessage = "";
    QTcpSocket* tcpSocket;

    QDataStream in;
    QNetworkSession *networkSession;
    QString lastResponse;

    quint16 port = 57853;
    QString ip = "192.168.1.76";
    bool connected = false;
};

#endif // FPGACONNECT_H
