#pragma once
class user
{
	private:

		int ID;
		char Pseudo;
		char Mots_de_passe;
		int Status;
		int Administrateur;
		char Avatar;
		char Dernière_connexion;

	public:
		
		//fonction pour permet a lutilisateur de se conneter elle prend en parametre le Pseudo et le mots de passe elle return rien
		void Connexion(char Pseudo, char Mdp);
		//fonction qui permet a l'utilisateur de se deconnecter elle prend rien en parametre et elle return rien
		void Deconnexion();
		//fonction qui permet a l'utilisateur de sincrire elle prend en parametre un pseudo et un mdp elle returne rien
		void Creation(char Pseudo, char Mdp);

};

