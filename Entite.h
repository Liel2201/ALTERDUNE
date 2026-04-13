#ifndef ENTITE_H
#define ENTITE_H

#include "Utilitaires.h"

// Classe de base abstraite représentant toute entité vivante dans le jeu.
class Entity {
protected: // accessible par les classes filles (Player, Monster)
    std::string nom;
    int pv;
    int pvMax;
    int attaque;
    int defense;

public:
    Entity(std::string _nom, int _pvMax, int _attaque, int _defense);

    // Destructeur virtuel obligatoire en C++ pour le polymorphisme
    virtual ~Entity();

    std::string obtenirNom() const;
    int obtenirPv() const;
    bool estVivant() const;

    virtual void subirDegats(int _degats);

    // Méthode virtuelle pure : rend la classe abstraite
    virtual void afficherInfo() const = 0;
};

#endif