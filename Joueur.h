#ifndef JOUEUR_H
#define JOUEUR_H

#include "Entite.h"
#include "Objet.h"

// Player hérite publiquement de Entity
class Player : public Entity {
private:
    std::vector<Item> inventaire;
    int tues;
    int epargnes;
    int victoires;

public:
    // Constructeur
    Player(std::string _nom, int _pvMax, int _attaque, int _defense);

    // Override de la méthode virtuelle pure de Entity
    void afficherInfo() const override;

    // Méthodes spécifiques au joueur
    void ajouterVictoire(bool _mortDuMonstre);
    int obtenirVictoires() const;
    
    void ajouterObjet(Item _nouvelObjet);
    void afficherInventaire() const;
};

#endif