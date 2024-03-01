#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <unordered_map>

using namespace std;

class Cours // Création de la liste chaînée pour les cours 
{
public:
	std::string sigle;
	Cours* suivant;
};

class Etudiant // Création de la liste chaînée pour les étudiants 
{
public:
	std::string nom;
	Etudiant* suivant;
};

class Professeur //Création de la liste chaîneée des professeurs comprenant leur identifiant, le nombre d'étudiant de ce probfesseur, son nom, prénom, cours et etudiants 
{
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
		Professeur* tete; // début de la liste chaînée
		DossierProfesseur() // Appele la fonction chargerProfesseur
		{
			tete = nullptr;
		}
		~DossierProfesseur() // Détruit de la liste chaînée existant en mémoire.
		{
			Professeur* courant; //pointe le noeud en cours

			while (tete != nullptr) //Si le noeud contient de l'information, la supprime
			{
				courant = tete; //prends l'information de la tete et la met dans courant
				tete = tete->suivant; //Mets l'information du noeud suivant dans la tete
				delete courant; //Supprime l'information de courant
			}
		}

		void chargerProfesseurs() // Construit la structure de la liste chaînée en mémoire à
		{
			ifstream Fichier("DonneesProfesseur.txt"); //Ouvrer le fichier .txt contenant l'information des professeurs
			if (!Fichier) // Si le fichier n'ouvre pas, affiche un message d'erreur à l'utilisateur
			{
				cout << "Impossible d'ouvrir le fichier de donnees des professeurs" << endl;
			}
			else //Si le fichier ouvre
			{
			
				while (!Fichier.eof()) // Si nous ne sommes pas à la fin du fichier de données .txt
				{
					Professeur* firstP = nullptr; //Variable temporaire pour le premier prénom
					Professeur* lastP = nullptr; //Variable temporaire pour le dernier prenom
					// Cours n
					{
						Professeur* profcourant = new Professeur; // Créer un nouvelle liste professeur selon avec la classe créée précédemment
						profcourant->listeCours = nullptr; //Pointeur sur la liste de cours de la classe
						Cours* firstC = nullptr;  //Variable temporaire pour le premier cours
						Cours* lastC = nullptr; //Variable temporaire pour le dernier cours
						Etudiant* firstE = nullptr; //Variable temporaire pour le premier etudiant
						Etudiant* lastE = nullptr; //Variable temporaire pour le dernier etudiant

						Fichier >> profcourant->id >> profcourant->nom >> profcourant->prenom; //Entre l'id, le nom et le prenom dans la liste chainée du professeur en cours
						/*cout << profcourant->id << endl << profcourant->nom << endl << profcourant->prenom << endl;*/ //id, nom, prenom
						while (true) // Cours n
						{
							Cours* nouveauC = new Cours; //Crée une nouvelle liste chainée cours
							getline(Fichier >> ws, nouveauC->sigle); //Prends la ligne du fichier qu'on place dans le noeud sigle
							if (nouveauC->sigle == "#") //Si le getline détecte le # qui délimite les catégories pendant le noeud de sigle, il enlève le # de la liste chainée et continue
							{
								delete nouveauC; break;
							}
							if (firstC == nullptr) //S'il n'y a pas de donnée pour le premier cours, alors c'est la fin de la liste
							{
								firstC = lastC = nouveauC;
							}
							else //s'il y a une donnée, alors on passe au suivant
							{
								lastC->suivant = nouveauC;
								lastC = nouveauC;
							}
						}profcourant->listeCours = firstC; //La donnée est placée dans la liste chainee

						/*Cours* courantC = firstC;
						while (courantC != nullptr)
						{
							cout << courantC->sigle << endl;
							courantC = courantC->suivant;
						}*/

						while (true) // Cours n
						{
							profcourant->nbE = -1; //La variable est mise à -1
							profcourant->nbE++; //On incrémente
							Etudiant* nouveauE = new Etudiant; //Créer un nouvelle liste étudiant selon avec la classe créée précédemment						
							getline(Fichier >> ws, nouveauE->nom); //On prend la ligne du fichier .txt qu'on place dans le noeud nom
							if (nouveauE->nom == "#") //Si le noeud placé est #, alors on l'enlève et on passe au prochain
							{
								delete nouveauE; break;
							}
							if (firstE == nullptr) //Si la donnée placée dans la liste est nul, alors on est à la fin de la présente liste chaînée
							{
								firstE = lastE = nouveauE;
							}
							else //Si la donnée est non nulle, alors on passe dans le noeud suivant
							{
								lastE->suivant = nouveauE;
								lastE = nouveauE;
							}
						}profcourant->listeEtudiants = firstE; // La donnée est placée dans la liste chainee
						/*Etudiant* courantE = firstE;
						while (courantE != nullptr)
						{
							cout << courantE->nom << endl;
							courantE = courantE->suivant;
						}*/
						if (tete == nullptr) //Si la tete est nulle, alors on a fini pour ce professeur
						{
							tete = profcourant;
						}
						else //Si la tete est non nulle, alors on passe à la prochaine donnée du fichier txt
						{
							profcourant->suivant = tete;
							tete = profcourant;
						}
						
					}
				}						
			}				
		}					// partir du fichier donnees.txt
		void supprimer(int id) //Supprimer la liste chaînée d'un professeur à l'id donné
		{
			Professeur* supprimer = tete; //Variable temporaire supprimer devient la tete
			Professeur* safe = nullptr; //Varibale temporaire safe est nul
			while (supprimer != nullptr && supprimer->id != id) { //Si supprimer n'est pas nul et le noeud id de supprimer n'est pas égal à id.
				safe = supprimer; //Alors safe prend l'information du noeud supprimer
				supprimer = supprimer->suivant; //Puis supprimer prend la valeur du suivant
			}
			if (supprimer!=nullptr) //Si supprimer et non nul  alors on fait les opérations suivantes
			{
				if (safe == nullptr) //Si safe est nul alors la tete devient le noeud suivant de supprimer
				{
					tete = supprimer->suivant;
				}
				else //Si safe a une valeur, alors sa valeur suivant prends celle de supprimer
				{
					safe->suivant = supprimer->suivant;

				}
				cout << "Le professeur " << id << " a ete supprime" << endl; //On afficher pour l'utilisateur quel id a été supprimé
				delete supprimer; //On supprime ensuite la liste chainée du professeur supprimer
				cout << "------------------------" << endl; //Mise en page

			}
		}// supprime de la liste chaînée un professeur donné
		void profil(int id) const //Afficher le profil d'un professeur à l'id donné
		{
			Professeur* courant = tete; //Variable de la valeur courante est égale à la tête			
			while (courant != nullptr && courant->id != id) { //Pendant qu'il y a une valeur dans courant et que l'id de courant n'est pas égal à l'id présent
				courant = courant->suivant; //Courant prend la valeur suivante
			}
		
			if (courant != nullptr) { //Si la valeur de courant est non nulle alors on affiche pour l'utilisateur l'id, le nom et le prénom du professeur
				cout << "ID: " << courant->id << endl;
				cout << "Nom: " << courant->nom << endl;
				cout << "Prenom: " << courant->prenom << endl;

				cout << "Cours: "; //On afficher le ou les cours
				Cours* courantC = courant->listeCours; //Création d'une variable temporaire qui est égale à la valeur lisste de cours de courant
				while (courantC != nullptr) { //Tant que CourantC possède une valeur non nulle, on affiche à l'utilisateur le sigle du cours puis on va au noeud suivant
					cout << courantC->sigle << " ";
					courantC = courantC->suivant;
				}
				cout << endl; //Change de ligne

				cout << "Etudiants: "; //Affiche les étudiants à l'utilisateur
				Etudiant* courantE = courant->listeEtudiants; //La valeur de la liste chainée d'étudiant courantE devient celle de la liste d'étudiant
				while (courantE != nullptr) { // Si la valeur que vient de prendre courantE est non nulle, alors on affiche cet étudiant, puis on prend le prochain noeud
					cout << courantE->nom << " "; 
					courantE = courantE->suivant;
				}
				cout << endl; //Change de ligne

				cout << "------------------------" << endl; //Mise en page

				courant = courant->suivant; //On passe au dossier du prochain professeur
			}
			else //Si l'id du professeur n'existe pas, alors on affiche un message d'erreur à l'utilisateur
			{
				cout << "Professeur introuvable" << endl;
				cout << "------------------------" << endl;
			}
		}											
		void afficherProfPlusEtudiants() const // Affiche les noms des professeur ayant le plus d’étudiants
		{
			Professeur* mostE = tete; //Crée une variable temporaire compatbilisant le nombre d'étudiant qui prend la valeur de la tete
			int max = 0; //Le max s'initialise à 0
			while (mostE != nullptr) //Si la profil mostE existe
			{
				int nbE=0; //alors on initialise le nombre d'étudiant à 0
				Etudiant* courant = mostE->listeEtudiants; //Courant prend donc la valeur du premier étudiant
				while (courant !=nullptr) //Si il y a bel et bien un nom d'étudiant
				{
					nbE++; //on incrémente le nombre d'étudiant pour ce professeur
					courant = courant->suivant; //Et on passe au prochain noeud d'étudiant
				}
				if (max<nbE) //Si le nombre d'étudiant est plus grand que le max
				{
					max = nbE; //alors ce max devient le plus grand nombre d'étudiant pour un professeur
				}
				mostE = mostE->suivant; //On passe au profil suivant
			}
			mostE = tete; //On remet la valeur de la tete dans mostE
			cout << "Voici le ou les professeur aillant le plus d'eleves :" << endl; //On affiche les noms des professeurs avec le plus d'élèves
			while (mostE != nullptr) //Si mostE a un profil de professeur qui n'est pas vide
			{
				int nbE = 0; //alors on initialise le nombre d'étudiant à 0
				Etudiant* courant = mostE->listeEtudiants; //Et on met la liste d'étudiants dans courant
				while (courant != nullptr) //S'il y a un étudiant, on incrémente et on passe au prochain étudiant
				{
					nbE++;
					courant = courant->suivant;
				}
				if (nbE == max) //Si c'est un des professeurs ou le professeur avec le plus d'étudiant, alors on affiche son nom et son prénom à l'utilisateur
				{
				
					cout << mostE->nom << ", " << mostE->prenom << endl;
				}
				mostE = mostE->suivant; //On passe au prochain professeur
			}
			cout << "------------------------" << endl; //Mise en page
		}								
		void afficherCoursPlusDemande() const // affiche les cours les plus demandés de la liste
		{
			Professeur* profCourant = tete; //Les informations de la tete sont mises dans profCourant
			unordered_map<string, int> coursMap; //Calcule le nombre de fois qu'un cours est mentionné
			while (profCourant != nullptr) //Si profCourant est non nul
			{
				Cours* courant = profCourant->listeCours; //
				while (courant !=nullptr) //Si courant est non nul
				{
					coursMap[courant->sigle]++; //On incrémente le compteur pour le cours vu
					courant = courant->suivant; //On prends l'information du prochain noeud
				}
				profCourant = profCourant->suivant; //On va ensuite au prochain professeur
			}
			vector<string> courslesplusdemandes; //On crée un vecteur pour les cours les plus demandés
			int max = 0; //Le max est initialisé à 0
			for (const auto& diffcours : coursMap) //Les différents cours sont analysés selon le nombre de fois qu'ils apparaissent
			{
				if (diffcours.second > max) //Si le nombre de fois qu'il apparait est plus grand que celui qui est le plus apparu à date, alors il devient le nouveau max et devient le cours le plus demandé
				{
					max = diffcours.second;
					courslesplusdemandes = { diffcours.first };
				}
				else if (diffcours.second == max) //S'il apparait un nombre de fois égal à celui qui est le plus apparu à date, alors il devient lui aussi un des cours les plus demandés
				{
					courslesplusdemandes.push_back(diffcours.first);
				}
			}
			cout << "Le ou les cours les plus en demandes sont : " << endl; //On affiche ensuite pour l'utilisateur les cours les plus demandés
			for (const auto& lescours : courslesplusdemandes ) //Les cours les plus demandés sont affichés uns par uns
			{
				cout << lescours << endl;
			}
			cout << "------------------------" << endl; //Mise en page 
		}
	};
	int main() //Initialisation du main
	{
		DossierProfesseur<Professeur> dossier; //Crée des varaibles selon la classe créée précédemment
		
		ifstream Operations("Operations.txt"); //Ouvre et prends l'information du fichier .txt des opérations
		string ligne; //variable de type string
		char operation; //variable de type char
		int id; //variable de type int
		if (!Operations) //Si le fichier .txt d'opérations n'ouvre pas, alors afficher un message d'erreur pour l'utilisateur
		{
			cout << "Le fichier operations ne s'est pas ouvert" << endl;
		}
		else
		{
			dossier.chargerProfesseurs();
			while (getline(Operations, ligne)) 
			{
				operation = ligne[0];
				switch (operation) //On prend en entrée l'opération que l'utilisateur veut effectuer
				{
				case '+': //le + affiche le dossier de l'id de professeur demandé
					id = stoi(ligne.substr(1));
					dossier.profil(id);
					break;
				case '-': //Le - supprime le dossier
					id = stoi(ligne.substr(1));
					dossier.supprimer(id);
					break;
				case '>': //Le > affiche les professeurs avec les plus d'étudiants
					dossier.afficherProfPlusEtudiants();
					break;
				case '*': //Le * affiche le cours le plus demandé
					dossier.afficherCoursPlusDemande();
				default:
					break; //On sort de la boucle
				}
			}
		}
		dossier.~DossierProfesseur();
		
		return 0; // retour à zéro
	}
