#include "Utilitaires.h"
using namespace std;


string nettoyerTexte(string texte) {
    while (!texte.empty() && texte[0] == ' ') {
        texte.erase(0, 1);
    }

    while (!texte.empty() && texte[texte.size() - 1] == ' ') {
        texte.erase(texte.size() - 1, 1);
    }

    return texte;
}