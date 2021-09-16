#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TCP_Serveur.h"
#include <qtcpserver.h>
#include <qtcpsocket.h>

class TCP_Serveur : public QMainWindow
{
    Q_OBJECT

public:
    TCP_Serveur(QWidget *parent = Q_NULLPTR);

private:
    Ui::TCP_ServeurClass ui;
	QTcpServer * server;
	QTcpSocket * socket;

public slots:
	void onServerNewConnection();
	void onClientDisconnected();
	void onClientReadyRead();
};
