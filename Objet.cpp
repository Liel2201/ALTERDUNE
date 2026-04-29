#include "Objet.h"
using namespace std;


Item::Item(string _nom, string _type, int _valeur, int _quantite) {
    this->nom = _nom;
    this->type = _type;
    this->valeur = _valeur;
    this->quantite = _quantite;
}

string Item::obtenirNom() const {
    return this->nom;
}

string Item::obtenirType() const {
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
    cout << "- " << this->nom << " (" << this->type << " : +"
              << this->valeur << " PV) [x" << this->quantite << "]" << endl;
}