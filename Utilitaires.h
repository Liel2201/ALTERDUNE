#ifndef UTILITAIRES_H
#define UTILITAIRES_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>

std::string nettoyerTexte(std::string texte) {
    while (!texte.empty() && texte[0] == ' ') {
        texte.erase(0, 1);
    }

    while (!texte.empty() && texte[texte.size() - 1] == ' ') {
        texte.erase(texte.size() - 1, 1);
    }

    return texte;
}

#endif