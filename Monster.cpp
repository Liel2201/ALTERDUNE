#include "Monster.h"

// ============================================================
// Constructeur de Monster
// ============================================================
Monster::Monster(std::string _nom, std::string _categorie, int _pvMax,
                 int _attaque, int _defense, int _objectifMercy)
    : Entity(_nom, _pvMax, _attaque, _defense)
{
    this->categorie = _categorie;
    this->jaugeMercy = 0;
    this->objectifMercy = _objectifMercy;
}

// ============================================================
// Accesseurs (getters)
// ============================================================
std::string Monster::obtenirCategorie() const {
    return this->categorie;
}

int Monster::obtenirJaugeMercy() const {
    return this->jaugeMercy;
}

int Monster::obtenirObjectifMercy() const {
    return this->objectifMercy;
}

std::vector<std::string> Monster::obtenirIdsActions() const {
    return this->idsActions;
}

// ============================================================
// Affichage
// ============================================================
void Monster::afficherInfo() const {
    std::cout << "[" << this->categorie << "] " << this->obtenirNom()
              << " | PV: " << this->obtenirPv() << "/" << this->obtenirPvMax()
              << " | MERCY: " << this->jaugeMercy << "/" << this->objectifMercy
              << std::endl;
}

// ============================================================
// Systeme MERCY
// ============================================================
void Monster::modifierMercy(int _delta) {
    this->jaugeMercy += _delta;
    this->jaugeMercy = std::clamp(this->jaugeMercy, 0, this->objectifMercy);
}

bool Monster::estEpargnable() const {
    return this->jaugeMercy >= this->objectifMercy;
}

// ============================================================
// Gestion des actions ACT
// ============================================================
void Monster::ajouterActionAct(std::string _idAction) {
    this->idsActions.push_back(_idAction);
}

// Retourne uniquement les N premieres actions valides
// selon la categorie (2 pour NORMAL, 3 pour MINIBOSS, 4 pour BOSS)
std::vector<std::string> Monster::obtenirActDisponibles() const {
    std::vector<std::string> disponibles;
    int nombre = this->obtenirNombreActions();
    for (int i = 0; i < nombre && i < (int)this->idsActions.size(); i++) {
        if (this->idsActions[i] != "-") {
            disponibles.push_back(this->idsActions[i]);
        }
    }
    return disponibles;
}

// ============================================================
// Classes derivees (polymorphisme)
// ============================================================
NormalMonster::NormalMonster(std::string _nom, int _pvMax, int _atk, int _def, int _objectifMercy)
    : Monster(_nom, "NORMAL", _pvMax, _atk, _def, _objectifMercy) {}

int NormalMonster::obtenirNombreActions() const {
    return 2;
}

MiniBossMonster::MiniBossMonster(std::string _nom, int _pvMax, int _atk, int _def, int _objectifMercy)
    : Monster(_nom, "MINIBOSS", _pvMax, _atk, _def, _objectifMercy) {}

int MiniBossMonster::obtenirNombreActions() const {
    return 3;
}

BossMonster::BossMonster(std::string _nom, int _pvMax, int _atk, int _def, int _objectifMercy)
    : Monster(_nom, "BOSS", _pvMax, _atk, _def, _objectifMercy) {}

int BossMonster::obtenirNombreActions() const {
    return 4;
}