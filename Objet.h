#ifndef OBJET_H
#define OBJET_H

#include "Utilitaires.h"

class Item {
private:
    std::string nom;
    std::string type; // Ex: "HEAL"
    int valeur;       // Ex: HP rendus
    int quantite;

public:
    Item(std::string _nom, std::string _type, int _valeur, int _quantite);
    
    std::string obtenirNom() const;
    int obtenirQuantite() const;
    
    // Retourne true si l'objet a pu être utilisé (quantité > 0)
    bool utiliser(); 
    void afficherDescription() const;
};

#endif