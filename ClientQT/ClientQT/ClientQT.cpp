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
	socket->connectToHost("192.168.64.107", 4321);

	//On cache la partit "chat" au lancement pour ne voir que le formulaire de connection
	ui.texteRecu->setVisible(false);
	ui.texteAEnvoyer->setVisible(false);
	ui.envoieMessage->setVisible(false);
	ui.buttonDeconnexion->setVisible(false);
	ui.labelBienvenueX->setVisible(false);
	//On cache formulaire de connexion car on est pas sur d'être connecter
	ui.connectVous->setVisible(false);
	ui.labelPseudo->setVisible(false);
	ui.labelMdP->setVisible(false);
	ui.linePseudo->setVisible(false);
	ui.lineMdP->setVisible(false);
	ui.envoieInfoLogin->setVisible(false);
	ui.buttonRedirectCreationUser->setVisible(false);
	//On cache formulaire d'inscription car on en a pas besoin
	ui.lineMdPInscription->setVisible(false);
	ui.linePseudoInscription->setVisible(false);
	ui.inscriptionCompte->setVisible(false);
}

//Vérifie si Utilisateur est Connecté
void ClientQT::onSocketConnected()
{
	ui.InfoConnection->setText("He Reconnected");
	//Cache le boutton de connexion au serveur car on est connecté de base
	ui.buttonConnexionServeur->setVisible(false);
	/*
	ui.texteRecu->setVisible(false);
	ui.texteAEnvoyer->setVisible(false);
	ui.envoieMessage->setVisible(false);
	ui.buttonDeconnexion->setVisible(false);
	ui.labelBienvenueX->setVisible(false);
	*/
	ui.connectVous->setVisible(true);
	ui.labelPseudo->setVisible(true);
	ui.labelMdP->setVisible(true);
	ui.linePseudo->setVisible(true);
	ui.lineMdP->setVisible(true);
	ui.envoieInfoLogin->setVisible(true);
	ui.buttonRedirectCreationUser->setVisible(true);

}

void ClientQT::onSocketDisonnected()
{
	//Cacher tout : on c est déco lol
	ui.texteRecu->setVisible(false);
	ui.texteAEnvoyer->setVisible(false);
	ui.envoieMessage->setVisible(false);
	ui.buttonDeconnexion->setVisible(false);

	ui.connectVous->setVisible(false);
	ui.labelPseudo->setVisible(false);
	ui.labelMdP->setVisible(false);
	ui.linePseudo->setVisible(false);
	ui.lineMdP->setVisible(false);
	ui.envoieInfoLogin->setVisible(false);
	ui.labelBienvenueX->setVisible(false);
	ui.buttonRedirectCreationUser->setVisible(false);
	

	ui.InfoConnection->setText("He Disconnected");

	ui.buttonConnexionServeur->setVisible(true);

	ui.infoServeur->setText("Le serveur ne fonctionne pas, cliquer sur le boutton pour reessayer.");

}

void ClientQT::connexionServeur()
{
	socket->connectToHost("192.168.64.107", 4321);
}

void ClientQT::envoieInfoConnexion()
{
	//On retire le boutton pour éviter le surplus d'info
	ui.envoieInfoLogin->setEnabled(false);

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
		socket->write("LOGIN :: Pseudo : "+ PseudoEncode + " MdP : " + MdPEncode + "\n");
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
		//ClientQT::receptionInfoLogin();
	}
	else if (str == "MOK" || str == "NMOK")
	{
		//ClientQT::receptionInfoMessage();
	}

}

void ClientQT::deconnexion()
{
	//Cacher le chat
	ui.texteRecu->setVisible(false);
	ui.texteAEnvoyer->setVisible(false);
	ui.envoieMessage->setVisible(false);
	ui.buttonDeconnexion->setVisible(false);

	//Afficehr le Formulaire
	ui.connectVous->setVisible(true);
	ui.labelPseudo->setVisible(true);
	ui.labelMdP->setVisible(true);
	ui.linePseudo->setVisible(true);
	ui.lineMdP->setVisible(true);
	ui.envoieInfoLogin->setVisible(true);
	ui.labelBienvenueX->setVisible(true);
	ui.buttonRedirectCreationUser->setVisible(true);
}


void ClientQT::redirectInscription()
{
	//Cacher le Formulaire Connection
	ui.connectVous->setVisible(false);
	ui.labelPseudo->setVisible(false);
	ui.labelMdP->setVisible(false);
	ui.linePseudo->setVisible(false);
	ui.lineMdP->setVisible(false);
	ui.envoieInfoLogin->setVisible(false);
	ui.labelBienvenueX->setVisible(false);
	ui.buttonRedirectCreationUser->setVisible(false);
	//Affichage Formulaire Inscription
	ui.lineMdPInscription->setVisible(true);
	ui.linePseudoInscription->setVisible(true);
	ui.inscriptionCompte->setVisible(true);
}

void ClientQT::retourConnexion()
{
	//Cacher le Formulaire Connection
	ui.connectVous->setVisible(true);
	ui.labelPseudo->setVisible(true);
	ui.labelMdP->setVisible(true);
	ui.linePseudo->setVisible(true);
	ui.lineMdP->setVisible(true);
	ui.envoieInfoLogin->setVisible(true);
	ui.labelBienvenueX->setVisible(true);
	ui.buttonRedirectCreationUser->setVisible(true);
	//Affichage Formulaire Inscription
	ui.lineMdPInscription->setVisible(false);
	ui.linePseudoInscription->setVisible(false);
	ui.inscriptionCompte->setVisible(false);
}

void ClientQT::envoieInscription()
{
	//On retire le boutton pour éviter le surplus d'info
	ui.envoieInfoLogin->setEnabled(false);

	//On recupere ce qui a été saisi dans le formulaire
	QString InscriptionPseudo = ui.linePseudo->text();
	QString InscriptionMdP = ui.lineMdP->text();

	//Convertion des donnée en Array pour envoyer au serveur
	QByteArray InscriptionPseudoEncode = InscriptionPseudo.toUtf8();
	QByteArray InscriptionMdPEncode = InscriptionMdP.toUtf8();

	//On stock le pseudo entré dans l'objet
	QString save_Pseudo = InscriptionPseudoEncode;

	if (socket->state() == QTcpSocket::ConnectedState)
	{
		//Envoie des infos entré dans formulaire : 
		socket->write("LOGIN :: Pseudo : " + InscriptionPseudoEncode + " MdP : " + InscriptionMdPEncode + "\n");
	}
}
/* En attente de reception message
void ClientQT::receptionInfoLogin()
{
	//UserName stocker avant : on l effacera si c est pas le bon (?)
	if (str == "LOK")
	{
		//On remplace ce qu'il y a dans le labelBienvenueX :
		ui.labelBienvenueX->setText("Bienvenue "+ save_Pseudo +".");

		//Afficher le chat
		ui.texteRecu->setVisible(true);
		ui.texteAEnvoyer->setVisible(true);
		ui.envoieMessage->setVisible(true);
		ui.buttonDeconnexion->setVisible(true);
		ui.labelBienvenueX->setVisible(true);


		//Cacher le Formulaire
		ui.connectVous->setVisible(false);
		ui.labelPseudo->setVisible(false);
		ui.labelMdP->setVisible(false);
		ui.linePseudo->setVisible(false);
		ui.lineMdP->setVisible(false);
		ui.envoieInfoLogin->setVisible(false);
		ui.buttonRedirectCreationUser->setVisible(false);


		//Remplir le Chat

	}
	else if (str == "NLOK")
	{
		//Affichage message d erreur
	}

	//ON remet en place le boutton pour recommencer au cas où il le faudrait
	ui.envoieInfoLogin->setEnabled(true);

}

void ClientQT::receptionInfoMessage()
{
	//Si l'info recu correspond a celle attendu pour reception message : 
	//Lancement de methode pour actualiser la messagerie


	//Système de mot banni ?
	//Affichage de message d erreur
}

*/