#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TCP_Serveur.h"
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qtwidgets>

class TCP_Serveur : public QMainWindow
{
    Q_OBJECT

public:
    TCP_Serveur(QWidget *parent = Q_NULLPTR);

private:
	
    Ui::TCP_ServeurClass ui;
	QTcpServer * server;
	QTcpSocket * socket;
	QString username;
	QString password;

public slots:
	void onServerNewConnection();
	void onClientDisconnected();
	void onClientReadyRead();
	void ConnectionDataBase();
	void Login();
};