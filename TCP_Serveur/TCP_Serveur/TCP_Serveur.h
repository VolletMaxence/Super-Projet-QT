#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TCP_Serveur.h"
#include <qtcpsocket.h>
#include <qtcpserver.h>

class TCP_Serveur : public QMainWindow
{
    Q_OBJECT

public:
    TCP_Serveur(QWidget *parent = Q_NULLPTR);

private:
    Ui::TCP_ServeurClass ui;
	QTcpSocket * socket;
	QTcpServer * server;

public slots:
	void onDisplayMessageButtonClicked();
	void onConnectButtonClicked();
	void onSokectConnected();
	void onSocketDisconnected();
	void onSendMessageButtonClicked();
	void onSocketReadyRead();
	void onServerNewConnection();
};