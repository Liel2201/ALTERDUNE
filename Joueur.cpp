#include "Joueur.h"

Player::Player(std::string _nom, int _pvMax, int _attaque, int _defense)
    : Entity(_nom, _pvMax, _attaque, _defense) {
    this->tues = 0;
    this->epargnes = 0;
    this->victoires = 0;
}

void Player::afficherInfo() const {
    std::cout << "=== JOUEUR : " << this->obtenirNom() << " ===" << std::endl;
    std::cout << "HP : " << this->obtenirPv() << " / " << this->obtenirPvMax() << std::endl;
    // CORRECTION : On utilise les méthodes obtenirAttaque() et obtenirDefense() !
    std::cout << "ATK: " << this->obtenirAttaque() << " | DEF: " << this->obtenirDefense() << std::endl;
    std::cout << "Victoires : " << this->victoires 
              << " (Tues: " << this->tues << ", Epargnes: " << this->epargnes << ")" << std::endl;
}

void Player::ajouterVictoire(bool mortDuMonstre) {
    this->victoires++;
    if (mortDuMonstre) this->tues++;
    else this->epargnes++;
}

int Player::obtenirVictoires() const {
    return this->victoires;
}

void Player::soigner(int montant) {
    // A coder plus tard (Combat)
}

// L'implémentation de l'ajout d'objet
void Player::ajouterObjet(Item nouvelObjet) {
    this->inventaire.push_back(nouvelObjet);
}

void Player::utiliserObjet(int index) {
    // A coder plus tard (Combat)
}

// L'implémentation de l'affichage de l'inventaire
void Player::afficherInventaire() const {
    std::cout << "\n--- INVENTAIRE ---" << std::endl;
    if (inventaire.empty()) {
        std::cout << "(Vide)" << std::endl;
        return;
    }
    for (size_t i = 0; i < inventaire.size(); i++) {
        std::cout << "- ";
        inventaire[i].afficherDescription();
    }
}