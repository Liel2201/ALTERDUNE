#ifndef ACTACTION_H
#define ACTACTION_H

#include "Utilitaires.h"
using namespace std;


class ActAction {
private:
    string id;          
    string texte;       
    int impactMercy;         

public:
    ActAction(string _id, string _texte, int _impact);
    string obtenirId() const;
    int obtenirImpact() const;
    void executer() const;
};

#endif