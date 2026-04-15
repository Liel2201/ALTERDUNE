#ifndef ACTACTION_H
#define ACTACTION_H

#include "Utilitaires.h"

// Classe représentant une action pacifique (ACT) que le joueur peut faire en combat
class ActAction {
private:
    std::string id;          
    std::string texte;       
    int impactMercy;         

public:
    ActAction(std::string _id, std::string _texte, int _impact);
    std::string obtenirId() const;
    int obtenirImpact() const;
    void executer() const;
};

#endif