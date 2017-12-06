#include <QNetworkSession>
#include <QNetworkConfigurationManager>
#include <QtNetwork>
#include <QMessageBox>
#include <QDebug>
#include "tcpconnect.h"
#include <iostream>
#include <QTextStream>

TcpConnect::TcpConnect(QObject *parent)
    : QObject(parent)
    , logFile("qtconn.log")
    , tcpSocket(new QTcpSocket(this))
    , networkSession(Q_NULLPTR)
{
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_5_9);

    connect(tcpSocket, SIGNAL(connected()), this, SLOT(writeMessage()));
    connect(tcpSocket, SIGNAL(bytesWritten(qint64))
            , this, SLOT(messageSent(qint64)));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError))
            , this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(tcpSocket, &QIODevice::readyRead, this, &TcpConnect::readResponse);
}

void TcpConnect::sendCommand(const QString &command)
{
    commandList << command;
    logMessage("About to send\t: " + command);
    if (!tcpSocket->isValid()
            || tcpSocket->state() != QAbstractSocket::ConnectedState)
    {
        connectServer();
    }
    else
        writeMessage();
}

void TcpConnect::connectServer()
{
    tcpSocket->abort();
    tcpSocket->connectToHost(ip,port);
    logMessage(" connection to ip: " + ip + " port: " + QString::number(port));
}

QString TcpConnect::getLastResponse() const
{
    return lastResponse;
}



void TcpConnect::writeMessage()
{
    if (!commandList.empty())
    {
        QString nextCommand = commandList.first();
        tcpSocket->write(commandList.first().toUtf8());
        qDebug() << "writing message " << commandList.first();
        logMessage("writing message: " + commandList.first());
        commandList.removeFirst();
    }
}

void TcpConnect::messageSent(qint64)
{

}

void TcpConnect::readResponse()
{
    logMessage("readyRead signal recieved");
    //in.startTransaction();
    QString nextResponse = tcpSocket->readAll();

    //QString nextResponse;
    //in >> nextResponse;

    //if (!in.commitTransaction())
    //{
    //    logMessage("Message recieved " + nextResponse + " Message not finishsed yet");
    //    return;
    //}

    lastResponse = nextResponse;
    emit responseRead();
    logMessage("Message recieved" + nextResponse);
    qDebug() << "Response recieved" << nextResponse;
}

void TcpConnect::displayError(QAbstractSocket::SocketError)
{
    qDebug() << "error recieved" << tcpSocket->errorString();
    logMessage("Error: " + tcpSocket->errorString());
    tcpSocket->abort();
}

void TcpConnect::setIp(const QString &value)
{
    ip = value;
}

void TcpConnect::setPort(const quint16 &value)
{
    port = value;
}

void TcpConnect::logMessage(QString message)
{
    QFile file(logFile);
    file.open(QFile::Append);
    file.write(message.toUtf8());
}

