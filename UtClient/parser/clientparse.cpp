#include <QDebug>
#include <cstdlib>
#include <stdio.h>
#include <fstream>

#include "clientcomgrammer.h"
#include "clientcomvocab.yy.h"
#include "clientparse.h"
#include "clientcommon.h"

ClientParse::ClientParse()
{
    
}

ClientParse::~ClientParse()
{
}

void ClientParse::parse(QByteArray commandLine)
{
    commandText = QString(commandLine);

    // Set up the scanner
    yyscan_t scanner;
    yycomlex_init(&scanner);

    // Pass this to flex to allow callbacks.
    yycomlex_init_extra( this, &scanner );
    YY_BUFFER_STATE bufferState = yycom_scan_string(commandLine.constData(), scanner);

    // Set up the parser
    void* shellParser = ParseClientAlloc(malloc);

    // Set up tracing
    FILE* traceFile;
    traceFile = fopen("traceLemon.log", "w");
    QByteArray prefix("parser >> ");
    if(traceFile != NULL) {
        ParseClientTrace(traceFile, prefix.data());
    }

    // Main parsing loop
    int lexCode;
    do {
        lexCode = yycomlex(flex_yytext, scanner);
        flex_yytext = yycomget_text(scanner);
        ParseClient(shellParser, lexCode, flex_yytext, this);
    }
    while (lexCode > 0 );

    // Cleanup the scanner and parser
    if(traceFile != NULL) {
        fclose(traceFile);
    }
    yycom_delete_buffer(bufferState, scanner);
    yycomlex_destroy(scanner);
    ParseClientFree(shellParser, free);
}



QString ClientParse::getDays() const
{
    return days;
}

QString ClientParse::getMonth() const
{
    return month;
}

void ClientParse::response(Cmd cmd, const char *yyear, const char* ydays)
{
    month = Command::list[cmd].response;
    year = QString(yyear);
    year = year.left(year.indexOf(" "));
    days = ydays;
    days = days.left(days.indexOf(" "));
}

void ClientParse::setFlexDays(const char *value)
{
    days = QString(value);
}

void ClientParse::syntaxError()
{
    qDebug()  << "syntax error parsing |" << commandText << "|\n";

}

void ClientParse::successfulParse()
{
    qDebug()  << "Succesfully parsed |" << commandText << "|\n";
}

void ClientParse::unsuccessfulParse()
{
    qDebug()  << "Unsuccesfully parsed |" << commandText << "|\n";
}

void ClientParse::stackOverflow()
{
    qDebug()  << "Stack overflow parsing |" << commandText << "|\n";
}

QString ClientParse::getYear() const
{
    return year;
}



