#include "TCP_Serveur.h"
#include <qdebug.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
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

	QRegExp rx("\\b(LOGIN|INSCRIPTION|MSG100)\\b");
	rx.indexIn(str);  


	//QRegExp rx("^(.+) :: Pseudo :: (.+) MDP : (.+)");
	//QStringList test = rx.capturedTexts();
	//qDebug() << test[0];

	int pos = rx.indexIn(str);
	if (pos > -1) 
	{
		QString Info = rx.cap(1); // Info de ce qui est demander

		//QString Pseudo = rx.cap(2); 
		//QString MdP = rx.cap(3);


		if (Info == "LOGIN")
		{
			//QRegExp rxL("^LOGIN :: Pseudo ::([^\t]+)MDP :([^\t]+)");

			QString Pseudo, MDP;
			QRegExp rxL("^([^\t]+) :: ([^\t]+) :: ([^\t]+) : ([^\t]+)$");
			if (rxL.indexIn(str) != -1) 
			{
				Pseudo = rxL.cap(2);
				MDP = rxL.cap(4);

				QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
				db.setHostName("192.168.64.66");
				db.setDatabaseName("QT");
				db.setUserName("root");
				db.setPassword("root");
				bool ok = db.open();
				QSqlQuery query(db);

				query.exec("SELECT Pseudo, MDP FROM User");
				QString requete = "SELECT * FROM User WHERE Pseudo = '" + Pseudo + "' AND MDP = '" + MDP + "'";
				retour = query.exec(requete);

				if (retour) {
					obj->write("LOK");
				}
				else {
					obj->write("NLOK");
				}
			}

		}
		else if (rx.exactMatch("INSCRIPTION"))
		{

		}
		else
		{
			//Envoyer les 100 derniers messages
		}
	}

	//Récupérer chaque groupe en String
	//Vérifier le premier pour envoyer aprés


	// Pseudo :: (.+) MDP : (.+) = e qui donne group Pseudo / mdp
	// ^LOGIN :: 

}
/*
void TCP_Serveur::Login()
{


}
*/