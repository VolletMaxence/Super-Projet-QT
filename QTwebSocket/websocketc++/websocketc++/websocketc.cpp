#include "websocketc.h"

websocketc::websocketc(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	socket = new QTcpSocket(this);
	QObject::connect(socket, SIGNAL(connected()), this, SLOT(TCPconnected()));
	QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(TCPdesconect()));
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

void websocketc::TCPconnected() {
	ui.statusTCPServer->setText("serveur TCP : connecter");
}

void websocketc::TCPdesconect() {
	ui.statusTCPServer->setText("serveur TCP : deconnecter");
}