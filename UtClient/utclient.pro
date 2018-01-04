QT += network widgets

HEADERS       = client.h \
    commandlist.h \
    tcpconnect.h \
    parser/clientcomgrammer.y \
    parser/clientcomgrammer.h \
    parser/clientcommon.h \
    parser/clientcomvocab.l \
    parser/clientcomvocab.yy.h \
    parser/clientparse.h


SOURCES       = client.cpp \
                main.cpp \
    commandlist.cpp \
    tcpconnect.cpp \
    parser/clientparse.cpp \
    parser/clientcomgrammer.cpp \
    parser/clientcomvocab.yy.cpp


DISTFILES += \
    parser/clientcomgrammer.out \
    parser/makelex.bat

