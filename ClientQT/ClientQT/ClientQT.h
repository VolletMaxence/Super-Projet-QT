#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ClientQT.h"
#include <qtcpsocket.h>

class ClientQT : public QMainWindow
{
	Q_OBJECT

	public:
		ClientQT(QWidget *parent = Q_NULLPTR);
		QString save_Pseudo;


	private:
		Ui::ClientQTClass ui;
		QTcpSocket * socket;


	public slots:
		void connexionServeur();
		void onSocketConnected();
		void onSocketDisonnected();
		void envoieInfoConnexion();
		void onSocketReadyRead();
		void redirectInscription();
		void envoieInscription();
		void retourConnexion();

		void receptionInfoLogin(QString);
		void receptionInfoMessage();

		//En attente d'implementation de classe user
		void deconnexion();
};