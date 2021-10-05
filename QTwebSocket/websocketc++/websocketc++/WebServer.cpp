#include "WebServer.h"
#include <QWebSocket>


WebServer::WebServer(QObject *parent) : QWebSocketServer("serverWebsocketqt", QWebSocketServer::NonSecureMode, parent)
{
	mSocket = NULL;
	connect(this, SIGNAL(newConnection()), this, SLOT(nouvelleCo()));

}
 //fonction qui autorise la connection au server websocket
void WebServer::nouvelleCo() {
	mSocket = nextPendingConnection();
	connect(mSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(NeauveauMess(QString)));
}

void WebServer::NeauveauMess(const QString &message) {
	emit envoiMess(message);
}