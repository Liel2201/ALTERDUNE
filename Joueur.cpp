#include "Joueur.h"

Player::Player(std::string _nom, int _pvMax, int _attaque, int _defense)
    : Entity(_nom, _pvMax, _attaque, _defense) {
    this->tues = 0;
    this->epargnes = 0;
    this->victoires = 0;
}

void Player::afficherInfo() const {
    std::cout << "=== JOUEUR : " << this->obtenirNom() << " ===" << std::endl;
    std::cout << "PV  : " << this->obtenirPv() << " / " << this->obtenirPvMax() << std::endl;
    std::cout << "ATK : " << this->obtenirAttaque()
              << " | DEF : " << this->obtenirDefense() << std::endl;
    std::cout << "Victoires : " << this->victoires << " / 10"
              << " (Tues: " << this->tues
              << ", Epargnes: " << this->epargnes << ")" << std::endl;
}

void Player::ajouterVictoire(bool mortDuMonstre) {
    this->victoires++;

    if (mortDuMonstre) {
        this->tues++;
    } else {
        this->epargnes++;
    }
}

int Player::obtenirVictoires() const {
    return this->victoires;
}

int Player::obtenirTues() const {
    return this->tues;
}

int Player::obtenirEpargnes() const {
    return this->epargnes;
}

void Player::ajouterObjet(Item nouvelObjet) {
    this->inventaire.push_back(nouvelObjet);
}

bool Player::utiliserObjet(int index) {
    if (index < 0 || index >= (int)this->inventaire.size()) {
        std::cout << "Index invalide !" << std::endl;
        return false;
    }

    Item& item = this->inventaire[index];

    if (item.obtenirQuantite() <= 0) {
        std::cout << "Vous n'avez plus de " << item.obtenirNom() << " !" << std::endl;
        return false;
    }

    if (item.obtenirType() == "HEAL") {
        item.utiliser();
        this->soigner(item.obtenirValeur());

        std::cout << "Vous utilisez " << item.obtenirNom()
                  << " et recuperez " << item.obtenirValeur() << " PV !" << std::endl;

        std::cout << "PV : " << this->obtenirPv()
                  << "/" << this->obtenirPvMax() << std::endl;

        return true;
    }

    std::cout << "Cet objet ne peut pas etre utilise." << std::endl;
    return false;
}

void Player::afficherInventaire() const {
    std::cout << "\n--- INVENTAIRE ---" << std::endl;

    if (this->inventaire.empty()) {
        std::cout << "(Vide)" << std::endl;
        return;
    }

    for (int i = 0; i < (int)this->inventaire.size(); i++) {
        std::cout << "  [" << (i + 1) << "] ";
        this->inventaire[i].afficherDescription();
    }
}

int Player::obtenirTailleInventaire() const {
    return (int)this->inventaire.size();
}