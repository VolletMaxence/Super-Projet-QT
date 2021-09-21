#pragma once
class message
{
private:
	int ID_message;
	char Date;
	char Contenu;
	int ID_Utilisateur;

public:
	//fonction qui permet de envoyer un message elle prend en paramettre char Contenu qui est le messgae et le IDCompte qui est le expediteur 
	void EnvoieMessage(char Contenu, int IDCompte);
};

