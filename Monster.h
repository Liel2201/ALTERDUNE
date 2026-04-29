#ifndef MONSTRE_H
#define MONSTRE_H

#include "Entite.h"
using namespace std;


class Monster : public Entity {
private:
    string categorie;
    int jaugeMercy;
    int objectifMercy;
    vector<string> idsActions;

public:
    Monster(string _nom, string _categorie, int _pvMax,
            int _attaque, int _defense, int _objectifMercy);

    void afficherInfo() const override;

    string obtenirCategorie() const;
    int obtenirJaugeMercy() const;
    int obtenirObjectifMercy() const;
    vector<string> obtenirIdsActions() const;

    void modifierMercy(int _delta);
    bool estEpargnable() const;

    void ajouterActionAct(string _idAction);

    virtual int obtenirNombreActions() const = 0;

    vector<string> obtenirActDisponibles() const;
};


class NormalMonster : public Monster {
public:
    NormalMonster(string _nom, int _pvMax, int _atk, int _def, int _objectifMercy);
    int obtenirNombreActions() const override; 
};

class MiniBossMonster : public Monster {
public:
    MiniBossMonster(string _nom, int _pvMax, int _atk, int _def, int _objectifMercy);
    int obtenirNombreActions() const override;
};

class BossMonster : public Monster {
public:
    BossMonster(string _nom, int _pvMax, int _atk, int _def, int _objectifMercy);
    int obtenirNombreActions() const override;
};

#endif