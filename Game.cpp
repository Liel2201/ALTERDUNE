#include "Game.h"

Game::Game() {
    this->joueurPtr = nullptr;
    this->partieTerminee = false;

    std::random_device rd;
    this->rng = std::mt19937(rd());

    this->initialiserCatalogue();
}

Game::~Game() {
    delete this->joueurPtr;

    for (int i = 0; i < (int)this->monstresDisponibles.size(); i++) {
        delete this->monstresDisponibles[i];
    }
}

void Game::initialiserCatalogue() {
    this->catalogueActions.insert({"COMPLIMENT", ActAction("COMPLIMENT", "Vous dites au monstre qu'il a un joli sourire.", 20)});
    this->catalogueActions.insert({"JOKE", ActAction("JOKE", "Pourquoi les plongeurs plongent-ils toujours en arriere ? Parce que sinon ils tombent dans le bateau.", 15)});
    this->catalogueActions.insert({"DANCE", ActAction("DANCE", "Vous faites une petite danse ridicule.", 10)});
    this->catalogueActions.insert({"DISCUSS", ActAction("DISCUSS", "Vous parlez de la pluie et du beau temps.", 5)});
    this->catalogueActions.insert({"PET", ActAction("PET", "Vous lui caressez doucement la tete.", 25)});
    this->catalogueActions.insert({"OFFER_SNACK", ActAction("OFFER_SNACK", "Vous partagez un bout de votre gouter.", 30)});
    this->catalogueActions.insert({"OBSERVE", ActAction("OBSERVE", "Vous le regardez fixement sans rien dire.", 0)});
    this->catalogueActions.insert({"REASON", ActAction("REASON", "Vous tentez de raisonner le monstre avec des arguments logiques.", 10)});
    this->catalogueActions.insert({"INSULT", ActAction("INSULT", "Vous dites que sa maman est un dictionnaire.", -10)});
    this->catalogueActions.insert({"THREATEN", ActAction("THREATEN", "Vous menacez le monstre du regard. Il serre les poings.", -15)});
}

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

        if (ligne.empty()) {
            continue;
        }

        try {
            std::stringstream ss(ligne);

            std::string nom;
            std::string type;
            std::string valeurStr;
            std::string quantiteStr;

            if (!std::getline(ss, nom, ';') ||
                !std::getline(ss, type, ';') ||
                !std::getline(ss, valeurStr, ';') ||
                (!std::getline(ss, quantiteStr, ';') && !std::getline(ss, quantiteStr))) {
                std::cout << "Avertissement : items.csv ligne " << numLigne
                          << " mal formee, ignoree." << std::endl;
                continue;
            }

            nom = nettoyerTexte(nom);
            type = nettoyerTexte(type);
            valeurStr = nettoyerTexte(valeurStr);
            quantiteStr = nettoyerTexte(quantiteStr);

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

        if (ligne.empty()) {
            continue;
        }

        try {
            std::stringstream ss(ligne);

            std::string cat;
            std::string nom;
            std::string hpStr;
            std::string atkStr;
            std::string defStr;
            std::string mercyStr;

            std::string a1;
            std::string a2;
            std::string a3;
            std::string a4;

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

            std::getline(ss, a1, ';');
            std::getline(ss, a2, ';');
            std::getline(ss, a3, ';');
            std::getline(ss, a4);

            cat = nettoyerTexte(cat);
            nom = nettoyerTexte(nom);
            hpStr = nettoyerTexte(hpStr);
            atkStr = nettoyerTexte(atkStr);
            defStr = nettoyerTexte(defStr);
            mercyStr = nettoyerTexte(mercyStr);

            a1 = nettoyerTexte(a1);
            a2 = nettoyerTexte(a2);
            a3 = nettoyerTexte(a3);
            a4 = nettoyerTexte(a4);

            int hp = std::stoi(hpStr);
            int atk = std::stoi(atkStr);
            int def = std::stoi(defStr);
            int mercy = std::stoi(mercyStr);

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

            if (a1 != "-" && !a1.empty()) {
                if (this->catalogueActions.find(a1) != this->catalogueActions.end()) {
                    m->ajouterActionAct(a1);
                } else {
                    std::cout << "Avertissement : action ACT inconnue '" << a1
                              << "' ligne " << numLigne << ", ignoree." << std::endl;
                }
            }

            if (a2 != "-" && !a2.empty()) {
                if (this->catalogueActions.find(a2) != this->catalogueActions.end()) {
                    m->ajouterActionAct(a2);
                } else {
                    std::cout << "Avertissement : action ACT inconnue '" << a2
                              << "' ligne " << numLigne << ", ignoree." << std::endl;
                }
            }

            if (a3 != "-" && !a3.empty()) {
                if (this->catalogueActions.find(a3) != this->catalogueActions.end()) {
                    m->ajouterActionAct(a3);
                } else {
                    std::cout << "Avertissement : action ACT inconnue '" << a3
                              << "' ligne " << numLigne << ", ignoree." << std::endl;
                }
            }

            if (a4 != "-" && !a4.empty()) {
                if (this->catalogueActions.find(a4) != this->catalogueActions.end()) {
                    m->ajouterActionAct(a4);
                } else {
                    std::cout << "Avertissement : action ACT inconnue '" << a4
                              << "' ligne " << numLigne << ", ignoree." << std::endl;
                }
            }

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

void Game::afficherMenuPrincipal() {
    std::cout << "\n=== ALTERDUNE : MENU PRINCIPAL ===" << std::endl;
    std::cout << "1. Partir au combat" << std::endl;
    std::cout << "2. Voir mes statistiques" << std::endl;
    std::cout << "3. Ouvrir l'inventaire" << std::endl;
    std::cout << "4. Consulter le Bestiaire" << std::endl;
    std::cout << "5. Quitter" << std::endl;
    std::cout << "Votre choix : ";
}

void Game::lancer() {
    std::string nomJoueur;

    std::cout << "========================================" << std::endl;
    std::cout << "       BIENVENUE DANS ALTERDUNE" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Entrez le nom de votre personnage : ";
    std::getline(std::cin, nomJoueur);

    this->joueurPtr = new Player(nomJoueur, 100, 15, 5);

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
    std::cout << std::endl;

    this->joueurPtr->afficherInfo();
    this->joueurPtr->afficherInventaire();

    std::string choixTexte;
    int choix = 0;

    while (choix != 5 && !this->partieTerminee) {
        this->afficherMenuPrincipal();
        std::cin >> choixTexte;

        try {
            choix = std::stoi(choixTexte);

            switch (choix) {
                case 1:
                    this->demarrerCombat();
                    break;

                case 2:
                    this->afficherStatistiques();
                    break;

                case 3:
                    this->ouvrirInventaire();
                    break;

                case 4:
                    this->afficherBestiaire();
                    break;

                case 5:
                    std::cout << "Au revoir !" << std::endl;
                    break;

                default:
                    std::cout << "Choix invalide. Veuillez entrer un nombre entre 1 et 5." << std::endl;
                    break;
            }

        } catch (const std::exception& e) {
            std::cout << "Saisie invalide. Veuillez entrer un nombre entre 1 et 5." << std::endl;
            choix = 0;
        }
    }
}

Monster* Game::creerCopieMonstre(Monster* modele) {
    Monster* copie = nullptr;

    if (modele->obtenirCategorie() == "NORMAL") {
        copie = new NormalMonster(
            modele->obtenirNom(),
            modele->obtenirPvMax(),
            modele->obtenirAttaque(),
            modele->obtenirDefense(),
            modele->obtenirObjectifMercy()
        );
    } else if (modele->obtenirCategorie() == "MINIBOSS") {
        copie = new MiniBossMonster(
            modele->obtenirNom(),
            modele->obtenirPvMax(),
            modele->obtenirAttaque(),
            modele->obtenirDefense(),
            modele->obtenirObjectifMercy()
        );
    } else if (modele->obtenirCategorie() == "BOSS") {
        copie = new BossMonster(
            modele->obtenirNom(),
            modele->obtenirPvMax(),
            modele->obtenirAttaque(),
            modele->obtenirDefense(),
            modele->obtenirObjectifMercy()
        );
    }

    if (copie != nullptr) {
        std::vector<std::string> actions = modele->obtenirIdsActions();

        for (int i = 0; i < (int)actions.size(); i++) {
            copie->ajouterActionAct(actions[i]);
        }
    }

    return copie;
}

void Game::ouvrirInventaire() {
    if (this->joueurPtr->obtenirTailleInventaire() == 0) {
        std::cout << "\nVotre inventaire est vide." << std::endl;
        return;
    }

    int choix = -1;
    bool fini = false;

    while (!fini) {
        this->joueurPtr->afficherInventaire();

        std::cout << "\nEntrez le numero de l'objet a utiliser." << std::endl;
        std::cout << "Entrez 0 pour revenir au menu principal." << std::endl;
        std::cout << "Votre choix : ";

        std::cin >> choix;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Saisie invalide. Veuillez entrer un nombre." << std::endl;
        } else if (choix == 0) {
            fini = true;
        } else if (choix >= 1 && choix <= this->joueurPtr->obtenirTailleInventaire()) {
            bool objetUtilise = this->joueurPtr->utiliserObjet(choix - 1);

            if (objetUtilise) {
                fini = true;
            } else {
                std::cout << "Veuillez choisir un objet utilisable." << std::endl;
            }
        } else {
            std::cout << "Choix invalide. Veuillez choisir un numero de la liste." << std::endl;
        }
    }
}

void Game::demarrerCombat() {
    if (this->monstresDisponibles.empty()) {
        std::cout << "\nAucun monstre disponible. Impossible de lancer un combat." << std::endl;
        return;
    }

    std::uniform_int_distribution<int> distribution(0, (int)this->monstresDisponibles.size() - 1);
    int indiceMonstre = distribution(this->rng);

    Monster* modele = this->monstresDisponibles[indiceMonstre];
    Monster* monstre = this->creerCopieMonstre(modele);

    if (monstre == nullptr) {
        std::cout << "\nErreur : impossible de creer une copie du monstre." << std::endl;
        return;
    }

    bool combatGagne = false;

    std::cout << "\n========================================" << std::endl;
    std::cout << "                COMBAT" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Un monstre apparait !" << std::endl;
    std::cout << "Nom       : " << monstre->obtenirNom() << std::endl;
    std::cout << "Categorie : " << monstre->obtenirCategorie() << std::endl;
    std::cout << "========================================" << std::endl;

    while (monstre->estVivant() && this->joueurPtr->estVivant() && !combatGagne) {
        std::cout << "\n------------- ETAT DU COMBAT ------------" << std::endl;
        std::cout << "Joueur  : "
                  << this->joueurPtr->obtenirPv()
                  << " / "
                  << this->joueurPtr->obtenirPvMax()
                  << " PV" << std::endl;

        std::cout << "Monstre : "
                  << monstre->obtenirNom()
                  << " | "
                  << monstre->obtenirPv()
                  << " / "
                  << monstre->obtenirPvMax()
                  << " PV" << std::endl;

        std::cout << "Mercy   : "
                  << monstre->obtenirJaugeMercy()
                  << " / "
                  << monstre->obtenirObjectifMercy()
                  << std::endl;
        std::cout << "-----------------------------------------" << std::endl;

        int choix = 0;
        bool choixValide = false;

        while (!choixValide) {
            std::cout << "\n--------------- ACTIONS ----------------" << std::endl;
            std::cout << "1. FIGHT" << std::endl;
            std::cout << "2. ACT" << std::endl;
            std::cout << "3. ITEM" << std::endl;
            std::cout << "4. MERCY" << std::endl;
            std::cout << "-----------------------------------------" << std::endl;
            std::cout << "Votre choix : ";

            std::cin >> choix;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Saisie invalide. Veuillez entrer un nombre entre 1 et 4." << std::endl;
            } else if (choix == 1) {
                std::cout << "\nVous attaquez le monstre !" << std::endl;

                std::uniform_int_distribution<int> distributionDegats(0, monstre->obtenirPvMax());
                int degats = distributionDegats(this->rng);

                if (degats == 0) {
                    std::cout << "Votre attaque rate ! Aucun degat inflige." << std::endl;
                } else {
                    monstre->subirDegats(degats);
                    std::cout << "Vous infligez " << degats << " degats au monstre." << std::endl;
                    std::cout << "PV du monstre : "
                              << monstre->obtenirPv()
                              << " / "
                              << monstre->obtenirPvMax()
                              << std::endl;
                }

                choixValide = true;

            } else if (choix == 2) {
                std::vector<std::string> actionsDisponibles = monstre->obtenirActDisponibles();

                if (actionsDisponibles.empty()) {
                    std::cout << "\nCe monstre n'a aucune action ACT disponible." << std::endl;
                    choixValide = true;
                } else {
                    int choixAct = 0;
                    bool actionValide = false;

                    while (!actionValide) {
                        std::cout << "\n------------- ACTIONS ACT --------------" << std::endl;

                        for (int i = 0; i < (int)actionsDisponibles.size(); i++) {
                            std::cout << i + 1 << ". " << actionsDisponibles[i] << std::endl;
                        }

                        std::cout << "-----------------------------------------" << std::endl;
                        std::cout << "Votre choix : ";
                        std::cin >> choixAct;

                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                            std::cout << "Saisie invalide. Veuillez entrer un nombre." << std::endl;
                        } else if (choixAct >= 1 && choixAct <= (int)actionsDisponibles.size()) {
                            std::string idAction = actionsDisponibles[choixAct - 1];

                            std::map<std::string, ActAction>::iterator itAction;
                            itAction = this->catalogueActions.find(idAction);

                            std::cout << std::endl;
                            itAction->second.executer();

                            int impact = itAction->second.obtenirImpact();
                            monstre->modifierMercy(impact);

                            if (impact > 0) {
                                std::cout << "La Mercy augmente de " << impact << "." << std::endl;
                            } else if (impact < 0) {
                                std::cout << "La Mercy diminue de " << -impact << "." << std::endl;
                            } else {
                                std::cout << "La Mercy ne change pas." << std::endl;
                            }

                            std::cout << "Mercy du monstre : "
                                      << monstre->obtenirJaugeMercy()
                                      << " / "
                                      << monstre->obtenirObjectifMercy()
                                      << std::endl;

                            actionValide = true;
                            choixValide = true;
                        } else {
                            std::cout << "Choix invalide. Veuillez choisir un numero de la liste." << std::endl;
                        }
                    }
                }

            } else if (choix == 3) {
                if (this->joueurPtr->obtenirTailleInventaire() == 0) {
                    std::cout << "\nVotre inventaire est vide." << std::endl;
                } else {
                    int choixItem = 0;
                    bool objetUtilise = false;

                    while (!objetUtilise) {
                        this->joueurPtr->afficherInventaire();

                        std::cout << "Choisissez un objet a utiliser : ";
                        std::cin >> choixItem;

                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                            std::cout << "Saisie invalide. Veuillez entrer un nombre." << std::endl;
                        } else if (choixItem >= 1 && choixItem <= this->joueurPtr->obtenirTailleInventaire()) {
                            objetUtilise = this->joueurPtr->utiliserObjet(choixItem - 1);

                            if (!objetUtilise) {
                                std::cout << "Veuillez choisir un objet utilisable." << std::endl;
                            }
                        } else {
                            std::cout << "Choix invalide. Veuillez choisir un numero de la liste." << std::endl;
                        }
                    }

                    choixValide = true;
                }

            } else if (choix == 4) {
                if (monstre->estEpargnable()) {
                    std::cout << "\n========================================" << std::endl;
                    std::cout << "               VICTOIRE" << std::endl;
                    std::cout << "========================================" << std::endl;
                    std::cout << "Vous epargnez " << monstre->obtenirNom() << "." << std::endl;
                    std::cout << "Vous remportez le combat sans le tuer." << std::endl;

                    this->joueurPtr->ajouterVictoire(false);
                    this->joueurPtr->soigner(this->joueurPtr->obtenirPvMax());
                    std::cout << "Vous recuperez tous vos PV apres le combat." << std::endl;
                    std::cout << "========================================" << std::endl;

                    BestiaryEntry entree(
                        monstre->obtenirNom(),
                        monstre->obtenirCategorie(),
                        monstre->obtenirPvMax(),
                        monstre->obtenirAttaque(),
                        monstre->obtenirDefense(),
                        false
                    );

                    this->bestiaire.push_back(entree);

                    combatGagne = true;

                    if (this->verifierFinDePartie()) {
                        this->afficherFin();
                        this->partieTerminee = true;
                    }
                } else {
                    std::cout << "\nLe monstre n'est pas encore pret a etre epargne." << std::endl;
                    std::cout << "Mercy actuelle : "
                              << monstre->obtenirJaugeMercy()
                              << " / "
                              << monstre->obtenirObjectifMercy()
                              << std::endl;
                }

                choixValide = true;

            } else {
                std::cout << "\nChoix invalide. Veuillez entrer un nombre entre 1 et 4." << std::endl;
            }
        }

        if (!combatGagne) {
            if (!monstre->estVivant()) {
                std::cout << "\n========================================" << std::endl;
                std::cout << "               VICTOIRE" << std::endl;
                std::cout << "========================================" << std::endl;
                std::cout << "Vous avez vaincu " << monstre->obtenirNom() << "." << std::endl;
                std::cout << "Vous remportez le combat en tuant le monstre." << std::endl;

                this->joueurPtr->ajouterVictoire(true);
                this->joueurPtr->soigner(this->joueurPtr->obtenirPvMax());
                std::cout << "Vous recuperez tous vos PV apres le combat." << std::endl;
                std::cout << "========================================" << std::endl;

                BestiaryEntry entree(
                    monstre->obtenirNom(),
                    monstre->obtenirCategorie(),
                    monstre->obtenirPvMax(),
                    monstre->obtenirAttaque(),
                    monstre->obtenirDefense(),
                    true
                );

                this->bestiaire.push_back(entree);

                combatGagne = true;

                if (this->verifierFinDePartie()) {
                    this->afficherFin();
                    this->partieTerminee = true;
                }
            } else {
                std::cout << "\nLe monstre attaque !" << std::endl;

                std::uniform_int_distribution<int> distributionDegatsMonstre(0, this->joueurPtr->obtenirPvMax());
                int degatsMonstre = distributionDegatsMonstre(this->rng);

                if (degatsMonstre == 0) {
                    std::cout << "Le monstre rate son attaque ! Aucun degat recu." << std::endl;
                } else {
                    this->joueurPtr->subirDegats(degatsMonstre);
                    std::cout << "Le monstre vous inflige " << degatsMonstre << " degats." << std::endl;
                }

                std::cout << "Vos PV : "
                          << this->joueurPtr->obtenirPv()
                          << " / "
                          << this->joueurPtr->obtenirPvMax()
                          << std::endl;

                if (!this->joueurPtr->estVivant()) {
                    std::cout << "\n========================================" << std::endl;
                    std::cout << "                DEFAITE" << std::endl;
                    std::cout << "========================================" << std::endl;
                    std::cout << "Vous avez ete vaincu..." << std::endl;
                    std::cout << "La partie est terminee." << std::endl;
                    std::cout << "========================================" << std::endl;

                    this->partieTerminee = true;
                }
            }
        }
    }

    delete monstre;
}

void Game::afficherStatistiques() {
    this->joueurPtr->afficherInfo();
}

void Game::afficherBestiaire() {
    std::cout << "\n--- BESTIAIRE ---" << std::endl;

    if (this->bestiaire.empty()) {
        std::cout << "Aucun monstre rencontre pour le moment." << std::endl;
    }

    for (int i = 0; i < (int)this->bestiaire.size(); i++) {
        this->bestiaire[i].afficher();
    }
}

bool Game::verifierFinDePartie() const {
    return this->joueurPtr->obtenirVictoires() >= 10;
}

void Game::afficherFin() const {
    std::cout << "\n========================================" << std::endl;
    std::cout << "              FIN DE PARTIE" << std::endl;
    std::cout << "========================================" << std::endl;

    if (this->joueurPtr->obtenirTues() == 10) {
        std::cout << "Fin genocidaire" << std::endl;
        std::cout << "Vous avez elimine tous les monstres rencontres." << std::endl;
        std::cout << "Le monde d'ALTERDUNE se souviendra de votre violence." << std::endl;
    } else if (this->joueurPtr->obtenirEpargnes() == 10) {
        std::cout << "Fin pacifiste" << std::endl;
        std::cout << "Vous avez epargne tous les monstres rencontres." << std::endl;
        std::cout << "Votre compassion a apaise le monde d'ALTERDUNE." << std::endl;
    } else {
        std::cout << "Fin neutre" << std::endl;
        std::cout << "Vous avez parfois combattu, parfois epargne." << std::endl;
        std::cout << "Votre aventure laisse derriere elle un monde incertain." << std::endl;
    }

    std::cout << "========================================" << std::endl;
}