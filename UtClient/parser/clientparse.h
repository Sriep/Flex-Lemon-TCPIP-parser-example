#ifndef FPGAPARSE_H
#define FPGAPARSE_H

#include <QByteArray>
#include "commandlist.h"

class ClientParse
{
public:
    ClientParse();
    ~ClientParse();

    void operator()(QByteArray commandLine);
    QString getDays() const;
    QString getMonth() const;
    QString getYear() const;

    void response(Cmd cmd, const char* yyear, const char* ydays);
    void setFlexDays(const char *value);

    void syntaxError();
    void successfulParse();
    void unsuccessfulParse();
    void stackOverflow();

private:
    const char* flex_yytext;
    const char* flex_yyextra;
    QString days;
    QString month;
    QString year;
    QString lastResponse;
    QString commandText;
    QString logfile = "lemon.log";
    FILE* traceFile;
    const char* traceFilename= "traceLemon.log";
    QByteArray prefix = "parser >> ";
};

#endif //FPGAPARSE_H
