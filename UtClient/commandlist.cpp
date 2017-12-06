#include "commandlist.h"

Command::Command(CommandGUI name
                 , const QString &command
                 , const int paraLength
                 , const QString &response
                 , int responseParamLength
                 , const QString &suffix)
    : name(name)
    , command(command)
    , paraLength(paraLength)
    , response(response)
    , responseParamLength(responseParamLength)
    , suffix(suffix)
{}

const QVector<Command>  Command::list = {
    Command(CommandGUI::January, "JAN", 4, "January", 2, " days.")
    ,Command(CommandGUI::Febuary, "FEB", 4, "Febuary", 2, " days.")
    ,Command(CommandGUI::March, "MAR", 4, "March", 2, " days.")
    ,Command(CommandGUI::April, "APR", 4, "April", 2, " days.")
    ,Command(CommandGUI::May, "MAY", 4, "May", 2, " days.")
    ,Command(CommandGUI::June, "JUN", 4, "June", 2, " days.")
    ,Command(CommandGUI::July, "JUL", 4, "July", 2, " days.")
    ,Command(CommandGUI::August, "AUG", 4, "August", 2, " days.")
    ,Command(CommandGUI::September, "SEP", 4, "September", 2, " days.")
    ,Command(CommandGUI::October, "OCT", 4, "October", 2, " days.")
    ,Command(CommandGUI::November, "NOV", 4, "November", 2, " days.")
    ,Command(CommandGUI::December, "DEC", 4, "December", 2, " days.")
    ,Command(CommandGUI::NumOfCommands, "", 0, "Unknown command.", 0, "")
};

//CommandGUI Command::strToCmd(const QString &commandStr)
CommandGUI Command::strToCmd(const QString &commandStr)
{
    QString cmd(commandStr);
    cmd.trimmed();
    for ( int i=0 ; i<CommandGUI::NumOfCommands ; i++ )
    {
        if (list[i].command == cmd)
        {
            CommandGUI cmd = list[i].name;
            return cmd;
        }
    }
    return  CommandGUI::NumOfCommands;
}
















