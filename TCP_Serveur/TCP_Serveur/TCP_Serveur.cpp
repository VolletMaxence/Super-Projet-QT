#include "TCP_Serveur.h"
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlQuery>

TCP_Serveur::TCP_Serveur(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	socket = new QTcpSocket(this);
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
	server = new QTcpServer(this);
	QObject::connect(server, SIGNAL(newConnection()), this, SLOT(onServerNewConnection()));
	ConnectionDataBase();
	server->listen(QHostAddress::AnyIPv4, 4321);
}

void TCP_Serveur::ConnectionDataBase()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("192.168.64.66");
	db.setDatabaseName("QT");
	db.setUserName("root");
	db.setPassword("root");
	bool ok = db.open();
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
}

void TCP_Serveur::Login()
{
	QTcpSocket * obj = qobject_cast<QTcpSocket*>(sender());
	QByteArray data = obj->read(obj->bytesAvailable());
	QString str(data);

	QRegExp rx("[a - zA - Z] + [a - z]\w +");

	QString strr(rx);

	if(rx == "LOGIN"){

	}
}