#include "Joueur.h"

// Appel du constructeur de la classe mère (Entity) via la liste d'initialisation
Player::Player(std::string _nom, int _pvMax, int _attaque, int _defense) 
    : Entity(_nom, _pvMax, _attaque, _defense) 
{
    this->tues = 0;
    this->epargnes = 0;
    this->victoires = 0;
}

void Player::afficherInfo() const {
    std::cout << "=== JOUEUR : " << this->nom << " ===" << std::endl;
    std::cout << "HP : " << this->pv << " / " << this->pvMax << std::endl; 
    std::cout << "ATK: " << this->attaque << " | DEF: " << this->defense << std::endl;
    std::cout << "Victoires : " << this->victoires << " (Tués: " << this->tues 
              << ", Épargnés: " << this->epargnes << ")" << std::endl; 
}

void Player::ajouterVictoire(bool _mortDuMonstre) {
    this->victoires++;
    if (_mortDuMonstre) {
        this->tues++;
    } else {
        this->epargnes++;
    }
}

int Player::obtenirVictoires() const {
    return this->victoires;
}

void Player::ajouterObjet(Item _nouvelObjet) {
    this->inventaire.push_back(_nouvelObjet);
}

void Player::afficherInventaire() const {
    std::cout << "--- INVENTAIRE ---" << std::endl;
    if (this->inventaire.empty()) {
        std::cout << "Inventaire vide." << std::endl;
        return;
    }
    for (const Item& obj : this->inventaire) {
        obj.afficherDescription();
    }
}