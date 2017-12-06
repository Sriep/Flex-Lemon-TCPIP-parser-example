#ifndef COMMANDLIST_H
#define COMMANDLIST_H
#include <QString>
#include <QVector>

enum CommandGUI {
    January = 0
    ,Febuary
    ,March
    ,April
    ,May
    ,June
    ,July
    ,August
    ,September
    ,October
    ,November
    ,December
    ,NumOfCommands
};

const QString InvalidRequest = "Unknown Command";

struct Command {
    static const QVector<Command>  list;
    static CommandGUI strToCmd(const QString &commandStr);

    CommandGUI name;
    const QString command;
    const QString paraLength;
    const QString response;
    int responseParamLength;
    QString suffix;

    Command(CommandGUI name
            , const QString &command
            , const int paraLength
            , const QString& response
            , int responseParamLength
            , const QString& suffix
            );

};

#endif // COMMANDLIST_H
