#ifndef OBJET_H
#define OBJET_H

#include "Utilitaires.h"
using namespace std;


class Item {
private:
    string nom;
    string type;   
    int valeur;         
    int quantite;

public:
    Item(string _nom, string _type, int _valeur, int _quantite);

    string obtenirNom() const;
    string obtenirType() const;
    int obtenirValeur() const;
    int obtenirQuantite() const;

    bool utiliser();
    void afficherDescription() const;
};

#endif