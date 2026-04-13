#ifndef ACTACTION_H
#define ACTACTION_H

#include "Utilitaires.h"

// Classe représentant une action pacifique (ACT) que le joueur peut faire en combat
class ActAction {
private:
    std::string id;          // Ex: "JOKE", "COMPLIMENT"
    std::string texte;       // Le texte drôle affiché à l'écran
    int impactMercy;         // Positif (apaise), Négatif (énerve), ou Zéro

public:
    ActAction(std::string _id, std::string _texte, int _impact);
    
    std::string obtenirId() const;
    int obtenirImpact() const;
    
    // Affiche simplement le texte de l'action à l'écran
    void executer() const;
};

#endif