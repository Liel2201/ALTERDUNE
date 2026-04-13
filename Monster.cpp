#include "Monster.h"

// --- Implémentation de Monster (Classe de base) ---
Monster::Monster(std::string _nom, std::string _categorie, int _pvMax, int _attaque, int _defense, int _objectifMercy)
    : Entity(_nom, _pvMax, _attaque, _defense)
{
    this->categorie = _categorie;
    this->jaugeMercy = 0;
    this->objectifMercy = _objectifMercy;
}

void Monster::afficherInfo() const {
    std::cout << "[" << this->categorie << "] " << this->obtenirNom()
              << " | HP: " << this->obtenirPv() << "/" << this->obtenirPvMax()
              << " | MERCY: " << this->jaugeMercy << "/" << this->objectifMercy << std::endl;
}

void Monster::modifierMercy(int _delta) {
    this->jaugeMercy += _delta;
    // Bornage de Mercy [cite: 58]
    this->jaugeMercy = std::clamp(this->jaugeMercy, 0, this->objectifMercy);
}

bool Monster::estEpargnable() const {
    return this->jaugeMercy >= this->objectifMercy; 
}
void Monster::ajouterActionAct(std::string _idAction) {
    this->idsActions.push_back(_idAction);
}

// --- Implémentation des classes filles ---

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