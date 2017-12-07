#ifndef COMMANDLIST_H
#define COMMANDLIST_H
#include <QString>
#include <QVector>

enum Cmd {
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

struct Command {
    static const QVector<Command>  list;
    static Cmd strToCmd(const QString &commandStr);

    Cmd name;
    QString command;
    bool yearParam;
    QString response;
    int responseParamLength;
    QString suffix;

    Command(Cmd name
            , const QString &command
            , bool yearParam
            , const QString& response
            , int responseParamLength
            , const QString& suffix
            );

};

#endif // COMMANDLIST_H
