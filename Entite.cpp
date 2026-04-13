#include "Entite.h"

Entity::Entity(std::string _nom, int _pvMax, int _attaque, int _defense) {
    this->nom = _nom;
    this->pvMax = _pvMax;
    this->pv = _pvMax; // L'entité commence avec tous ses PV
    this->attaque = _attaque;
    this->defense = _defense;
}

// Implémentation des getters
std::string Entity::obtenirNom() const { return this->nom; }
int Entity::obtenirPv() const { return this->pv; }
int Entity::obtenirPvMax() const { return this->pvMax; }
int Entity::obtenirAttaque() const { return this->attaque; }
int Entity::obtenirDefense() const { return this->defense; }

bool Entity::estVivant() const {
    return this->pv > 0;
}

void Entity::subirDegats(int degats) {
    // Calcul classique des dégâts : Attaque - Défense
    int degatsReels = degats - this->defense;
    if (degatsReels < 0) degatsReels = 0; // On ne soigne pas si la défense est trop haute
    
    this->pv -= degatsReels;
    if (this->pv < 0) this->pv = 0; // Les PV ne peuvent pas être négatifs
}