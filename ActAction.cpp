#include "ActAction.h"
using namespace std;


ActAction::ActAction(string _id, string _texte, int _impact) {
    this->id = _id;
    this->texte = _texte;
    this->impactMercy = _impact;
}

string ActAction::obtenirId() const {
    return this->id;
}

int ActAction::obtenirImpact() const {
    return this->impactMercy;
}

void ActAction::executer() const {
    cout << ">> " << this->texte << endl;
}
