#include "Utilitaires.h"
#include "Joueur.h"
#include "Monster.h"
#include "Objet.h"

// --- CHARGEMENT DES ITEMS ---
// Lit le fichier et retourne une liste d'objets Item
std::vector<Item> chargerItems(std::string _chemin) {
    std::vector<Item> inventaireCharge;
    std::ifstream fichier(_chemin);

    // Gestion d'erreur obligatoire : fichier introuvable 
    if (!fichier.is_open()) {
        std::cerr << "ERREUR : Impossible d'ouvrir " << _chemin << std::endl;
        return inventaireCharge;
    }

    std::string ligne;
    while (std::getline(fichier, ligne)) {
        if (ligne.empty()) continue; // Ignore les lignes vides 

        std::stringstream ss(ligne);
        std::string nom, type, valeurBrute, quantiteBrute;

        // Découpage par le séparateur ';' [cite: 137]
        std::getline(ss, nom, ';');
        std::getline(ss, type, ';');
        std::getline(ss, valeurBrute, ';');
        std::getline(ss, quantiteBrute, ';');

        try {
            int valeur = std::stoi(valeurBrute);
            int quantite = std::stoi(quantiteBrute);
            inventaireCharge.push_back(Item(nom, type, valeur, quantite));
        } catch (...) {
            // Gestion d'erreur : ligne mal formée 
            std::cerr << "Avertissement : Ligne mal formee ignoree dans " << _chemin << std::endl;
        }
    }
    fichier.close();
    return inventaireCharge;
}

// --- CHARGEMENT DES MONSTRES ---
// Utilise le polymorphisme pour creer les bonnes categories [cite: 21]
std::vector<Monster*> chargerMonstres(std::string _chemin) {
    std::vector<Monster*> monstresCharges;
    std::ifstream fichier(_chemin);

    if (!fichier.is_open()) {
        std::cerr << "ERREUR : Impossible d'ouvrir " << _chemin << std::endl;
        return monstresCharges;
    }

    std::string ligne;
    while (std::getline(fichier, ligne)) {
        if (ligne.empty()) continue;

        std::stringstream ss(ligne);
        std::string cat, nom, hpB, atkB, defB, mercyB, a1, a2, a3, a4;

        // Lecture de tous les champs 
        std::getline(ss, cat, ';');
        std::getline(ss, nom, ';');
        std::getline(ss, hpB, ';');
        std::getline(ss, atkB, ';');
        std::getline(ss, defB, ';');
        std::getline(ss, mercyB, ';');
        std::getline(ss, a1, ';');
        std::getline(ss, a2, ';');
        std::getline(ss, a3, ';');
        std::getline(ss, a4, ';');

        try {
            int hp = std::stoi(hpB);
            int atk = std::stoi(atkB);
            int def = std::stoi(defB);
            int mercyBut = std::stoi(mercyB);

            Monster* m = nullptr;
            // Instanciation selon la categorie (Polymorphisme) [cite: 156, 157, 158]
            if (cat == "NORMAL") m = new NormalMonster(nom, hp, atk, def, mercyBut);
            else if (cat == "MINIBOSS") m = new MiniBossMonster(nom, hp, atk, def, mercyBut);
            else if (cat == "BOSS") m = new BossMonster(nom, hp, atk, def, mercyBut);

            if (m) {
                // Ajout des identifiants d'actions ACT [cite: 152]
                if (a1 != "-") m->ajouterActionAct(a1);
                if (a2 != "-") m->ajouterActionAct(a2);
                if (a3 != "-") m->ajouterActionAct(a3);
                if (a4 != "-") m->ajouterActionAct(a4);
                monstresCharges.push_back(m);
            }
        } catch (...) {
            std::cerr << "Avertissement : Monstre mal forme ignore." << std::endl;
        }
    }
    fichier.close();
    return monstresCharges;
}

int main() {
    std::cout << "--- CHARGEMENT DES DONNEES ALTERDUNE ---" << std::endl;

    // Chargement des fichiers [cite: 28]
    std::vector<Item> inventaireHero = chargerItems("items.csv");
    std::vector<Monster*> listeEnnemis = chargerMonstres("monsters.csv");

    // Simulation de l'affichage resume du debut de partie [cite: 31]
    std::cout << "\n[RESUME DU JOUEUR]" << std::endl;
    Player hero("Daniel", 100, 15, 5);
    for (const auto& objet : inventaireHero) {
        hero.ajouterObjet(objet);
    }
    hero.afficherInfo();
    hero.afficherInventaire();

    std::cout << "\n[BESTIAIRE CHARGE]" << std::endl;
    for (Monster* m : listeEnnemis) {
        m->afficherInfo();
        std::cout << "  Actions dispo : " << m->obtenirNombreActions() << std::endl;
    }

    // Nettoyage memoire
    for (Monster* m : listeEnnemis) delete m;
    
    return 0;
}