#include "commandlist.h"

Command::Command(Cmd name
                 , const QString &command
                 , bool yearParam
                 , const QString &response
                 , int responseParamLength
                 , const QString &suffix)
    : name(name)
    , command(command)
    , yearParam(yearParam)
    , response(response)
    , responseParamLength(responseParamLength)
    , suffix(suffix)
{}

const QVector<Command>  Command::list = {
    Command(Cmd::January, "JAN", true, "January", 2, " days.")
    ,Command(Cmd::Febuary, "FEB", true, "Febuary", 2, " days.")
    ,Command(Cmd::March, "MAR", true, "March", 2, " days.")
    ,Command(Cmd::April, "APR", true, "April", 2, " days.")
    ,Command(Cmd::May, "MAY", true, "May", 2, " days.")
    ,Command(Cmd::June, "JUN", true, "June", 2, " days.")
    ,Command(Cmd::July, "JUL", true, "July", 2, " days.")
    ,Command(Cmd::August, "AUG", true, "August", 2, " days.")
    ,Command(Cmd::September, "SEP", true, "September", 2, " days.")
    ,Command(Cmd::October, "OCT", true, "October", 2, " days.")
    ,Command(Cmd::November, "NOV", true, "November", 2, " days.")
    ,Command(Cmd::December, "DEC", true, "December", 2, " days.")
    ,Command(Cmd::NumOfCommands, "", false, "Unknown command.", 0, "")
};

//CommandGUI Command::strToCmd(const QString &commandStr)
Cmd Command::strToCmd(const QString &commandStr)
{
    QString cmd(commandStr);
    cmd.trimmed();
    for ( int i=0 ; i<Cmd::NumOfCommands ; i++ )
    {
        if (list[i].command == cmd)
        {
            Cmd cmd = list[i].name;
            return cmd;
        }
    }
    return  Cmd::NumOfCommands;
}
















