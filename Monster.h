#ifndef MONSTRE_H
#define MONSTRE_H

#include "Entite.h"

// Classe abstraite Monster
class Monster : public Entity {
protected:
    std::string categorie;
    int jaugeMercy;
    int objectifMercy;
    std::vector<std::string> idsActions;

public:
    Monster(std::string _nom, std::string _categorie, int _pvMax, int _attaque, int _defense, int _objectifMercy);

    void afficherInfo() const override;
    
    // Gestion du système MERCY
    void modifierMercy(int _delta);
    bool estEpargnable() const;
    
    // Ajout d'une action ACT disponible pour ce monstre
    void ajouterActionAct(std::string _idAction);

    // Méthode virtuelle pure : force les classes filles à définir le nombre d'actions
    virtual int obtenirNombreActions() const = 0; 
};

// --- CLASSES DÉRIVÉES ---

class NormalMonster : public Monster {
public:
    NormalMonster(std::string _nom, int _pvMax, int _atk, int _def, int _objectifMercy);
    int obtenirNombreActions() const override; // Retournera 2
};

class MiniBossMonster : public Monster {
public:
    MiniBossMonster(std::string _nom, int _pvMax, int _atk, int _def, int _objectifMercy);
    int obtenirNombreActions() const override; // Retournera 3
};

class BossMonster : public Monster {
public:
    BossMonster(std::string _nom, int _pvMax, int _atk, int _def, int _objectifMercy);
    int obtenirNombreActions() const override; // Retournera 4
};

#endif