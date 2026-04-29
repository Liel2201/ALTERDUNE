#ifndef JOUEUR_H
#define JOUEUR_H

#include "Entite.h"
#include "Objet.h"
#include <vector>
using namespace std;


class Player : public Entity {
private:
    int tues;
    int epargnes;
    int victoires;
    vector<Item> inventaire;

public:
    Player(string _nom, int _pvMax, int _attaque, int _defense);

    void afficherInfo() const override;
    void ajouterVictoire(bool mortDuMonstre);
    int obtenirVictoires() const;
    int obtenirTues() const;
    int obtenirEpargnes() const;
    void ajouterObjet(Item nouvelObjet);
    bool utiliserObjet(int index);
    void afficherInventaire() const;
    int obtenirTailleInventaire() const;
};

#endif