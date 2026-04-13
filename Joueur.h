#ifndef JOUEUR_H
#define JOUEUR_H

#include "Entite.h"
#include "Objet.h"
#include <vector>

// ============================================================
// Classe Player : herite de Entity
// En C# : public class Player : Entity { ... }
// soigner() est herite de Entity, pas besoin de le redeclarer
// ============================================================
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

    // Gestion de l'inventaire
    void ajouterObjet(Item nouvelObjet);
    void utiliserObjet(int index);
    void afficherInventaire() const;
    int obtenirTailleInventaire() const;
};

#endif