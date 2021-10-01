#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_webserver.h"
#include <QTcpSocket.h>

class webserver : public QMainWindow
{
    Q_OBJECT

public:
    webserver(QWidget *parent = Q_NULLPTR);

private:
    Ui::webserverClass ui;
	QTcpSocket * socket;
};
