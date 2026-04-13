#include "Game.h"

// ============================================================
// Constructeur / Destructeur
// ============================================================
Game::Game() {
    this->joueurPtr = nullptr;
    this->initialiserCatalogue();
}

Game::~Game() {
    delete this->joueurPtr;
    for (Monster* m : this->monstresDisponibles) {
        delete m;
    }
}

// ============================================================
// Catalogue d'actions ACT (10 actions, dont 2 negatives)
// ============================================================
void Game::initialiserCatalogue() {
    this->catalogueActions.insert({"COMPLIMENT", ActAction("COMPLIMENT", "Vous dites au monstre qu'il a un joli sourire.", 20)});
    this->catalogueActions.insert({"JOKE", ActAction("JOKE", "Pourquoi les plongeurs plongent-ils toujours en arriere ? Parce que sinon ils tombent dans le bateau.", 15)});
    this->catalogueActions.insert({"DANCE", ActAction("DANCE", "Vous faites une petite danse ridicule.", 10)});
    this->catalogueActions.insert({"DISCUSS", ActAction("DISCUSS", "Vous parlez de la pluie et du beau temps.", 5)});
    this->catalogueActions.insert({"PET", ActAction("PET", "Vous lui caressez doucement la tete.", 25)});
    this->catalogueActions.insert({"OFFER_SNACK", ActAction("OFFER_SNACK", "Vous partagez un bout de votre gouter.", 30)});
    this->catalogueActions.insert({"OBSERVE", ActAction("OBSERVE", "Vous le regardez fixement sans rien dire.", 0)});
    this->catalogueActions.insert({"REASON", ActAction("REASON", "Vous tentez de raisonner le monstre avec des arguments logiques.", 10)});
    // Actions negatives (minimum 2 exigees par le sujet)
    this->catalogueActions.insert({"INSULT", ActAction("INSULT", "Vous dites que sa maman est un dictionnaire.", -10)});
    this->catalogueActions.insert({"THREATEN", ActAction("THREATEN", "Vous menacez le monstre du regard. Il serre les poings.", -15)});
}

// ============================================================
// Chargement de items.csv
// Format : nom;type;valeur;quantite
// Gestion d'erreurs : fichier introuvable + lignes mal formees
// ============================================================
bool Game::chargerFichierObjets(std::string chemin) {
    std::ifstream fichier(chemin);
    if (!fichier.is_open()) {
        std::cout << "Erreur : impossible d'ouvrir le fichier '" << chemin << "'" << std::endl;
        return false;
    }

    std::string ligne;
    int numLigne = 0;

    while (std::getline(fichier, ligne)) {
        numLigne++;

        // Ignorer les lignes vides
        if (ligne.empty()) continue;

        try {
            std::stringstream ss(ligne);
            std::string nom, type, valeurStr, quantiteStr;

            if (!std::getline(ss, nom, ';') ||
                !std::getline(ss, type, ';') ||
                !std::getline(ss, valeurStr, ';') ||
                (!std::getline(ss, quantiteStr, ';') && !std::getline(ss, quantiteStr))) {
                std::cout << "Avertissement : items.csv ligne " << numLigne
                          << " mal formee, ignoree." << std::endl;
                continue;
            }

            int valeur = std::stoi(valeurStr);
            int quantite = std::stoi(quantiteStr);

            this->joueurPtr->ajouterObjet(Item(nom, type, valeur, quantite));

        } catch (const std::exception& e) {
            std::cout << "Avertissement : items.csv ligne " << numLigne
                      << " contient des valeurs invalides, ignoree. (" << e.what() << ")"
                      << std::endl;
        }
    }

    fichier.close();
    return true;
}

// ============================================================
// Chargement de monsters.csv
// Format : categorie;nom;hp;atk;def;mercyGoal;act1;act2;act3;act4
// Gestion d'erreurs : fichier introuvable + lignes mal formees
// ============================================================
bool Game::chargerFichierMonstres(std::string chemin) {
    std::ifstream fichier(chemin);
    if (!fichier.is_open()) {
        std::cout << "Erreur : impossible d'ouvrir le fichier '" << chemin << "'" << std::endl;
        return false;
    }

    std::string ligne;
    int numLigne = 0;

    while (std::getline(fichier, ligne)) {
        numLigne++;

        if (ligne.empty()) continue;

        try {
            std::stringstream ss(ligne);
            std::string cat, nom, hpStr, atkStr, defStr, mercyStr;
            std::string a1, a2, a3, a4;

            if (!std::getline(ss, cat, ';') ||
                !std::getline(ss, nom, ';') ||
                !std::getline(ss, hpStr, ';') ||
                !std::getline(ss, atkStr, ';') ||
                !std::getline(ss, defStr, ';') ||
                !std::getline(ss, mercyStr, ';')) {
                std::cout << "Avertissement : monsters.csv ligne " << numLigne
                          << " mal formee, ignoree." << std::endl;
                continue;
            }

            // Lire les identifiants ACT (certains peuvent etre absents)
            std::getline(ss, a1, ';');
            std::getline(ss, a2, ';');
            std::getline(ss, a3, ';');
            std::getline(ss, a4);

            int hp = std::stoi(hpStr);
            int atk = std::stoi(atkStr);
            int def = std::stoi(defStr);
            int mercy = std::stoi(mercyStr);

            // Creation polymorphique du monstre selon la categorie
            Monster* m = nullptr;
            if (cat == "NORMAL") {
                m = new NormalMonster(nom, hp, atk, def, mercy);
            } else if (cat == "MINIBOSS") {
                m = new MiniBossMonster(nom, hp, atk, def, mercy);
            } else if (cat == "BOSS") {
                m = new BossMonster(nom, hp, atk, def, mercy);
            } else {
                std::cout << "Avertissement : monsters.csv ligne " << numLigne
                          << " categorie inconnue '" << cat << "', ignoree." << std::endl;
                continue;
            }

            if (a1 != "-" && !a1.empty()) m->ajouterActionAct(a1);
            if (a2 != "-" && !a2.empty()) m->ajouterActionAct(a2);
            if (a3 != "-" && !a3.empty()) m->ajouterActionAct(a3);
            if (a4 != "-" && !a4.empty()) m->ajouterActionAct(a4);

            this->monstresDisponibles.push_back(m);

        } catch (const std::exception& e) {
            std::cout << "Avertissement : monsters.csv ligne " << numLigne
                      << " contient des valeurs invalides, ignoree. (" << e.what() << ")"
                      << std::endl;
        }
    }

    fichier.close();
    return true;
}

// ============================================================
// Affichage du menu principal
// ============================================================
void Game::afficherMenuPrincipal() {
    std::cout << "\n=== ALTERDUNE : MENU PRINCIPAL ===" << std::endl;
    std::cout << "1. Partir au combat" << std::endl;
    std::cout << "2. Voir mes statistiques" << std::endl;
    std::cout << "3. Ouvrir l'inventaire" << std::endl;
    std::cout << "4. Consulter le Bestiaire" << std::endl;
    std::cout << "5. Quitter" << std::endl;
    std::cout << "Votre choix : ";
}

// ============================================================
// Point d'entree principal
// ============================================================
void Game::lancer() {
    // 1. Saisie du nom du joueur
    std::string nomJoueur;
    std::cout << "========================================" << std::endl;
    std::cout << "       BIENVENUE DANS ALTERDUNE" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Entrez le nom de votre personnage : ";
    std::getline(std::cin, nomJoueur);

    // 2. Creation du joueur
    this->joueurPtr = new Player(nomJoueur, 100, 15, 5);

    // 3. Chargement des fichiers CSV
    std::cout << "\nChargement des donnees..." << std::endl;
    if (!this->chargerFichierObjets("items.csv")) {
        std::cout << "Erreur critique : arret du programme." << std::endl;
        return;
    }
    std::cout << "  Items charges avec succes." << std::endl;

    if (!this->chargerFichierMonstres("monsters.csv")) {
        std::cout << "Erreur critique : arret du programme." << std::endl;
        return;
    }
    std::cout << "  Monstres charges avec succes." << std::endl;

    // 4. Resume de depart
    std::cout << std::endl;
    this->joueurPtr->afficherInfo();
    this->joueurPtr->afficherInventaire();

    // 5. Boucle du menu principal
    int choix = 0;
    while (choix != 5) {
        this->afficherMenuPrincipal();
        std::cin >> choix;

        // Protection contre les saisies invalides (point 6 de l'audit)
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Saisie invalide, entrez un nombre." << std::endl;
            choix = 0;
            continue;
        }

        switch (choix) {
            case 1: this->demarrerCombat(); break;
            case 2: this->afficherStatistiques(); break;
            case 3: this->joueurPtr->afficherInventaire(); break;
            case 4: this->afficherBestiaire(); break;
            case 5: std::cout << "Au revoir !" << std::endl; break;
            default: std::cout << "Choix invalide." << std::endl;
        }
    }
}

// ============================================================
// Combat (a implementer)
// ============================================================
void Game::demarrerCombat() {
    std::cout << "\n[Combat en cours de developpement...]" << std::endl;
}

// ============================================================
// Sous-menus
// ============================================================
void Game::afficherStatistiques() {
    this->joueurPtr->afficherInfo();
}

void Game::afficherBestiaire() {
    std::cout << "\n--- BESTIAIRE ---" << std::endl;
    if (this->bestiaire.empty()) {
        std::cout << "Aucun monstre rencontre pour le moment." << std::endl;
    }
    for (const auto& entry : this->bestiaire) {
        entry.afficher();
    }
}

// ============================================================
// Fin de partie (a completer avec demarrerCombat)
// ============================================================
bool Game::verifierFinDePartie() const {
    return this->joueurPtr->obtenirVictoires() >= 10;
}

void Game::afficherFin() const {
    // A implementer quand le combat sera code
}