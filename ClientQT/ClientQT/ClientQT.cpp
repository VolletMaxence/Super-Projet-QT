#include "ClientQT.h"

ClientQT::ClientQT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	socket = new QTcpSocket(this);
	QObject::connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
	QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisonnected()));
	socket->connectToHost("127.0.0.1", 1234);
}

//Vérifie si Utilisateur est Connecté
void ClientQT::onSocketConnected()
{
	ui.InfoConnection->setText("He Reconnected");
}

void ClientQT::onSocketDisonnected()
{
	ui.InfoConnection->setText("He Disconnected");
}