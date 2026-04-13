#ifndef MONSTRE_H
#define MONSTRE_H

#include "Entite.h"

// ============================================================
// Classe abstraite Monster : herite de Entity
// Les attributs sont PRIVATE (conformes a l'UML et au bareme
// encapsulation). On accede a tout via des getters.
// La methode virtuelle pure obtenirNombreActions() force
// chaque sous-classe a definir son propre nombre d'actions ACT.
// ============================================================
class Monster : public Entity {
private:
    std::string categorie;
    int jaugeMercy;
    int objectifMercy;
    std::vector<std::string> idsActions;

public:
    Monster(std::string _nom, std::string _categorie, int _pvMax,
            int _attaque, int _defense, int _objectifMercy);

    // Affichage (override de Entity)
    void afficherInfo() const override;

    // Accesseurs (getters)
    std::string obtenirCategorie() const;
    int obtenirJaugeMercy() const;
    int obtenirObjectifMercy() const;
    std::vector<std::string> obtenirIdsActions() const;

    // Systeme MERCY
    void modifierMercy(int _delta);
    bool estEpargnable() const;

    // Ajout d'une action ACT disponible pour ce monstre
    void ajouterActionAct(std::string _idAction);

    // Methode virtuelle pure : force les classes filles a definir le nombre d'actions
    // En C# : public abstract int ObtenirNombreActions();
    virtual int obtenirNombreActions() const = 0;

    // Retourne les actions disponibles limitees par obtenirNombreActions()
    // Utile pour le menu ACT en combat
    std::vector<std::string> obtenirActDisponibles() const;
};

// --- CLASSES DERIVEES ---

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