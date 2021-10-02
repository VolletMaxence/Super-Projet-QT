#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_websocketc.h"
#include <qtcpsocket.h>

class websocketc : public QMainWindow
{
    Q_OBJECT

public:
    websocketc(QWidget *parent = Q_NULLPTR);

private:
    Ui::websocketcClass ui;
	QTcpSocket * socket;

public slots: 
	void ConnexionServerTcp();
	void TCPconnected();
	void TCPdesconect();

};
