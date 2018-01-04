#ifndef FPGAPARSE_H
#define FPGAPARSE_H

#include <QByteArray>
#include "commandlist.h"

/*!
 * \brief The ClientParse class
 *
 * Wraps a Flex Lemon parser.
 *
 * Flex is a toxaniser avalable on GitHub
 * <a href="https://github.com/westes/flex">. Tokanising rules are
 * given in clientcomvocab.l. Functions that start yycom are flex.
 *
 * Lemon <a href="https://github.com/deplinenoise/lemon-win32">
 * is a praser that takes a string of tokens from Flex and
 * fits them into a gramer, defined in clientcomgrammer.y.
 * <a href="https://github.com/deplinenoise/lemon-win32">
 *
 * Flex and Lemon makes calls to ClientParse member functions
 * during parsing.
 */
class ClientParse
{
public:
    ClientParse();
    ~ClientParse();

    /*!
     * \brief parse
     * Parses a string according to the grammer defined in the flex
     * and lemon grammer files.
     *
     * \param commandLine
     * The line to be parsed.
     */
    void parse(QByteArray commandLine);

    /*!
     * \brief getDays
     * \return Returns data found in the parser. Can be called
     * after some data has been parsed.
     */
    QString getDays() const;
    QString getMonth() const;
    QString getYear() const;

    /*!
     * \brief response
     * Called from within the lemon parser once a line has been succesfully
     * parsed. This is where you can perform any actions associated with
     * the identified grammatic element.
     * The parameters tend to contain the rest of the line starting at the
     * identified variable.
     * \param cmd
     * \param yyear
     * \param ydays
     */
    void response(Cmd cmd, const char* yyear, const char* ydays);

    /*!
     * \brief setFlexDays
     * Called from within the flex tokeniser. You can use this to perform
     * any actions related to an identified token. For instance, this is often
     * the best place to store the value an identified variable.
     * \param value
     */
    void setFlexDays(const char *value);

    /*!
     * \brief syntaxError
     * Called when a syntax error is identified by lemon parser.
     * <a href="https://www.sqlite.org/src/doc/trunk/doc/lemon.html#syntax_error">
     */
    void syntaxError();

    /*!
     * \brief successfulParse
     * Called after a line has been succesfully parsed by lemon.
     * <a href="https://www.sqlite.org/src/doc/trunk/doc/lemon.html#parse_accept">
     */
    void successfulParse();

    /*!
     * \brief unsuccessfulParse
     * Called after a line has been succesfully parsed by lemon.
     * <a href="https://www.sqlite.org/src/doc/trunk/doc/lemon.html#parse_failure">
     */
    void unsuccessfulParse();

    /*!
     * \brief stackOverflow
     * Called after a stack overflow has been detected by lemon.
     * <a href="https://www.sqlite.org/src/doc/trunk/doc/lemon.html#stack_overflow">
     */
    void stackOverflow();

private:

    /*!
     * \brief flex_yytext
     * Entered into flex toxaniser, holds text associated with current
     * token.
     */
    const char* flex_yytext;
    QString days;
    QString month;
    QString year;
    QString lastResponse;
    QString commandText;
    QString logfile = "lemon.log";

    /*!
     * \brief traceFile
     * File used for lemon parse tracing. Can be useful for debugging.
     */
    FILE* traceFile;
    const char* traceFilename= "traceLemon.log";
    QByteArray prefix = "parser >> ";
};

#endif //FPGAPARSE_H
