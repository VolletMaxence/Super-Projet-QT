#include "websocketc.h"
#include "WebServer.h"

websocketc::websocketc(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	socket = new QTcpSocket(this);
	Qtwebserver = new WebServer(this);
	Qtwebserver->listen(QHostAddress::Any, 4321);
	QObject::connect(socket, SIGNAL(connected()), this, SLOT(TCPconnected())); //regarde sur on est connecter au server TCP
	QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(TCPdesconect())); //regarde si on est déconnecter au server TCP
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(RidefMess())); //regarde sur un nouveau message arrive depuis le tcp server
	connect(Qtwebserver, SIGNAL(envoiMess(QString)), this, SLOT(envoiMess(QString))); //regarde si un client du web socket envoyer un message ver le tcp server
}

//fonction qui permet au websocket server de se connecter au tcp server
void websocketc::ConnexionServerTcp() {
	QString ip = ui.IPtcp->text();
	QString port = ui.Porttcp->text();

	bool ok;
	int portAsInt = port.toInt(&ok);

	if (ok) {
		socket->connectToHost(ip, portAsInt);
	}
}

//fonction qui permet au websocket server de se déconnecter sur server tcp
void websocketc::disco() {
	socket->disconnectFromHost();
}

//affiche serveur TCP : coonecter si le websoket est bien connecter au server TCP
void websocketc::TCPconnected() {
	ui.statusTCPServer->setText("serveur TCP : connecter");
}

//affiche serveur TCP : déconnecter si le websoket est bien déconnecter au server TCP
void websocketc::TCPdesconect() {
	ui.statusTCPServer->setText("serveur TCP : deconnecter");
}

//methétode qui envoyer les information au serveur TCP
void websocketc::EnvoyerMess() {

	if (socket->state() == QTcpSocket::ConnectedState) { //on vérifi dabort si on est connecter au server TCP pour pas envoyer le message dans le vide
														 //et que cala return une erreur
	socket -> write("test\n");
	}
}

//fonction qui li les message arrivent du tcp server pour les envoyer au websocket
void websocketc::RidefMess() {

	QByteArray mess = socket->read(socket->bytesAvailable());
	QString str(mess);
	ui.statusMes->setText("des nouveau message son dispo (" + mess + ")");
	ui.listWidget->addItem(mess);
}

//fonction qui permet de d'envoyer les message vener du websocket client au tcp server
void websocketc::envoiMess(const QString &message) {
	ui.listWidget->addItem(message);
	//convertir le message venent du websocket client pour l'envoyer 
	QString myString(message +"\n");
	QByteArray inUtf8 = myString.toUtf8();
	const char *messageConverti = inUtf8.constData();

	socket->write(messageConverti);
}
