#include "ClientQT.h"

ClientQT::ClientQT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	socket = new QTcpSocket(this);
	QObject::connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
	QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisonnected()));
	//Connection au serveur au lancement
	socket->connectToHost("127.0.0.1", 1234);
	//On cache la partit "chat" au lancement pour ne voir que le formulaire de connection
	ui.texteRecu->setVisible(false);
	ui.texteAEnvoyer->setVisible(false);
	ui.envoieMessage->setVisible(false);
}

//V�rifie si Utilisateur est Connect�
void ClientQT::onSocketConnected()
{
	ui.InfoConnection->setText("He Reconnected");
}

void ClientQT::onSocketDisonnected()
{
	ui.InfoConnection->setText("He Disconnected");
}

void ClientQT::envoieInfoConnexion()
{
	//On recupere ce qui a �t� saisi dans le formulaire
	QString Pseudo = ui.linePseudo->text();
	QString MdP = ui.lineMdP->text();

	//Convertion des donn�e en Array pour envoyer au serveur
	QByteArray PseudoEncode = Pseudo.toUtf8();
	QByteArray MdPEncode = MdP.toUtf8();

	if (socket->state() == QTcpSocket::ConnectedState)
	{
		//Envoie des infos entr� dans formulaire : 
		socket->write("Pseudo : "+ PseudoEncode);
		socket->write(" MdP : " + MdPEncode +"\n");
	}
	//Faire v�rification � partir de serveur, recevoir la reponse pour afficher ou non le chat
}

void ClientQT::autorisationConnection()
{
	//R�cuperer une info pour savoir si les infos envoyers on �t� accepter

}