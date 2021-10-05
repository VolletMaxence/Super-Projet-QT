#include "TCP_Serveur.h"
#include <qdebug.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <qregularexpression.h>
#include <QRegExp>
#include <QByteArray.h> 

TCP_Serveur::TCP_Serveur(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	socket = new QTcpSocket(this);
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
	server = new QTcpServer(this);
	QObject::connect(server, SIGNAL(newConnection()), this, SLOT(onServerNewConnection()));
	server->listen(QHostAddress::AnyIPv4, 4321);
}

void TCP_Serveur::onServerNewConnection()
{
	ui.connectionStatusLabel->setText("Un client c'est connecté");
	QTcpSocket * client = server->nextPendingConnection();
	QObject::connect(client, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
	QObject::connect(client, SIGNAL(disconnect()), this, SLOT(onClientDisconnected()));
}

void TCP_Serveur::onClientDisconnected()
{
	QTcpSocket * obj = qobject_cast<QTcpSocket*>(sender());
	QObject::disconnect(obj, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
	QObject::disconnect(obj, SIGNAL(readyRead()), this, SLOT(onClientDisconnected()));
	obj->deleteLater();
}

void TCP_Serveur::onClientReadyRead()
{
	QTcpSocket * obj = qobject_cast<QTcpSocket*>(sender());
	QByteArray data = obj->read(obj->bytesAvailable());
	QString str(data);

	ui.Message->setText(str);

	if (str == "MSG100")
	{
		//Envoyer les 100 derniers messages
		QRegExp rxL("^([^\t]+)");
		if (rxL.indexIn(str) != -1)
		{
			QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
			db.setHostName("192.168.64.66");
			db.setDatabaseName("QT");
			db.setUserName("superuser");
			db.setPassword("superuser");
			QSqlQuery query(db);

			if (!db.open())
			{
				ui.connectionStatusLabel->setText("Pb de connexion a la db");
			}
			else
			{
				//Récupérer les 100 derniers messages
				QSqlQuery query("SELECT Content FROM `Message` ORDER BY `Date` ASC LIMIT 100");
				while (query.next())
				{
					QString message = query.value(0).toString();
					QByteArray MessageEncode = message.toUtf8();
					obj->write(MessageEncode + "\n");
				}
			}
		}
	}
	else
	{
		QRegExp rx("(LOGIN|INSCRIPTION|MESSAGE)");
		rx.indexIn(str);

		int pos = rx.indexIn(str);
		if (pos > -1)
		{
			QString Info = rx.cap(1); // Info de ce qui est demander

			if (Info == "LOGIN")
			{
				QString Pseudo, MDP;
				QRegExp rxL("^([^\t]+) :: ([^\t]+) :: ([^\t]+) : ([^\t]+)$");
				if (rxL.indexIn(str) != -1)
				{
					Pseudo = rxL.cap(2);
					MDP = rxL.cap(4);

					QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
					db.setHostName("192.168.64.66");
					db.setDatabaseName("QT");
					db.setUserName("superuser");
					db.setPassword("superuser");
					QSqlQuery query(db);

					if (!db.open()) {
						ui.connectionStatusLabel->setText("Pb de connexion a la db");
					}
					else
					{
						QString requete = "SELECT * FROM User WHERE Pseudo = '" + Pseudo + "' AND MDP = '" + MDP + "'";
						retour = query.exec(requete);


						if (query.size() > 0) {
							obj->write("LOK");
						}
						else {
							obj->write("NLOK");
						}
					}
				}
			} else if (Info == "INSCRIPTION")
			{
				QString Pseudo, MDP;
				QRegExp rxL("^([^\t]+) :: ([^\t]+) :: ([^\t]+) : ([^\t]+)$");
				if (rxL.indexIn(str) != -1)
				{
					Pseudo = rxL.cap(2);
					MDP = rxL.cap(4);

					QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
					db.setHostName("192.168.64.66");
					db.setDatabaseName("QT");
					db.setUserName("superuser");
					db.setPassword("superuser");
					QSqlQuery query(db);

					if (!db.open()) {
						ui.connectionStatusLabel->setText("Pb de connexion a la db");
					}
					else
					{
						QString requete = "SELECT * FROM User WHERE Pseudo = '" + Pseudo + "' AND MDP = '" + MDP + "'";
						retour = query.exec(requete);

						if (query.size() == 0) {
							obj->write("IOK");
							QString requete = "INSERT INTO `User`(`Pseudo`, `MDP`) VALUES ('" + Pseudo + "','" + MDP + "')";
							retour = query.exec(requete);
						}
						else {
							obj->write("NIOK");
						}
					}
				}
				
			} else if (Info == "MESSAGE")
			{
				QString Pseudo, MSG;
				QRegExp rxL("^([^\t]+) :: ([^\t]+) :: ([^\t]+) : ([^\t]+)$");
				if (rxL.indexIn(str) != -1)
				{
					//Pseudo
					Pseudo = rxL.cap(2);
					//Message
					MSG = rxL.cap(4);
					//On fusionne le message avec le pseudo du random qui écrit
					MSG = Pseudo + " : " + MSG;

					//Connexion à BDD
					QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
					db.setHostName("192.168.64.66");
					db.setDatabaseName("QT");
					db.setUserName("superuser");
					db.setPassword("superuser");
					QSqlQuery query(db);


					if (!db.open()) {
						ui.connectionStatusLabel->setText("Pb de connexion a la db");
					}
					else
					{
						//Récupérer ID user qui a envoyé le message : 
						query.prepare("SELECT `ID` FROM `User` WHERE `Pseudo`='"+ Pseudo + "'");
						if (query.exec())
						{
							//Récupère le résultat de la requête
							query.next();
							QString IDUser = query.value(0).toString();	

							query.prepare("INSERT INTO `Message`(`IDUser`, `Content`) VALUES ('" + IDUser + "' , '" + MSG + "')");
							query.exec();


						}
						//On récupère le MSG100
						obj->write("MSG100");
					}
				}
			}
		}
	}
}