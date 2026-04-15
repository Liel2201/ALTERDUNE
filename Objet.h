#ifndef OBJET_H
#define OBJET_H

#include "Utilitaires.h"

class Item {
private:
    std::string nom;
    std::string type;   
    int valeur;         
    int quantite;

public:
    Item(std::string _nom, std::string _type, int _valeur, int _quantite);

    std::string obtenirNom() const;
    std::string obtenirType() const;
    int obtenirValeur() const;
    int obtenirQuantite() const;

    bool utiliser();
    void afficherDescription() const;
};

#endif