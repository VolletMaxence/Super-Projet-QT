#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ClientQT.h"
#include <qtcpsocket.h>

class ClientQT : public QMainWindow
{
	Q_OBJECT

	public:
		ClientQT(QWidget *parent = Q_NULLPTR);

	private:
		Ui::ClientQTClass ui;
		QTcpSocket * socket;

	public slots:
		void onSocketConnected();
		void onSocketDisonnected();
		void connexion();
		void autorisationConnection();
};