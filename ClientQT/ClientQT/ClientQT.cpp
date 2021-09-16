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

//Vérifie si Utilisateur est Connecté
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
	//On recupere ce qui a été saisi dans le formulaire
	QString Pseudo = ui.linePseudo->text();
	QString MdP = ui.lineMdP->text();

	//Convertion des donnée en Array pour envoyer au serveur
	QByteArray PseudoEncode = Pseudo.toUtf8();
	QByteArray MdPEncode = MdP.toUtf8();

	if (socket->state() == QTcpSocket::ConnectedState)
	{
		//Envoie des infos entré dans formulaire : 
		socket->write("Pseudo : "+ PseudoEncode);
		socket->write(" MdP : " + MdPEncode +"\n");
	}
	//Faire vérification à partir de serveur, recevoir la reponse pour afficher ou non le chat
}

void ClientQT::autorisationConnection()
{
	//Récuperer une info pour savoir si les infos envoyers on été accepter

}