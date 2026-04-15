#ifndef ENTITE_H
#define ENTITE_H

#include "Utilitaires.h"

class Entity {
private:
    std::string nom;
    int pv;
    int pvMax;
    int attaque;
    int defense;

public:
    Entity(std::string _nom, int _pvMax, int _attaque, int _defense);
    virtual ~Entity() {}

    std::string obtenirNom() const;
    int obtenirPv() const;
    int obtenirPvMax() const;
    int obtenirAttaque() const;
    int obtenirDefense() const;
    bool estVivant() const;
    void subirDegats(int degats);
    void soigner(int montant);
    virtual void afficherInfo() const = 0;
};

#endif