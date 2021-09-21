#pragma once
class Adminisrateur
{
private:




public:

	//fonction qui permlet de supprimer des message il prend en parametre l'id du message
	void DeleteMessage(int IDMessage);

	//fonction qui permet de cacher un Message il prend en parametre l'id du message
	void CacherMessage(int IDMessage);

	//function qui permet de surpimer des user il prend en paramettre l'id du user
	void DeleteUser(int IDUser);

	//function qui permet d'ajouter des user en admin il attend en parametre l'id user
	void AjoutAdmin(int IDUser);
};

