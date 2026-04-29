#include "Monster.h"
using namespace std;


Monster::Monster(string _nom, string _categorie, int _pvMax,
                 int _attaque, int _defense, int _objectifMercy)
    : Entity(_nom, _pvMax, _attaque, _defense)
{
    this->categorie = _categorie;
    this->jaugeMercy = 0;
    this->objectifMercy = _objectifMercy;
}

string Monster::obtenirCategorie() const {
    return this->categorie;
}

int Monster::obtenirJaugeMercy() const {
    return this->jaugeMercy;
}

int Monster::obtenirObjectifMercy() const {
    return this->objectifMercy;
}

vector<string> Monster::obtenirIdsActions() const {
    return this->idsActions;
}

void Monster::afficherInfo() const {
    cout << "[" << this->categorie << "] " << this->obtenirNom()
              << " | PV: " << this->obtenirPv() << "/" << this->obtenirPvMax()
              << " | MERCY: " << this->jaugeMercy << "/" << this->objectifMercy
              << endl;
}

void Monster::modifierMercy(int _delta) {
    this->jaugeMercy += _delta;

    if (this->jaugeMercy < 0) {
        this->jaugeMercy = 0;
    }

    if (this->jaugeMercy > this->objectifMercy) {
        this->jaugeMercy = this->objectifMercy;
    }
}

bool Monster::estEpargnable() const {
    return this->jaugeMercy >= this->objectifMercy;
}

void Monster::ajouterActionAct(string _idAction) {
    this->idsActions.push_back(_idAction);
}

vector<string> Monster::obtenirActDisponibles() const {
    vector<string> disponibles;
    int nombre = this->obtenirNombreActions();

    for (int i = 0; i < nombre && i < (int)this->idsActions.size(); i++) {
        if (this->idsActions[i] != "-") {
            disponibles.push_back(this->idsActions[i]);
        }
    }

    return disponibles;
}

NormalMonster::NormalMonster(string _nom, int _pvMax, int _atk, int _def, int _objectifMercy)
    : Monster(_nom, "NORMAL", _pvMax, _atk, _def, _objectifMercy) {}

int NormalMonster::obtenirNombreActions() const {
    return 2;
}

MiniBossMonster::MiniBossMonster(string _nom, int _pvMax, int _atk, int _def, int _objectifMercy)
    : Monster(_nom, "MINIBOSS", _pvMax, _atk, _def, _objectifMercy) {}

int MiniBossMonster::obtenirNombreActions() const {
    return 3;
}

BossMonster::BossMonster(string _nom, int _pvMax, int _atk, int _def, int _objectifMercy)
    : Monster(_nom, "BOSS", _pvMax, _atk, _def, _objectifMercy) {}

int BossMonster::obtenirNombreActions() const {
    return 4;
}