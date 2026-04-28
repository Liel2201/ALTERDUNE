#ifndef GAME_H
#define GAME_H

#include "Utilitaires.h"
#include "Joueur.h"
#include "Monster.h"
#include "Objet.h"
#include "ActAction.h"
#include <map>

class BestiaryEntry {
private:
    std::string nomMonstre;
    std::string categorie;
    int pvMax;
    int attaque;
    int defense;
    bool aEteTue;

public:
    BestiaryEntry(std::string _nom, std::string _categorie,
                  int _pvMax, int _atk, int _def, bool _tue) {
        this->nomMonstre = _nom;
        this->categorie = _categorie;
        this->pvMax = _pvMax;
        this->attaque = _atk;
        this->defense = _def;
        this->aEteTue = _tue;
    }

    void afficher() const {
        std::string resultat;

        if (this->aEteTue) {
            resultat = "Tue";
        } else {
            resultat = "Epargne";
        }

        std::cout << "- " << this->nomMonstre
                  << " [" << this->categorie << "]"
                  << " | PV Max: " << this->pvMax
                  << " | ATK: " << this->attaque
                  << " | DEF: " << this->defense
                  << " | Resultat: " << resultat
                  << std::endl;
    }
};

class Game {
private:
    Player* joueurPtr;
    std::map<std::string, ActAction> catalogueActions;
    std::vector<Monster*> monstresDisponibles;
    std::vector<BestiaryEntry> bestiaire;
    std::mt19937 rng;

    void initialiserCatalogue();
    bool chargerFichierObjets(std::string chemin);
    bool chargerFichierMonstres(std::string chemin);
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