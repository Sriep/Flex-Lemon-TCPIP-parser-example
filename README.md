# Test-Qt-TCP-IP-Server

An example to illustrate how to write a simple client-server protocol using Qt's TCP/IP  objects. 

It was devised as a way of unit testing TCP/IP connection. The server acting as a simulation of hardware that was not available for testing against.

It is based Qt examples [Fortune Client Example](http://doc.qt.io/qt-5/qtnetwork-fortuneclient-example.html) and [Fortune Server Example](http://doc.qt.io/qt-5/qtnetwork-fortuneserver-example.html). You can read more about it on my [blog](http://piersshepperson.co.uk/programming/2017/12/07/qt-tcpip-testing-server/).

The server takes commands consisting of a month and year, eg JAN 2014, and returns the number of days in that month. The client has a simple GUI to allow sending commands to the server and displaying the result.

It is a simplified version of a server I created for unit testing a TCP/IP server connection code. The server was not available to me for testing my code so I need to simulate it. 

Hopefully, others can take my code and adapt it for their own needs.
