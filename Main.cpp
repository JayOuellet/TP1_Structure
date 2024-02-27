#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <unordered_map>

using namespace std;



class Cours {
public:
	std::string sigle;
	Cours* suivant;
};

class Etudiant {
public:
	std::string nom;
	Etudiant* suivant;
};

class Professeur {
public:
	int id, nbE;
	std::string nom;
	std::string prenom;
	Cours* listeCours;
	Etudiant* listeEtudiants;
	Professeur* suivant;
};


	template <typename Element> class DossierProfesseur 
	{
	public:
		Professeur* tete; // d�but de la liste cha�n�e
		DossierProfesseur() // Appele la fonction chargerProfesseur
		{
			tete = nullptr;
		}
		~DossierProfesseur() // D�truit de la liste cha�n�e existant en m�moire.
		{
			Professeur* courant;

			while (tete != nullptr) {
				courant = tete;
				tete = tete->suivant;
				delete courant;
			}
		}

		void chargerProfesseurs() // Construit la structure de la liste cha�n�e en m�moire �
		{
			ifstream Fichier("DonneesProfesseur.txt");
		

			if (!Fichier)
			{
				cout << "Impossible d'ouvrir le fichier de donnees des professeurs" << endl;
			}
			else
			{
			
				while (!Fichier.eof())
				{
					Professeur* firstP = nullptr;
					Professeur* lastP = nullptr;
					// Cours n
					{
						Professeur* profcourant = new Professeur;
						profcourant->listeCours = nullptr;
						Cours* firstC = nullptr;
						Cours* lastC = nullptr;
						Etudiant* firstE = nullptr;
						Etudiant* lastE = nullptr;

						Fichier >> profcourant->id >> profcourant->nom >> profcourant->prenom;
						/*cout << profcourant->id << endl << profcourant->nom << endl << profcourant->prenom << endl;*/ //id, nom, prenom
						while (true) // Cours n
						{
							Cours* nouveauC = new Cours;
							getline(Fichier >> ws, nouveauC->sigle);
							if (nouveauC->sigle == "#")
							{
								delete nouveauC; break;
							}
							if (firstC == nullptr)
							{
								firstC = lastC = nouveauC;
							}
							else
							{
								lastC->suivant = nouveauC;
								lastC = nouveauC;
							}
						}profcourant->listeCours = firstC;

						/*Cours* courantC = firstC;
						while (courantC != nullptr)
						{
							cout << courantC->sigle << endl;
							courantC = courantC->suivant;
						}*/

						while (true) // Cours n
						{
							profcourant->nbE = -1;
							profcourant->nbE++;
							Etudiant* nouveauE = new Etudiant;							
							getline(Fichier >> ws, nouveauE->nom);
							if (nouveauE->nom == "#")
							{
								delete nouveauE; break;
							}
							if (firstE == nullptr)
							{
								firstE = lastE = nouveauE;
							}
							else
							{
								lastE->suivant = nouveauE;
								lastE = nouveauE;
							}
						}profcourant->listeEtudiants = firstE;
						/*Etudiant* courantE = firstE;
						while (courantE != nullptr)
						{
							cout << courantE->nom << endl;
							courantE = courantE->suivant;
						}*/
						if (tete == nullptr)
						{
							tete = profcourant;
						}
						else
						{
							profcourant->suivant = tete;
							tete = profcourant;
						}
						
					}
				}						
			}				
		}					// partir du fichier donnees.txt
		void supprimer(int id)
		{
			Professeur* supprimer = tete;
			Professeur* safe = nullptr;
			while (supprimer != nullptr && supprimer->id != id) {
				safe = supprimer;
				supprimer = supprimer->suivant;
			}
			if (supprimer!=nullptr)
			{
				if (safe == nullptr)
				{
					tete = supprimer->suivant;
				}
				else
				{
					safe->suivant = supprimer->suivant;

				}
				cout << "Le professeur " << id << " a ete supprime" << endl;
				delete supprimer;
				cout << "------------------------" << endl;

			}
		}// supprime de la liste cha�n�e un professeur donn�
		void profil(int id) const
		{
			Professeur* courant = tete;			
			while (courant != nullptr && courant->id != id) {
				courant = courant->suivant;
			}
		
			if (courant != nullptr) {
				cout << "ID: " << courant->id << endl;
				cout << "Nom: " << courant->nom << endl;
				cout << "Prenom: " << courant->prenom << endl;

				cout << "Cours: ";
				Cours* courantC = courant->listeCours;
				while (courantC != nullptr) {
					cout << courantC->sigle << " ";
					courantC = courantC->suivant;
				}
				cout << endl;

				cout << "Etudiants: ";
				Etudiant* courantE = courant->listeEtudiants;
				while (courantE != nullptr) {
					cout << courantE->nom << " ";
					courantE = courantE->suivant;
				}
				cout << endl;

				cout << "------------------------" << endl;

				courant = courant->suivant;
			}
			else
			{
				cout << "Professeur introuvable" << endl;
				cout << "------------------------" << endl;
			}
		}											// affiche le profil du professeur identifi� pour id
		void afficherProfPlusEtudiants() const
		{
			Professeur* mostE = tete;
			int max = 0;
			while (mostE != nullptr)
			{
				int nbE=0;
				Etudiant* courant = mostE->listeEtudiants;
				while (courant !=nullptr)
				{
					nbE++;
					courant = courant->suivant;
				}
				if (max<nbE)
				{
					max = nbE;
				}
				mostE = mostE->suivant;
			}
			mostE = tete;
			cout << "Voici le ou les professeur aillant le plus d'eleves :" << endl;
			while (mostE != nullptr)
			{
				int nbE = 0;
				Etudiant* courant = mostE->listeEtudiants;
				while (courant != nullptr)
				{
					nbE++;
					courant = courant->suivant;
				}
				if (nbE == max)
				{
				
					cout << mostE->nom << ", " << mostE->prenom << endl;
				}
				mostE = mostE->suivant;
			}
			cout << "------------------------" << endl;
		}								// affiche les noms des professeur ayant le plus d��tudiants
		void afficherCoursPlusDemande() const // affiche les cours les plus demand�s de la liste
		{
			Professeur* profCourant = tete;
			unordered_map<string, int> coursMap;
			while (profCourant != nullptr)
			{
				Cours* courant = profCourant->listeCours; 
				while (courant !=nullptr)
				{
					coursMap[courant->sigle]++;
					courant = courant->suivant;
				}
				profCourant = profCourant->suivant;
			}
			vector<string> courslesplusdemandes;
			int max = 0;
			for (const auto& diffcours : coursMap)
			{
				if (diffcours.second > max)
				{
					max = diffcours.second;
					courslesplusdemandes = { diffcours.first };
				}
				else if (diffcours.second == max)
				{
					courslesplusdemandes.push_back(diffcours.first);
				}
			}
			cout << "Le ou les cours les plus en demandes sont : " << endl;
			for (const auto& lescours : courslesplusdemandes )
			{
				cout << lescours << endl;
			}
			cout << "------------------------" << endl;
		}
	};
	int main() 
	{
		DossierProfesseur<Professeur> dossier;
		
		ifstream Operations("Operations.txt");
		string ligne;
		char operation;
		int id;
		if (!Operations)
		{
			cout << "Le fichier operations ne S'est pas ouvert" << endl;
		}
		else
		{
			dossier.chargerProfesseurs();
			while (getline(Operations, ligne))
			{
				operation = ligne[0];
				switch (operation)
				{
				case '+':
					id = stoi(ligne.substr(1));
					dossier.profil(id);
					break;
				case '-':
					id = stoi(ligne.substr(1));
					dossier.supprimer(id);
					break;
				case '>':
					dossier.afficherProfPlusEtudiants();
					break;
				case '*':
					dossier.afficherCoursPlusDemande();
				default:
					break;
				}
			}
		}
		dossier.~DossierProfesseur();
		
		return 0;
	}