#include "Entite.h"

Entity::Entity(std::string _nom, int _pvMax, int _attaque, int _defense) {
    this->nom = _nom;
    this->pvMax = _pvMax;
    this->pv = _pvMax; // L'entité commence full life
    this->attaque = _attaque;
    this->defense = _defense;
}

Entity::~Entity() {
    // Rien de spécial à détruire ici pour l'instant
}

std::string Entity::obtenirNom() const {
    return this->nom;
}

int Entity::obtenirPv() const {
    return this->pv;
}

bool Entity::estVivant() const {
    return this->pv > 0;
}

void Entity::subirDegats(int _degats) {
    int degatsEffectifs = _degats - this->defense;
    if (degatsEffectifs < 0) degatsEffectifs = 0;

    this->pv -= degatsEffectifs;
    if (this->pv < 0) this->pv = 0;
}