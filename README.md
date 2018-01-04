# Test-Qt-TCP-IP-Server

An example to illustrate how to write a simple client-server protocol using Qt's TCP/IP  objects. 

It was devised as a way of unit testing TCP/IP connection. The server acting as a simulation of hardware that was not available for testing against.

It is based Qt examples [Fortune Client Example](http://doc.qt.io/qt-5/qtnetwork-fortuneclient-example.html) and [Fortune Server Example](http://doc.qt.io/qt-5/qtnetwork-fortuneserver-example.html). You can read more about it on my [blog](http://piersshepperson.co.uk/programming/2017/12/07/qt-tcpip-testing-server/).

The server takes commands consisting of a month and year, eg JAN 2014, and returns the number of days in that month. The client has a simple GUI to allow sending commands to the server and displaying the result.

It is a simplified version of a server I created for unit testing a TCP/IP server connection code. The server was not available to me for testing my code so I need to simulate it. 

Hopefully, others can take my code and adapt it for their own needs.

# Flex lemon parser

The /UtClient/parser/ directory has an example of a flex lemon parser. It should be relatively simple to modify this for your own use. This has been developed on windows but should work on any OS that flex and lemon support.

Just copy the UtClient/parser directoy to your system and modify the flex, .l and lemon .y to fit your needs.

## Files to copy.

[clientcomvocab.l](https://github.com/Sriep/Flex-Lemon-TCPIP-parser/blob/master/UtClient/parser/clientcomvocab.l): This is the flex tokenizer. You will want to edit this so that it recognises the tokens in the grammar you are parsing. You will also want to download the [latest version of flex](http://gnuwin32.sourceforge.net/packages/flex.htm). You should also check out the [flex manual](https://westes.github.io/flex/manual/index.html#Top).

[lentcomgrammer.y](https://github.com/Sriep/Flex-Lemon-TCPIP-parser/blob/master/UtClient/parser/clientcomgrammer.y) is the grammar parser. Again you will want to edit this to match the grammar you are working on.  You should probably download and build the [latest version of lemon](https://www.hwaci.com/sw/lemon/). Also read the [lemon manual](https://www.sqlite.org/src/doc/trunk/doc/lemon.html).

I found the following webpages helpfull. [souptonuts](http://souptonuts.sourceforge.net/readme_lemon_tutorial.html)[flex-lemon-example](https://github.com/theory/flex-lemon-example)and [Generating a High-Speed Parser](https://www.codeproject.com/Articles/1056460/Generating-a-High-Speed-Parser-Part-Lemon).

The [clientparses.h](https://github.com/Sriep/Flex-Lemon-TCPIP-parser/blob/master/UtClient/parser/clientparse.h) and [clieentparse.cpp](https://github.com/Sriep/Flex-Lemon-TCPIP-parser/blob/master/UtClient/parser/clientparse.cpp) files; the ClientPrase object wraps a flex lemon parser. 

This contains callback functions used from flex and lemon. I have included 

void ClientParse::setFlexDays(const char *value); 

a callback function from flex and 

void ClientParse::response(Cmd cmd, const char* yyear, const char* ydays); 

a callback function from lemon. You will want to add your own functions here.

Also the flex option

%option prefix="yycom"

and the lemon option 

%name ParseClient

prefix all the flex and lemon calls, which allow multiple flex-lemon parsers to be run on the same machine. You will probably want to use your own names. The 

void ClientParse::parse(QByteArray commandLine) 

function will then need to be modified with these new names. A find and replace should work fine.

## Build flex and lemon files

On windows, you can now generate the other files by running the following commands. Similar commands should work on bash, except the --wincompat option can probably be removed.

win_flex --wincompat clientcomvocab.l

lemon clientcomgrammer.y -s

powershell -Command "(gc clientcomgrammer.c) -replace 'clientcomgrammer.c', 'clientcomgrammer.cpp' | Out-File clientcomgrammer.cpp"

del clientcomgrammer.c

the power shell command just replaces clentcomgrammer.c with clientcomgrammer.cpp everywhere. You will also need to add to the top of clientvocab.h

#include "clientparse.h"
#define YYSTYPE const char

Again feel to rename anything to fit in with your setup.








