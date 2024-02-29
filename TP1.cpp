// (1) En-t�te
// J�r�my Ouellet
// TP1 Structure de Donnees
// 02/13/24
// 02/26/24
/**/ 

// (2) Clauses d'inclusion
#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <list>

using namespace std;

class Cours 
{
public:
    string nom;
    Cours* suivant;

    Cours(const string& n) : nom(n), suivant(nullptr) {}
};

class Etudiant
{
public:
    string nom;
    Etudiant* suivant;

    Etudiant(const string& n) : nom(n), suivant(nullptr) {}
};

class Professeur 
{
public:
    int id;
    string nom;
    string prenom;
    Cours* listeCours;
    Etudiant* listeEtudiants;
    Professeur* suivant;

    Professeur(int id, const string& nom, const string& prenom) : id(id), nom(nom), prenom(prenom), listeCours(nullptr), listeEtudiants(nullptr), suivant(nullptr) {}
};

class DossierProfesseur 
{
private:
    Professeur* debut;
public:
    DossierProfesseur() : debut(nullptr) {}

    ~DossierProfesseur() {
        // Lib�rer la m�moire allou�e pour les professeurs et leurs cours/�tudiants
        while (debut != nullptr) {
            Professeur* temp = debut;
            debut = debut->suivant;
            delete temp;
        }
    }

    void ajouterProfesseur(int id, const string& nom, const string& prenom, Cours* listeCours, Etudiant* listeEtudiants) {
        Professeur* nouveauProfesseur = new Professeur(id, nom, prenom);
        nouveauProfesseur->listeCours = listeCours;
        nouveauProfesseur->listeEtudiants = listeEtudiants;

        if (debut == nullptr) {
            debut = nouveauProfesseur;
        }
        else {
            Professeur* temp = debut;
            while (temp->suivant != nullptr) {
                temp = temp->suivant;
            }
            temp->suivant = nouveauProfesseur;
        }
    }

    void lireFichier(const string& nomFichier) {
        ifstream fichier(nomFichier);
        if (!fichier) {
            cout << "Impossible d'ouvrir le fichier " << nomFichier << endl;
            return;
        }

        int id;
        string nom, prenom;
        string ligne;
        while (getline(fichier, ligne)) {
            if (ligne == "#") { // S�parateur entre les professeurs
                continue;
            }

            id = stoi(ligne);
            getline(fichier, nom);
            getline(fichier, prenom);

            Cours* listeCours = nullptr;
            while (getline(fichier, ligne) && ligne != "#") {
                Cours* nouveauCours = new Cours(ligne);
                if (listeCours == nullptr) {
                    listeCours = nouveauCours;
                }
                else {
                    Cours* temp = listeCours;
                    while (temp->suivant != nullptr) {
                        temp = temp->suivant;
                    }
                    temp->suivant = nouveauCours;
                }
            }

            Etudiant* listeEtudiants = nullptr;
            while (getline(fichier, ligne) && ligne != "#") {
                Etudiant* nouvelEtudiant = new Etudiant(ligne);
                if (listeEtudiants == nullptr) {
                    listeEtudiants = nouvelEtudiant;
                }
                else {
                    Etudiant* temp = listeEtudiants;
                    while (temp->suivant != nullptr) {
                        temp = temp->suivant;
                    }
                    temp->suivant = nouvelEtudiant;
                }
            }

            ajouterProfesseur(id, nom, prenom, listeCours, listeEtudiants);
        }

        fichier.close();
    }

    void lireOperations(const string& nomFichier) {
        ifstream fichier(nomFichier);
        if (!fichier) {
            cout << "Impossible d'ouvrir le fichier " << nomFichier << endl;
            return;
        }

        string ligne;
        while (getline(fichier, ligne)) {
            if (ligne.empty()) continue;

            char operation = ligne[0];
            int id;
            switch (operation) {
            case '-':
                id = stoi(ligne.substr(2));
                supprimerProfesseur(id);
                break;
            case '+':
                id = stoi(ligne.substr(2));
                profilProfesseur(id);
                break;
            case '>':
                afficherProfPlusEtudiants();
                break;
            case '*':
                afficherCoursPlusDemande();
                break;
            default:
                cout << "Op�ration non reconnue : " << operation << endl;
                break;
            }
        }

        fichier.close();
    }

    void supprimerProfesseur(int id) {
        // Impl�mentez la suppression du professeur avec l'ID donn� ici
        cout << "Suppression du professeur avec l'ID " << id << endl;
    }

    void profilProfesseur(int id) {
        // Impl�mentez l'affichage du profil du professeur avec l'ID donn� ici
        cout << "Affichage du profil du professeur avec l'ID " << id << endl;
    }

    void afficherProfPlusEtudiants() {
        // Impl�mentez l'affichage du professeur avec le plus d'�tudiants ici
        cout << "Affichage du professeur avec le plus d'�tudiants" << endl;
    }

    void afficherCoursPlusDemande() {
        // Impl�mentez l'affichage du cours le plus demand� ici
        cout << "Affichage du cours le plus demand�" << endl;
    }
};

int main() {
    DossierProfesseur dossier;
    dossier.lireFichier("donnees.txt");
    dossier.lireOperations("operations.txt");
    return 0;
}