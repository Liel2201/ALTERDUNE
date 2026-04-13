#ifndef OBJET_H
#define OBJET_H

#include "Utilitaires.h"

// ============================================================
// Classe Item : objet de l'inventaire du joueur
// Charge depuis items.csv
// ============================================================
class Item {
private:
    std::string nom;
    std::string type;   // Ex: "HEAL"
    int valeur;         // Ex: HP rendus
    int quantite;

public:
    Item(std::string _nom, std::string _type, int _valeur, int _quantite);

    // Accesseurs
    std::string obtenirNom() const;
    std::string obtenirType() const;
    int obtenirValeur() const;
    int obtenirQuantite() const;

    // Retourne true si l'objet a pu etre utilise (quantite > 0)
    bool utiliser();
    void afficherDescription() const;
};

#endif