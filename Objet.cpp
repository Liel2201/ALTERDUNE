#include "Objet.h"

Item::Item(std::string _nom, std::string _type, int _valeur, int _quantite) {
    this->nom = _nom;
    this->type = _type;
    this->valeur = _valeur;
    this->quantite = _quantite;
}

std::string Item::obtenirNom() const {
    return this->nom;
}

std::string Item::obtenirType() const {
    return this->type;
}

int Item::obtenirValeur() const {
    return this->valeur;
}

int Item::obtenirQuantite() const {
    return this->quantite;
}

bool Item::utiliser() {
    if (this->quantite > 0) {
        this->quantite--;
        return true;
    } else {
        return false;
    }
}

void Item::afficherDescription() const {
    std::cout << "- " << this->nom << " (" << this->type << " : +"
              << this->valeur << " PV) [x" << this->quantite << "]" << std::endl;
}