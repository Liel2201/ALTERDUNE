#ifndef ENTITE_H
#define ENTITE_H

#include "Utilitaires.h"

// ============================================================
// Classe abstraite Entity : classe mere pour Player et Monster
// En C# : public abstract class Entity { ... }
// ============================================================
class Entity {
private:
    std::string nom;
    int pv;
    int pvMax;
    int attaque;
    int defense;

public:
    Entity(std::string _nom, int _pvMax, int _attaque, int _defense);
    virtual ~Entity() {}

    // Accesseurs
    std::string obtenirNom() const;
    int obtenirPv() const;
    int obtenirPvMax() const;
    int obtenirAttaque() const;
    int obtenirDefense() const;

    bool estVivant() const;
    void subirDegats(int degats);

    // soigner() est dans Entity car pv est private ici
    // et conceptuellement, toute entite peut etre soignee
    void soigner(int montant);

    // Methode virtuelle pure
    virtual void afficherInfo() const = 0;
};

#endif