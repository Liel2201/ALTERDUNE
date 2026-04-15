#ifndef MONSTRE_H
#define MONSTRE_H

#include "Entite.h"

class Monster : public Entity {
private:
    std::string categorie;
    int jaugeMercy;
    int objectifMercy;
    std::vector<std::string> idsActions;

public:
    Monster(std::string _nom, std::string _categorie, int _pvMax,
            int _attaque, int _defense, int _objectifMercy);

    void afficherInfo() const override;

    std::string obtenirCategorie() const;
    int obtenirJaugeMercy() const;
    int obtenirObjectifMercy() const;
    std::vector<std::string> obtenirIdsActions() const;

    void modifierMercy(int _delta);
    bool estEpargnable() const;

    void ajouterActionAct(std::string _idAction);

    virtual int obtenirNombreActions() const = 0;

    std::vector<std::string> obtenirActDisponibles() const;
};


class NormalMonster : public Monster {
public:
    NormalMonster(std::string _nom, int _pvMax, int _atk, int _def, int _objectifMercy);
    int obtenirNombreActions() const override; 
};

class MiniBossMonster : public Monster {
public:
    MiniBossMonster(std::string _nom, int _pvMax, int _atk, int _def, int _objectifMercy);
    int obtenirNombreActions() const override;
};

class BossMonster : public Monster {
public:
    BossMonster(std::string _nom, int _pvMax, int _atk, int _def, int _objectifMercy);
    int obtenirNombreActions() const override;
};

#endif