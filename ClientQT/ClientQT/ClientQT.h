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
		//Connexion / D�connexion au serveur
		void connexionServeur();
		void onSocketConnected();
		void onSocketDisonnected();
		//Envoie des donn�e
		void envoieInfoConnexion();
		void envoieInscription();
		void envoieMessage();
		//Redirection vers autre page
		void redirectInscription();
		void retourConnexion();
		void deconnexion();
		//Recpetion des messages du serveur
		void onSocketReadyRead();
		void receptionInfoLogin(QString);
		void receptionInfoMessage(QString);
		void receptionInfoInscription(QString);
		void priseCentDernierMessage(); 
		void priseCentDernierMessageLogin();
};