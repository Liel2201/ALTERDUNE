#include "ActAction.h"

ActAction::ActAction(std::string _id, std::string _texte, int _impact) {
    this->id = _id;
    this->texte = _texte;
    this->impactMercy = _impact;
}

std::string ActAction::obtenirId() const {
    return this->id;
}

int ActAction::obtenirImpact() const {
    return this->impactMercy;
}

void ActAction::executer() const {
    std::cout << ">> " << this->texte << std::endl;
}