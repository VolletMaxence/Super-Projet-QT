#include "websocketc.h"

websocketc::websocketc(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	socket = new QTcpSocket(this);
	QObject::connect(socket, SIGNAL(connected()), this, SLOT(TCPconnected())); //regarde sur on est connecter au server TCP
	QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(TCPdesconect())); //regarde si on est d�connecter au server TCP
}

void websocketc::ConnexionServerTcp() {
	QString ip = ui.IPtcp->text();
	QString port = ui.Porttcp->text();

	bool ok;
	int portAsInt = port.toInt(&ok);

	if (ok) {
		socket->connectToHost(ip, portAsInt);
	}
}

//affiche serveur TCP : coonecter si le websoket est bien connecter au server TCP
void websocketc::TCPconnected() {
	ui.statusTCPServer->setText("serveur TCP : connecter");
}

//affiche serveur TCP : d�connecter si le websoket est bien d�connecter au server TCP
void websocketc::TCPdesconect() {
	ui.statusTCPServer->setText("serveur TCP : deconnecter");
}

//meth�tode qui envoyer les information au serveur TCP
void websocketc::EnvoyerMess() {

	if (socket->state() == QTcpSocket::ConnectedState) { //on v�rifi dabort si on est connecter au server TCP pour pas envoyer le message dans le vide
														 //et que cala return une erreur
	socket -> write("test");
	}
}
