#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TCP_Serveur.h"
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qtwidgets>
#include <QtSql/QtSql>
#include <QSqlQuery>

class TCP_Serveur : public QMainWindow
{
    Q_OBJECT

public:
    TCP_Serveur(QWidget *parent = Q_NULLPTR);
	char retour;
	char requete;

private:
	
    Ui::TCP_ServeurClass ui;
	QTcpServer * server;
	QTcpSocket * socket;
	QString username;
	QString password;
	QSqlQuery db;

public slots:
	void onServerNewConnection();
	void onClientDisconnected();
	void onClientReadyRead();
};