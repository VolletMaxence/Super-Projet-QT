#include "ClientQT.h"
#include "qscrollbar.h"


ClientQT::ClientQT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	socket = new QTcpSocket(this);
	QObject::connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
	QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisonnected()));
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
	//Connection au serveur au lancement

	void setWindowIcon(const QIcon &icon);
	QIcon windowIcon();

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
	ui.Shellos->setVisible(false);
	ui.Caterpie->setVisible(false);

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
	ui.buttonRetour->setVisible(false);

}

//Vérifie si Utilisateur est Connecté
void ClientQT::onSocketConnected()
{
	//Cache le boutton de connexion au serveur car on est connecté de base
	ui.buttonConnexionServeur->setVisible(false);

	ui.connectVous->setVisible(true);
	ui.labelPseudo->setVisible(true);
	ui.labelMdP->setVisible(true);
	ui.linePseudo->setVisible(true);
	ui.lineMdP->setVisible(true);
	ui.envoieInfoLogin->setVisible(true);
	ui.buttonRedirectCreationUser->setVisible(true);
}

//Affiche le boutton pour se connecter si le serveur se coupe
void ClientQT::onSocketDisonnected()
{
	//On c est deco : on caceh tout
	ui.texteRecu->setVisible(false);
	ui.texteAEnvoyer->setVisible(false);
	ui.envoieMessage->setVisible(false);
	ui.buttonDeconnexion->setVisible(false);
	ui.labelBienvenueX->setVisible(false);
	ui.Shellos->setVisible(false);
	ui.Caterpie->setVisible(false);

	ui.connectVous->setVisible(false);
	ui.labelPseudo->setVisible(false);
	ui.labelMdP->setVisible(false);
	ui.linePseudo->setVisible(false);
	ui.lineMdP->setVisible(false);
	ui.envoieInfoLogin->setVisible(false);
	ui.buttonRedirectCreationUser->setVisible(false);


	ui.lineMdPInscription->setVisible(false);
	ui.linePseudoInscription->setVisible(false);
	ui.inscriptionCompte->setVisible(false);
	ui.buttonRetour->setVisible(false);
	
	ui.buttonConnexionServeur->setVisible(true);

	ui.infoServeur->setText("Le serveur ne fonctionne pas, cliquer sur le boutton pour reessayer.");


}

//Connexion au serveur
void ClientQT::connexionServeur()
{
	//socket->connectToHost("127.0.0.1", 1234);
	socket->connectToHost("192.168.64.107", 4321);

	ui.infoServeur->setText("");
	
	ui.envoieInfoLogin->setEnabled(true);
	ui.envoieInfoLogin->setEnabled(true);
}

//Envoie de ce qui a été stocker dans le formulaire de connexion
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
	ClientQT::save_Pseudo = Pseudo;

	if (socket->state() == QTcpSocket::ConnectedState)
	{
		//Envoie des infos entré dans formulaire : 
		socket->write("LOGIN :: Pseudo :: "+ PseudoEncode +" :: MDP : "+MdPEncode);
	}
	//Faire vérification à partir de serveur, recevoir la reponse pour afficher ou non le chat
}

//Envoie de ce qui a été stocker dans le formulaire d'inscription
void ClientQT::envoieInscription()
{
	//On retire le boutton pour éviter le surplus d'info
	ui.envoieInfoLogin->setEnabled(false);

	//On recupere ce qui a été saisi dans le formulaire
	QString InscriptionPseudo = ui.linePseudoInscription->text();
	QString InscriptionMdP = ui.lineMdPInscription->text();

	//Convertion des donnée en Array pour envoyer au serveur
	QByteArray InscriptionPseudoEncode = InscriptionPseudo.toUtf8();
	QByteArray InscriptionMdPEncode = InscriptionMdP.toUtf8();

	//On stock le pseudo entré dans l'objet
	QString save_Pseudo = InscriptionPseudoEncode;

	if (socket->state() == QTcpSocket::ConnectedState)
	{
		//Envoie des infos entré dans formulaire : 
		socket->write("INSCRIPTION :: Pseudo :: " + InscriptionPseudoEncode + " :: MDP : " + InscriptionMdPEncode);
		//socket->write("INSCRIPTION " + InscriptionPseudoEncode + " " + InscriptionMdPEncode);
	}
}

//Envoie ce qui à été inserer dans la messagerie pour l envoyer au serveur
void ClientQT::envoieMessage()
{
	//On recupere ce qu'on a dans le message : 
	QString MessageEntree = ui.texteAEnvoyer->text();
	QByteArray MessageEntreeEncode = MessageEntree.toUtf8();

	//On recupere le pseudo qui est connecter :
	QByteArray PseudoStock = ClientQT::save_Pseudo.toUtf8();

	//Si on est bien connecter : 
	if (socket->state() == QTcpSocket::ConnectedState)
	{
		//Envoie des infos entré dans formulaire : 
		socket->write("MESSAGE :: Pseudo :: "+ PseudoStock + " :: MESSAGE : " + MessageEntreeEncode + " \n");
	}

	//Effacer ce qu'il y avait dans la zone de texte : pas de spam
	ui.texteAEnvoyer->clear();

	ui.connectVous->setVisible(false);
	ui.labelPseudo->setVisible(false);
	ui.labelMdP->setVisible(false);
	ui.linePseudo->setVisible(false);
	ui.lineMdP->setVisible(false);
	ui.envoieInfoLogin->setVisible(false);
	ui.buttonRedirectCreationUser->setVisible(false);
}

//Reception et trie de tout message envoyer par le serveur
void ClientQT::onSocketReadyRead()
{
	//Récuperer une info pour savoir si les infos envoyers on été accepter
	QByteArray infoMessageRecu = socket->read(socket->bytesAvailable());
	QString str(infoMessageRecu);
	const char* strChar = str.toStdString().c_str();

	//Si l'info recu correspond a celle qui est attendu pour connexion : 
	//Lancement methode pour connecter
	if (str == "LOK" || str == "NLOK")
	{
		ClientQT::receptionInfoLogin(str);
	}
	else if (str == "IOK" || str == "NIOK")
	{
		ClientQT::receptionInfoInscription(str);
	}
	else if (str == "MSG100")
	{
		ClientQT::priseCentDernierMessage();
	}
	else
	{
		ClientQT::receptionInfoMessage(str);
	}

}

//Déconnexion : retour au formulaire de connexion
void ClientQT::deconnexion()
{
	//Cacher le chat
	ui.texteRecu->setVisible(false);
	ui.texteAEnvoyer->setVisible(false);
	ui.envoieMessage->setVisible(false);
	ui.buttonDeconnexion->setVisible(false);
	ui.labelBienvenueX->setVisible(false);
	ui.Shellos->setVisible(false);
	ui.Caterpie->setVisible(false);

	//Afficehr le Formulaire
	ui.connectVous->setVisible(true);
	ui.labelPseudo->setVisible(true);
	ui.labelMdP->setVisible(true);
	ui.linePseudo->setVisible(true);
	ui.lineMdP->setVisible(true);
	ui.envoieInfoLogin->setVisible(true);
	ui.buttonRedirectCreationUser->setVisible(true);

}

//Envoie vers formulaire inscription
void ClientQT::redirectInscription()
{
	//Cacher le Formulaire Connection
	ui.connectVous->setText("Inscrivez-vous");

	ui.linePseudo->setVisible(false);
	ui.lineMdP->setVisible(false);
	ui.envoieInfoLogin->setVisible(false);
	ui.labelBienvenueX->setVisible(false);
	ui.buttonRedirectCreationUser->setVisible(false);
	//Affichage Formulaire Inscription
	ui.lineMdPInscription->setVisible(true);
	ui.linePseudoInscription->setVisible(true);
	ui.inscriptionCompte->setVisible(true);
	ui.buttonRetour->setVisible(true);
	ui.labelErreur->setText("");
}

//Retour vers formulaire de Connexion sans s'inscrir
void ClientQT::retourConnexion()
{
	//Cacher le Formulaire Connection
	ui.connectVous->setText("Connectez-vous");
	ui.envoieInfoLogin->setVisible(true);
	ui.buttonRedirectCreationUser->setVisible(true);
	ui.lineMdP->setVisible(true);
	ui.linePseudo->setVisible(true);
	//Affichage Formulaire Inscription
	ui.lineMdPInscription->setVisible(false);
	ui.linePseudoInscription->setVisible(false);
	ui.inscriptionCompte->setVisible(false);
	ui.buttonRetour->setVisible(false);
	ui.labelErreur->setText("");
}

//Reception des info du login depuis le Serveur
void ClientQT::receptionInfoLogin(QString str)
{
	//UserName stocker avant : on l effacera si c est pas le bon (?)
	if (str == "LOK")
	{
		//Récuperer le pseudo stocker :
		QByteArray PseudoStock = ClientQT::save_Pseudo.toUtf8();

		//On remplace ce qu'il y a dans le labelBienvenueX :
		ui.labelBienvenueX->setText("Bienvenue "+ PseudoStock);

		//Afficher le chat
		ui.texteRecu->setVisible(true);
		ui.texteAEnvoyer->setVisible(true);
		ui.envoieMessage->setVisible(true);
		ui.buttonDeconnexion->setVisible(true);
		ui.labelBienvenueX->setVisible(true);
		ui.Shellos->setVisible(true);
		ui.Caterpie->setVisible(true);

		//Cacher le Formulaire
		ui.connectVous->setText("Connectez-vous");
		ui.connectVous->setVisible(false);
		ui.labelPseudo->setVisible(false);
		ui.labelMdP->setVisible(false);
		ui.linePseudo->setVisible(false);
		ui.lineMdP->setVisible(false);
		ui.envoieInfoLogin->setVisible(false);
		ui.buttonRedirectCreationUser->setVisible(false);
		ui.labelErreur->setText("");
		ui.labelErreur->setVisible(false);

		//Remplir le Chat (c est deugeulasse, putain de zoophile)
		ClientQT::priseCentDernierMessage();
	}
	else if (str == "NLOK")
	{
		//Affichage message d erreur
		ui.labelErreur->setText("Ce compte n'existe pas.");
	}

	//ON remet en place le boutton pour recommencer au cas où il le faudrait
	ui.envoieInfoLogin->setEnabled(true);

}

//Reception des info de messages depuis le Serveur
void ClientQT::receptionInfoMessage(QString str)
{
	//recuperer les messages envoyer par le monsieur
	ui.texteRecu->setText(str);
	ui.texteRecu->verticalScrollBar()->setValue(ui.texteRecu->verticalScrollBar()->maximum());


	//texteRecu
}

//Reception des info d'inscription depuis le Serveur
void ClientQT::receptionInfoInscription(QString str)
{
	//Si l'info recu correspond a celle attendu pour reception message : 
	//Lancement de methode pour actualiser la messagerie
	if (str == "IOK")
	{
		//Cacher Formulaire Inscription
		ui.lineMdPInscription->setVisible(false);
		ui.linePseudoInscription->setVisible(false);
		ui.inscriptionCompte->setVisible(false);
		ui.buttonRetour->setVisible(false);


		//Afficher formulaire Connexion
		ui.connectVous->setVisible(true);
		ui.envoieInfoLogin->setVisible(true);
		ui.buttonRedirectCreationUser->setVisible(true);
		ui.linePseudo->setVisible(true);
		ui.lineMdP->setVisible(true);
		ui.labelErreur->setText("");
	}
	else if (str == "NIOK")
	{
		//Affichage message d erreur
		ui.labelErreur->setText("Ce compte existe déjà.");
	}

	ui.envoieInfoLogin->setEnabled(true);
}

//Demande des 100 derniers messages stocker en base
void ClientQT::priseCentDernierMessage()
{
	//Mettre la scrollbar au maximum


	//On demande les 100 derniers messages depuis la BDD
	socket->write("MSG100");
}