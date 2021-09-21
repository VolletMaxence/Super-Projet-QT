#include "ClientQT.h"


ClientQT::ClientQT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	socket = new QTcpSocket(this);
	QObject::connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
	QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisonnected()));
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
	//Connection au serveur au lancement

	//Configuration Local
	//socket->connectToHost("127.0.0.1", 1234);
	//Configuration Serveur
	socket->connectToHost("192.168.64.107", 1234);

	//On cache la partit "chat" au lancement pour ne voir que le formulaire de connection
	ui.texteRecu->setVisible(false);
	ui.texteAEnvoyer->setVisible(false);
	ui.envoieMessage->setVisible(false);
	ui.buttonDeconnexion->setVisible(false);
	ui.labelBienvenueX->setVisible(false);

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

	//On stock le pseudo entré dans l'objet
	QString save_Pseudo = PseudoEncode;

	if (socket->state() == QTcpSocket::ConnectedState)
	{
		//Envoie des infos entré dans formulaire : 
		socket->write("Pseudo : "+ PseudoEncode);
		socket->write(" MdP : " + MdPEncode +"\n");
	}
	//Faire vérification à partir de serveur, recevoir la reponse pour afficher ou non le chat
}

void ClientQT::onSocketReadyRead()
{
	//Récuperer une info pour savoir si les infos envoyers on été accepter
	QByteArray infoMessageRecu = socket->read(socket->bytesAvailable());
	QString str(infoMessageRecu);

	//Si l'info recu correspond a celle qui est attendu pour connexion : 
	//Lancement methode pour connecter
	if (str == "LOK" || str == "NLOK")
	{
		ClientQT::receptionInfoLogin();
	}
	else if (str == "MOK" || str == "NMOK")
	{
		ClientQT::receptionInfoMessage();
	}

}

void ClientQT::deconnexion()
{
	//Afficher le chat
	ui.texteRecu->setVisible(false);
	ui.texteAEnvoyer->setVisible(false);
	ui.envoieMessage->setVisible(false);
	ui.buttonDeconnexion->setVisible(false);

	//Cacher le Formulaire
	ui.connectVous->setVisible(true);
	ui.labelPseudo->setVisible(true);
	ui.labelMdP->setVisible(true);
	ui.linePseudo->setVisible(true);
	ui.lineMdP->setVisible(true);
	ui.envoieInfoLogin->setVisible(true);
	ui.labelBienvenueX->setVisible(true);

}

void ClientQT::receptionInfoLogin()
{
	//UserName stocker avant : on l effacera si c est pas le bon (?)
	if (str == "LOK")
	{
		//On remplace ce qu'il y a dans le labelBienvenueX :
		ui.labelBienvenueX->setText("Bienvenue %s.", save_Pseudo);

		//Afficher le chat
		ui.texteRecu->setVisible(true);
		ui.texteAEnvoyer->setVisible(true);
		ui.envoieMessage->setVisible(true);
		ui.buttonDeconnexion->setVisible(true);
		ui.labelBienvenueX->setVisible(false);


		//Cacher le Formulaire
		ui.connectVous->setVisible(false);
		ui.labelPseudo->setVisible(false);
		ui.labelMdP->setVisible(false);
		ui.linePseudo->setVisible(false);
		ui.lineMdP->setVisible(false);
		ui.envoieInfoLogin->setVisible(false);

		//Remplir le Chat

	}
	else if (str == "NLOK")
	{
		//Affichage message d erreur
	}
}

void ClientQT::receptionInfoMessage()
{
	//Si l'info recu correspond a celle attendu pour reception message : 
	//Lancement de methode pour actualiser la messagerie


	//Système de mot banni ?
	//Affichage de message d erreur
}