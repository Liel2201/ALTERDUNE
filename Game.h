#ifndef GAME_H
#define GAME_H

#include "Utilitaires.h"
#include "Joueur.h"
#include "Monster.h"
#include "Objet.h"
#include "ActAction.h"
#include <map>

// Structure simple pour le bestiaire (comme sur ton UML)
struct BestiaryEntry {
    std::string nomMonstre;
    std::string categorie;
    bool aEteTue;
    void afficher() const {
        std::cout << "- " << nomMonstre << " [" << categorie << "] : " 
                  << (aEteTue ? "Elimine" : "Epargne") << std::endl;
    }
};

class Game {
private:
    Player* joueurPtr;
    std::map<std::string, ActAction> catalogueActions;
    std::vector<Monster*> monstresDisponibles;
    std::vector<BestiaryEntry> bestiaire;

    void initialiserCatalogue();
    bool chargerFichierObjets(std::string chemin);
    bool chargerFichierMonstres(std::string chemin);
    
    void afficherMenuPrincipal();
    void demarrerCombat();
    void afficherStatistiques();
    void afficherBestiaire();

public:
    Game();
    ~Game();
    
    void lancer(); // Point d'entrée de la boucle principale
};

#endif