/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QtNetwork>

#include "client.h"
#include "commandlist.h"
#include "tcpconnect.h"
#include "parser/clientparse.h"

//! [0]
Client::Client(QWidget *parent)
    : QDialog(parent)
    , hostCombo(new QComboBox)
    , portLineEdit(new QLineEdit)
    , sendButton(new QPushButton(tr("Send")))
    , commandCombo(new QComboBox)
    , yearLineEdit(new QLineEdit)
    , tcpConnect(new TcpConnect(this))
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
//! [0]
    hostCombo->setEditable(true);
    // find out name of this machine
    QString name = QHostInfo::localHostName();
    if (!name.isEmpty()) {
        hostCombo->addItem(name);
        QString domain = QHostInfo::localDomainName();
        if (!domain.isEmpty())
            hostCombo->addItem(name + QChar('.') + domain);
    }
    if (name != QLatin1String("localhost"))
        hostCombo->addItem(QString("localhost"));
    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }
    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }

    for ( int cmd = January ; cmd < NumOfCommands ; cmd++ )
    {
        commandCombo->addItem(Command::list[cmd].command);
    }

    portLineEdit->setValidator(new QIntValidator(1, 65535, this));
    yearLineEdit->setValidator(new QIntValidator(1,3000, this));

    QLabel *hostLabel = new QLabel(tr("&Server name:"));
    hostLabel->setBuddy(hostCombo);
    QLabel *portLabel = new QLabel(tr("S&erver port:"));
    portLabel->setBuddy(portLineEdit);

    QLabel *commandLable = new QLabel(tr("&Command:"));
    commandLable->setBuddy(commandCombo);
    QLabel *yearLable = new QLabel(tr("&Year:"));
    yearLable->setBuddy(yearLineEdit);


    statusLabel = new QLabel(tr("This examples requires that you run the "
                                "Server example as well."));

    sendButton->setDefault(true);
    sendButton->setEnabled(false);

    QPushButton *quitButton = new QPushButton(tr("Quit"));

    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(sendButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    connect(hostCombo, &QComboBox::editTextChanged,
            this, &Client::enableSendButton);
    connect(portLineEdit, &QLineEdit::textChanged,
            this, &Client::enableSendButton);
    connect(yearLineEdit, &QLineEdit::textChanged,
            this, &Client::enableSendButton);
    connect(sendButton, &QAbstractButton::clicked,
            this, &Client::sendCommand);
    connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);

    connect(tcpConnect, SIGNAL(responseRead()), this, SLOT(readResonse()) );

    QGridLayout *mainLayout = Q_NULLPTR;
    if (QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized()) {
        QVBoxLayout *outerVerticalLayout = new QVBoxLayout(this);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
        QHBoxLayout *outerHorizontalLayout = new QHBoxLayout;
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        QGroupBox *groupBox = new QGroupBox(QGuiApplication::applicationDisplayName());
        mainLayout = new QGridLayout(groupBox);
        outerHorizontalLayout->addWidget(groupBox);
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        outerVerticalLayout->addLayout(outerHorizontalLayout);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
    } else {
        mainLayout = new QGridLayout(this);
    }
    mainLayout->addWidget(hostLabel, 0, 0);
    mainLayout->addWidget(hostCombo, 0, 1);
    mainLayout->addWidget(portLabel, 1, 0);
    mainLayout->addWidget(portLineEdit, 1, 1);

    mainLayout->addWidget(commandLable, 2, 0);
    mainLayout->addWidget(commandCombo, 2, 1);
    mainLayout->addWidget(yearLable, 3, 0);
    mainLayout->addWidget(yearLineEdit, 3, 1);

    mainLayout->addWidget(statusLabel, 4, 0, 1, 2);
    mainLayout->addWidget(buttonBox, 5, 0, 1, 2);

    setWindowTitle(QGuiApplication::applicationDisplayName());
    portLineEdit->setFocus();
}

void Client::sendCommand()
{
    tcpConnect->setIp(hostCombo->currentText());
    tcpConnect->setPort(portLineEdit->text().toInt());

    QString command = commandCombo->currentText();
    Command cmd = Command::list[Command::strToCmd(command)];
    if (Cmd::NumOfCommands != cmd.name)
    {
        if (cmd.yearParam)
        {
            command += " ";
            command += yearLineEdit->text();
        }
        tcpConnect->sendCommand(command);
    }
}

void Client::readResonse()
{
    lastResponse = tcpConnect->getLastResponse();
    ClientParse parser;
    parser.parse(lastResponse.toLatin1());
    QString statusMesg;
    statusMesg = "There are " + parser.getDays() + " in " + parser.getMonth();
    statusMesg = statusMesg + " " + parser.getYear();
    setStatusMessage(lastResponse);
}

void Client::enableSendButton()
{
    sendButton->setEnabled(!hostCombo->currentText().isEmpty()
                           && !portLineEdit->text().isEmpty()
                           && !yearLineEdit->text().isEmpty()
                           && !commandCombo->currentText().isEmpty());

}

void Client::setStatusMessage(const QString &status)
{
    statusLabel->setText(status);
}




