#ifndef GAME_H
#define GAME_H

#include "Utilitaires.h"
#include "Joueur.h"
#include "Monster.h"
#include "Objet.h"
#include "ActAction.h"
#include <map>
using namespace std;


class BestiaryEntry {
private:
    string nomMonstre;
    string categorie;
    int pvMax;
    int attaque;
    int defense;
    bool aEteTue;

public:
    BestiaryEntry(string _nom, string _categorie, int _pvMax, int _atk, int _def, bool _tue) {
        this->nomMonstre = _nom;
        this->categorie = _categorie;
        this->pvMax = _pvMax;
        this->attaque = _atk;
        this->defense = _def;
        this->aEteTue = _tue;
    }

    void afficher() const {
        string resultat;

        if (this->aEteTue) {
            resultat = "Tue";
        } else {
            resultat = "Epargne";
        }

        cout << "- " << this->nomMonstre
                  << " [" << this->categorie << "]"
                  << " | PV Max: " << this->pvMax
                  << " | ATK: " << this->attaque
                  << " | DEF: " << this->defense
                  << " | Resultat: " << resultat
                  << endl;
    }
};

class Game {
private:
    Player* joueurPtr;
    map<string, ActAction> catalogueActions;
    vector<Monster*> monstresDisponibles;
    vector<BestiaryEntry> bestiaire;
    mt19937 rng;
    bool partieTerminee;

    void initialiserCatalogue();
    bool chargerFichierObjets(string chemin);
    bool chargerFichierMonstres(string chemin);
    Monster* creerCopieMonstre(Monster* modele);
    void ouvrirInventaire();
    void afficherMenuPrincipal();
    void demarrerCombat();
    void afficherStatistiques();
    void afficherBestiaire();
    bool verifierFinDePartie() const;
    void afficherFin() const;

public:
    Game();
    ~Game();

    void lancer();
};

#endif