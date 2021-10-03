#include <QWebSocketServer>
#pragma once

class WebServer : public QWebSocketServer
{
	Q_OBJECT
public:
	explicit WebServer(QObject *parent = 0);

signals:
	void envoiMess(QString);

private slots:
	void nouvelleCo();
	void NeauveauMess(const QString &message);
private:
	QWebSocket *mSocket;
};

