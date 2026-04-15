#ifndef JOUEUR_H
#define JOUEUR_H

#include "Entite.h"
#include "Objet.h"
#include <vector>

class Player : public Entity {
private:
    int tues;
    int epargnes;
    int victoires;
    std::vector<Item> inventaire;

public:
    Player(std::string _nom, int _pvMax, int _attaque, int _defense);

    void afficherInfo() const override;
    void ajouterVictoire(bool mortDuMonstre);
    int obtenirVictoires() const;
    int obtenirTues() const;
    int obtenirEpargnes() const;
    void ajouterObjet(Item nouvelObjet);
    void utiliserObjet(int index);
    void afficherInventaire() const;
    int obtenirTailleInventaire() const;
};

#endif