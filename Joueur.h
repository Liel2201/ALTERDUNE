#ifndef JOUEUR_H
#define JOUEUR_H

#include "Entite.h"
#include "Objet.h" // Indispensable pour connaitre Item
#include <vector>  // Indispensable pour utiliser std::vector

class Player : public Entity {
private:
    int tues;
    int epargnes;
    int victoires;
    std::vector<Item> inventaire; // L'inventaire qui manquait !

public:
    Player(std::string _nom, int _pvMax, int _attaque, int _defense);
    
    void afficherInfo() const override;
    void ajouterVictoire(bool mortDuMonstre);
    int obtenirVictoires() const;
    void soigner(int montant);
    
    // Ajout des méthodes pour gerer l'inventaire
    void ajouterObjet(Item nouvelObjet);
    void utiliserObjet(int index);
    void afficherInventaire() const;
};

#endif