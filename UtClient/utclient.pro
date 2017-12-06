QT += network widgets

HEADERS       = client.h \
    commandlist.h \
    tcpconnect.h
SOURCES       = client.cpp \
                main.cpp \
    commandlist.cpp \
    tcpconnect.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/fortuneclient
INSTALLS += target
