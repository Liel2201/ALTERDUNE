#include "Game.h"

Game::Game() {
    joueurPtr = new Player("Daniel", 100, 15, 5);
    initialiserCatalogue();
    chargerFichierObjets("items.csv");
    chargerFichierMonstres("monsters.csv");
}

Game::~Game() {
    delete joueurPtr;
    for (Monster* m : monstresDisponibles) delete m;
}

void Game::initialiserCatalogue() {
    // On remplit le catalogue avec les 8 actions minimum requises
    catalogueActions.insert({"COMPLIMENT", ActAction("COMPLIMENT", "Vous dites au monstre qu'il a un joli sourire.", 20)});
    catalogueActions.insert({"JOKE", ActAction("JOKE", "Pourquoi les plongeurs plongent-ils toujours en arriere ? Parce que sinon ils tombent dans le bateau.", 15)});
    catalogueActions.insert({"DANCE", ActAction("DANCE", "Vous faites une petite danse ridicule.", 10)});
    catalogueActions.insert({"DISCUSS", ActAction("DISCUSS", "Vous parlez de la pluie et du beau temps.", 5)});
    catalogueActions.insert({"INSULT", ActAction("INSULT", "Vous dites que sa maman est un dictionnaire.", -10)});
    catalogueActions.insert({"PET", ActAction("PET", "Vous lui caressez doucement la tete.", 25)});
    catalogueActions.insert({"OFFER_SNACK", ActAction("OFFER_SNACK", "Vous partagez un bout de votre gouter.", 30)});
    catalogueActions.insert({"OBSERVE", ActAction("OBSERVE", "Vous le regardez fixement sans rien dire.", 0)});
}

bool Game::chargerFichierObjets(std::string chemin) {
    std::ifstream fichier(chemin);
    if (!fichier.is_open()) return false;
    std::string ligne;
    while (std::getline(fichier, ligne)) {
        std::stringstream ss(ligne);
        std::string n, t, v, q;
        std::getline(ss, n, ';'); std::getline(ss, t, ';');
        std::getline(ss, v, ';'); std::getline(ss, q, ';');
        joueurPtr->ajouterObjet(Item(n, t, std::stoi(v), std::stoi(q)));
    }
    return true;
}

bool Game::chargerFichierMonstres(std::string chemin) {
    std::ifstream fichier(chemin);
    if (!fichier.is_open()) return false;
    std::string ligne;
    while (std::getline(fichier, ligne)) {
        std::stringstream ss(ligne);
        std::string cat, nom, hp, atk, def, mercy, a1, a2, a3, a4;
        std::getline(ss, cat, ';'); std::getline(ss, nom, ';');
        std::getline(ss, hp, ';');  std::getline(ss, atk, ';');
        std::getline(ss, def, ';'); std::getline(ss, mercy, ';');
        std::getline(ss, a1, ';');  std::getline(ss, a2, ';');
        std::getline(ss, a3, ';');  std::getline(ss, a4, ';');

        Monster* m = nullptr;
        if (cat == "NORMAL") m = new NormalMonster(nom, std::stoi(hp), std::stoi(atk), std::stoi(def), std::stoi(mercy));
        else if (cat == "MINIBOSS") m = new MiniBossMonster(nom, std::stoi(hp), std::stoi(atk), std::stoi(def), std::stoi(mercy));
        else if (cat == "BOSS") m = new BossMonster(nom, std::stoi(hp), std::stoi(atk), std::stoi(def), std::stoi(mercy));
        
        if (m) {
            if (a1 != "-") m->ajouterActionAct(a1);
            if (a2 != "-") m->ajouterActionAct(a2);
            if (a3 != "-") m->ajouterActionAct(a3);
            if (a4 != "-") m->ajouterActionAct(a4);
            monstresDisponibles.push_back(m);
        }
    }
    return true;
}

void Game::lancer() {
    int choix = 0;
    while (choix != 5) {
        afficherMenuPrincipal();
        std::cin >> choix;
        switch (choix) {
            case 1: demarrerCombat(); break;
            case 2: afficherStatistiques(); break;
            case 3: joueurPtr->afficherInventaire(); break;
            case 4: afficherBestiaire(); break;
            case 5: std::cout << "Au revoir !" << std::endl; break;
            default: std::cout << "Choix invalide." << std::endl;
        }
    }
}

void Game::afficherMenuPrincipal() {
    std::cout << "\n=== ALTERDUNE : MENU PRINCIPAL ===" << std::endl;
    std::cout << "1. Partir au combat" << std::endl;
    std::cout << "2. Voir mes statistiques" << std::endl;
    std::cout << "3. Ouvrir l'inventaire" << std::endl;
    std::cout << "4. Consulter le Bestiaire" << std::endl;
    std::cout << "5. Quitter" << std::endl;
    std::cout << "Votre choix : ";
}

void Game::demarrerCombat() {
    std::cout << "\n[Combat en cours de developpement...]" << std::endl;
    // Ici on ajoutera la logique de combat plus tard
}

void Game::afficherStatistiques() {
    joueurPtr->afficherInfo();
}

void Game::afficherBestiaire() {
    std::cout << "\n--- BESTIAIRE ---" << std::endl;
    if (bestiaire.empty()) std::cout << "Aucun monstre rencontre pour le moment." << std::endl;
    for (const auto& entry : bestiaire) entry.afficher();
}