#include "Entite.h"

Entity::Entity(std::string _nom, int _pvMax, int _attaque, int _defense) {
    this->nom = _nom;
    this->pvMax = _pvMax;
    this->pv = _pvMax;
    this->attaque = _attaque;
    this->defense = _defense;
}

std::string Entity::obtenirNom() const { return this->nom; }
int Entity::obtenirPv() const { return this->pv; }
int Entity::obtenirPvMax() const { return this->pvMax; }
int Entity::obtenirAttaque() const { return this->attaque; }
int Entity::obtenirDefense() const { return this->defense; }

bool Entity::estVivant() const {
    return this->pv > 0;
}

void Entity::subirDegats(int degats) {
    this->pv -= degats;
    if (this->pv < 0) this->pv = 0;
}

// Restaure des PV sans depasser pvMax
void Entity::soigner(int montant) {
    this->pv += montant;
    if (this->pv > this->pvMax) {
        this->pv = this->pvMax;
    }
}