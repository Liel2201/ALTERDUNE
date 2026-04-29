#include "Joueur.h"
using namespace std;


Player::Player(string _nom, int _pvMax, int _attaque, int _defense)
    : Entity(_nom, _pvMax, _attaque, _defense) {
    this->tues = 0;
    this->epargnes = 0;
    this->victoires = 0;
}

void Player::afficherInfo() const {
    cout << "=== JOUEUR : " << this->obtenirNom() << " ===" << endl;
    cout << "PV  : " << this->obtenirPv() << " / " << this->obtenirPvMax() << endl;
    cout << "ATK : " << this->obtenirAttaque()
              << " | DEF : " << this->obtenirDefense() << endl;
    cout << "Victoires : " << this->victoires << " / 10"
              << " (Tues: " << this->tues
              << ", Epargnes: " << this->epargnes << ")" << endl;
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
        cout << "Index invalide !" << endl;
        return false;
    }

    Item& item = this->inventaire[index];

    if (item.obtenirQuantite() <= 0) {
        cout << "Vous n'avez plus de " << item.obtenirNom() << " !" << endl;
        return false;
    }

    if (item.obtenirType() == "HEAL") {
        item.utiliser();
        this->soigner(item.obtenirValeur());

        cout << "Vous utilisez " << item.obtenirNom()
                  << " et recuperez " << item.obtenirValeur() << " PV !" << endl;

        cout << "PV : " << this->obtenirPv()
                  << "/" << this->obtenirPvMax() << endl;

        return true;
    }

    cout << "Cet objet ne peut pas etre utilise." << endl;
    return false;
}

void Player::afficherInventaire() const {
    cout << "\n--- INVENTAIRE ---" << endl;

    if (this->inventaire.empty()) {
        cout << "(Vide)" << endl;
        return;
    }

    for (int i = 0; i < (int)this->inventaire.size(); i++) {
        cout << "  [" << (i + 1) << "] ";
        this->inventaire[i].afficherDescription();
    }
}

int Player::obtenirTailleInventaire() const {
    return (int)this->inventaire.size();
}