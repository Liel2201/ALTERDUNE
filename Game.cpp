#include "Game.h"
using namespace std;


Game::Game() {
    this->joueurPtr = nullptr;
    this->partieTerminee = false;

    random_device rd;
    this->rng = mt19937(rd());

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

bool Game::chargerFichierObjets(string chemin) {
    ifstream fichier(chemin);

    if (!fichier.is_open()) {
        cout << "Erreur : impossible d'ouvrir le fichier '" << chemin << "'" << endl;
        return false;
    }

    string ligne;
    int numLigne = 0;

    while (getline(fichier, ligne)) {
        numLigne++;

        if (ligne.empty()) {
            continue;
        }

        try {
            stringstream ss(ligne);

            string nom;
            string type;
            string valeurStr;
            string quantiteStr;

            if (!getline(ss, nom, ';') ||
                !getline(ss, type, ';') ||
                !getline(ss, valeurStr, ';') ||
                (!getline(ss, quantiteStr, ';') && !getline(ss, quantiteStr))) {
                cout << "Avertissement : items.csv ligne " << numLigne
                          << " mal formee, ignoree." << endl;
                continue;
            }

            nom = nettoyerTexte(nom);
            type = nettoyerTexte(type);
            valeurStr = nettoyerTexte(valeurStr);
            quantiteStr = nettoyerTexte(quantiteStr);

            int valeur = stoi(valeurStr);
            int quantite = stoi(quantiteStr);

            this->joueurPtr->ajouterObjet(Item(nom, type, valeur, quantite));

        } catch (const exception& e) {
            cout << "Avertissement : items.csv ligne " << numLigne
                      << " contient des valeurs invalides, ignoree. (" << e.what() << ")"
                      << endl;
        }
    }

    fichier.close();
    return true;
}

bool Game::chargerFichierMonstres(string chemin) {
    ifstream fichier(chemin);

    if (!fichier.is_open()) {
        cout << "Erreur : impossible d'ouvrir le fichier '" << chemin << "'" << endl;
        return false;
    }

    string ligne;
    int numLigne = 0;

    while (getline(fichier, ligne)) {
        numLigne++;

        if (ligne.empty()) {
            continue;
        }

        try {
            stringstream ss(ligne);

            string cat;
            string nom;
            string hpStr;
            string atkStr;
            string defStr;
            string mercyStr;

            string a1;
            string a2;
            string a3;
            string a4;

            if (!getline(ss, cat, ';') ||
                !getline(ss, nom, ';') ||
                !getline(ss, hpStr, ';') ||
                !getline(ss, atkStr, ';') ||
                !getline(ss, defStr, ';') ||
                !getline(ss, mercyStr, ';')) {
                cout << "Avertissement : monsters.csv ligne " << numLigne
                          << " mal formee, ignoree." << endl;
                continue;
            }

            getline(ss, a1, ';');
            getline(ss, a2, ';');
            getline(ss, a3, ';');
            getline(ss, a4);

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

            int hp = stoi(hpStr);
            int atk = stoi(atkStr);
            int def = stoi(defStr);
            int mercy = stoi(mercyStr);

            Monster* m = nullptr;

            if (cat == "NORMAL") {
                m = new NormalMonster(nom, hp, atk, def, mercy);
            } else if (cat == "MINIBOSS") {
                m = new MiniBossMonster(nom, hp, atk, def, mercy);
            } else if (cat == "BOSS") {
                m = new BossMonster(nom, hp, atk, def, mercy);
            } else {
                cout << "Avertissement : monsters.csv ligne " << numLigne
                          << " categorie inconnue '" << cat << "', ignoree." << endl;
                continue;
            }

            if (a1 != "-" && !a1.empty()) {
                if (this->catalogueActions.find(a1) != this->catalogueActions.end()) {
                    m->ajouterActionAct(a1);
                } else {
                    cout << "Avertissement : action ACT inconnue '" << a1
                              << "' ligne " << numLigne << ", ignoree." << endl;
                }
            }

            if (a2 != "-" && !a2.empty()) {
                if (this->catalogueActions.find(a2) != this->catalogueActions.end()) {
                    m->ajouterActionAct(a2);
                } else {
                    cout << "Avertissement : action ACT inconnue '" << a2
                              << "' ligne " << numLigne << ", ignoree." << endl;
                }
            }

            if (a3 != "-" && !a3.empty()) {
                if (this->catalogueActions.find(a3) != this->catalogueActions.end()) {
                    m->ajouterActionAct(a3);
                } else {
                    cout << "Avertissement : action ACT inconnue '" << a3
                              << "' ligne " << numLigne << ", ignoree." << endl;
                }
            }

            if (a4 != "-" && !a4.empty()) {
                if (this->catalogueActions.find(a4) != this->catalogueActions.end()) {
                    m->ajouterActionAct(a4);
                } else {
                    cout << "Avertissement : action ACT inconnue '" << a4
                              << "' ligne " << numLigne << ", ignoree." << endl;
                }
            }

            this->monstresDisponibles.push_back(m);

        } catch (const exception& e) {
            cout << "Avertissement : monsters.csv ligne " << numLigne
                      << " contient des valeurs invalides, ignoree. (" << e.what() << ")"
                      << endl;
        }
    }

    fichier.close();
    return true;
}

void Game::afficherMenuPrincipal() {
    cout << "\n=== ALTERDUNE : MENU PRINCIPAL ===" << endl;
    cout << "1. Partir au combat" << endl;
    cout << "2. Voir mes statistiques" << endl;
    cout << "3. Ouvrir l'inventaire" << endl;
    cout << "4. Consulter le Bestiaire" << endl;
    cout << "5. Quitter" << endl;
    cout << "Votre choix : ";
}

void Game::lancer() {
    string nomJoueur;

    cout << "========================================" << endl;
    cout << "       BIENVENUE DANS ALTERDUNE" << endl;
    cout << "========================================" << endl;
    cout << "Entrez le nom de votre personnage : ";
    getline(cin, nomJoueur);

    this->joueurPtr = new Player(nomJoueur, 100, 15, 5);

    cout << "\nChargement des donnees..." << endl;

    if (!this->chargerFichierObjets("items.csv")) {
        cout << "Erreur critique : arret du programme." << endl;
        return;
    }

    cout << "  Items charges avec succes." << endl;

    if (!this->chargerFichierMonstres("monsters.csv")) {
        cout << "Erreur critique : arret du programme." << endl;
        return;
    }

    cout << "  Monstres charges avec succes." << endl;
    cout << endl;

    this->joueurPtr->afficherInfo();
    this->joueurPtr->afficherInventaire();

    string choixTexte;
    int choix = 0;

    while (choix != 5 && !this->partieTerminee) {
        this->afficherMenuPrincipal();
        cin >> choixTexte;

        try {
            choix = stoi(choixTexte);

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
                    cout << "Au revoir !" << endl;
                    break;

                default:
                    cout << "Choix invalide. Veuillez entrer un nombre entre 1 et 5." << endl;
                    break;
            }

        } catch (const exception& e) {
            cout << "Saisie invalide. Veuillez entrer un nombre entre 1 et 5." << endl;
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
        vector<string> actions = modele->obtenirIdsActions();

        for (int i = 0; i < (int)actions.size(); i++) {
            copie->ajouterActionAct(actions[i]);
        }
    }

    return copie;
}

void Game::ouvrirInventaire() {
    if (this->joueurPtr->obtenirTailleInventaire() == 0) {
        cout << "\nVotre inventaire est vide." << endl;
        return;
    }

    int choix = -1;
    bool fini = false;

    while (!fini) {
        this->joueurPtr->afficherInventaire();

        cout << "\nEntrez le numero de l'objet a utiliser." << endl;
        cout << "Entrez 0 pour revenir au menu principal." << endl;
        cout << "Votre choix : ";

        cin >> choix;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Saisie invalide. Veuillez entrer un nombre." << endl;
        } else if (choix == 0) {
            fini = true;
        } else if (choix >= 1 && choix <= this->joueurPtr->obtenirTailleInventaire()) {
            bool objetUtilise = this->joueurPtr->utiliserObjet(choix - 1);

            if (objetUtilise) {
                fini = true;
            } else {
                cout << "Veuillez choisir un objet utilisable." << endl;
            }
        } else {
            cout << "Choix invalide. Veuillez choisir un numero de la liste." << endl;
        }
    }
}

void Game::demarrerCombat() {
    if (this->monstresDisponibles.empty()) {
        cout << "\nAucun monstre disponible. Impossible de lancer un combat." << endl;
        return;
    }

    uniform_int_distribution<int> distribution(0, (int)this->monstresDisponibles.size() - 1);
    int indiceMonstre = distribution(this->rng);

    Monster* modele = this->monstresDisponibles[indiceMonstre];
    Monster* monstre = this->creerCopieMonstre(modele);

    if (monstre == nullptr) {
        cout << "\nErreur : impossible de creer une copie du monstre." << endl;
        return;
    }

    bool combatGagne = false;

    cout << "\n========================================" << endl;
    cout << "                COMBAT" << endl;
    cout << "========================================" << endl;
    cout << "Un monstre apparait !" << endl;
    cout << "Nom       : " << monstre->obtenirNom() << endl;
    cout << "Categorie : " << monstre->obtenirCategorie() << endl;
    cout << "========================================" << endl;

    while (monstre->estVivant() && this->joueurPtr->estVivant() && !combatGagne) {
        cout << "\n------------- ETAT DU COMBAT ------------" << endl;
        cout << "Joueur  : "
                  << this->joueurPtr->obtenirPv()
                  << " / "
                  << this->joueurPtr->obtenirPvMax()
                  << " PV" << endl;

        cout << "Monstre : "
                  << monstre->obtenirNom()
                  << " | "
                  << monstre->obtenirPv()
                  << " / "
                  << monstre->obtenirPvMax()
                  << " PV" << endl;

        cout << "Mercy   : "
                  << monstre->obtenirJaugeMercy()
                  << " / "
                  << monstre->obtenirObjectifMercy()
                  << endl;
        cout << "-----------------------------------------" << endl;

        int choix = 0;
        bool choixValide = false;

        while (!choixValide) {
            cout << "\n--------------- ACTIONS ----------------" << endl;
            cout << "1. FIGHT" << endl;
            cout << "2. ACT" << endl;
            cout << "3. ITEM" << endl;
            cout << "4. MERCY" << endl;
            cout << "-----------------------------------------" << endl;
            cout << "Votre choix : ";

            cin >> choix;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Saisie invalide. Veuillez entrer un nombre entre 1 et 4." << endl;
            } else if (choix == 1) {
                cout << "\nVous attaquez le monstre !" << endl;

                uniform_int_distribution<int> distributionDegats(0, monstre->obtenirPvMax());
                int degats = distributionDegats(this->rng);

                if (degats == 0) {
                    cout << "Votre attaque rate ! Aucun degat inflige." << endl;
                } else {
                    monstre->subirDegats(degats);
                    cout << "Vous infligez " << degats << " degats au monstre." << endl;
                    cout << "PV du monstre : "
                              << monstre->obtenirPv()
                              << " / "
                              << monstre->obtenirPvMax()
                              << endl;
                }

                choixValide = true;

            } else if (choix == 2) {
                vector<string> actionsDisponibles = monstre->obtenirActDisponibles();

                if (actionsDisponibles.empty()) {
                    cout << "\nCe monstre n'a aucune action ACT disponible." << endl;
                    choixValide = true;
                } else {
                    int choixAct = 0;
                    bool actionValide = false;

                    while (!actionValide) {
                        cout << "\n------------- ACTIONS ACT --------------" << endl;

                        for (int i = 0; i < (int)actionsDisponibles.size(); i++) {
                            cout << i + 1 << ". " << actionsDisponibles[i] << endl;
                        }

                        cout << "-----------------------------------------" << endl;
                        cout << "Votre choix : ";
                        cin >> choixAct;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Saisie invalide. Veuillez entrer un nombre." << endl;
                        } else if (choixAct >= 1 && choixAct <= (int)actionsDisponibles.size()) {
                            string idAction = actionsDisponibles[choixAct - 1];

                            map<string, ActAction>::iterator itAction;
                            itAction = this->catalogueActions.find(idAction);

                            cout << endl;
                            itAction->second.executer();

                            int impact = itAction->second.obtenirImpact();
                            monstre->modifierMercy(impact);

                            if (impact > 0) {
                                cout << "La Mercy augmente de " << impact << "." << endl;
                            } else if (impact < 0) {
                                cout << "La Mercy diminue de " << -impact << "." << endl;
                            } else {
                                cout << "La Mercy ne change pas." << endl;
                            }

                            cout << "Mercy du monstre : "
                                      << monstre->obtenirJaugeMercy()
                                      << " / "
                                      << monstre->obtenirObjectifMercy()
                                      << endl;

                            actionValide = true;
                            choixValide = true;
                        } else {
                            cout << "Choix invalide. Veuillez choisir un numero de la liste." << endl;
                        }
                    }
                }

            } else if (choix == 3) {
                if (this->joueurPtr->obtenirTailleInventaire() == 0) {
                    cout << "\nVotre inventaire est vide." << endl;
                } else {
                    int choixItem = 0;
                    bool objetUtilise = false;

                    while (!objetUtilise) {
                        this->joueurPtr->afficherInventaire();

                        cout << "Choisissez un objet a utiliser : ";
                        cin >> choixItem;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Saisie invalide. Veuillez entrer un nombre." << endl;
                        } else if (choixItem >= 1 && choixItem <= this->joueurPtr->obtenirTailleInventaire()) {
                            objetUtilise = this->joueurPtr->utiliserObjet(choixItem - 1);

                            if (!objetUtilise) {
                                cout << "Veuillez choisir un objet utilisable." << endl;
                            }
                        } else {
                            cout << "Choix invalide. Veuillez choisir un numero de la liste." << endl;
                        }
                    }

                    choixValide = true;
                }

            } else if (choix == 4) {
                if (monstre->estEpargnable()) {
                    cout << "\n========================================" << endl;
                    cout << "               VICTOIRE" << endl;
                    cout << "========================================" << endl;
                    cout << "Vous epargnez " << monstre->obtenirNom() << "." << endl;
                    cout << "Vous remportez le combat sans le tuer." << endl;

                    this->joueurPtr->ajouterVictoire(false);
                    this->joueurPtr->soigner(this->joueurPtr->obtenirPvMax());
                    cout << "Vous recuperez tous vos PV apres le combat." << endl;
                    cout << "========================================" << endl;

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
                    cout << "\nLe monstre n'est pas encore pret a etre epargne." << endl;
                    cout << "Mercy actuelle : "
                              << monstre->obtenirJaugeMercy()
                              << " / "
                              << monstre->obtenirObjectifMercy()
                              << endl;
                }

                choixValide = true;

            } else {
                cout << "\nChoix invalide. Veuillez entrer un nombre entre 1 et 4." << endl;
            }
        }

        if (!combatGagne) {
            if (!monstre->estVivant()) {
                cout << "\n========================================" << endl;
                cout << "               VICTOIRE" << endl;
                cout << "========================================" << endl;
                cout << "Vous avez vaincu " << monstre->obtenirNom() << "." << endl;
                cout << "Vous remportez le combat en tuant le monstre." << endl;

                this->joueurPtr->ajouterVictoire(true);
                this->joueurPtr->soigner(this->joueurPtr->obtenirPvMax());
                cout << "Vous recuperez tous vos PV apres le combat." << endl;
                cout << "========================================" << endl;

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
                cout << "\nLe monstre attaque !" << endl;

                uniform_int_distribution<int> distributionDegatsMonstre(0, this->joueurPtr->obtenirPvMax());
                int degatsMonstre = distributionDegatsMonstre(this->rng);

                if (degatsMonstre == 0) {
                    cout << "Le monstre rate son attaque ! Aucun degat recu." << endl;
                } else {
                    this->joueurPtr->subirDegats(degatsMonstre);
                    cout << "Le monstre vous inflige " << degatsMonstre << " degats." << endl;
                }

                cout << "Vos PV : "
                          << this->joueurPtr->obtenirPv()
                          << " / "
                          << this->joueurPtr->obtenirPvMax()
                          << endl;

                if (!this->joueurPtr->estVivant()) {
                    cout << "\n========================================" << endl;
                    cout << "                DEFAITE" << endl;
                    cout << "========================================" << endl;
                    cout << "Vous avez ete vaincu..." << endl;
                    cout << "La partie est terminee." << endl;
                    cout << "========================================" << endl;

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
    cout << "\n--- BESTIAIRE ---" << endl;

    if (this->bestiaire.empty()) {
        cout << "Aucun monstre rencontre pour le moment." << endl;
    }

    for (int i = 0; i < (int)this->bestiaire.size(); i++) {
        this->bestiaire[i].afficher();
    }
}

bool Game::verifierFinDePartie() const {
    return this->joueurPtr->obtenirVictoires() >= 10;
}

void Game::afficherFin() const {
    cout << "\n========================================" << endl;
    cout << "              FIN DE PARTIE" << endl;
    cout << "========================================" << endl;

    if (this->joueurPtr->obtenirTues() == 10) {
        cout << "Fin genocidaire" << endl;
        cout << "Vous avez elimine tous les monstres rencontres." << endl;
        cout << "Le monde d'ALTERDUNE se souviendra de votre violence." << endl;
    } else if (this->joueurPtr->obtenirEpargnes() == 10) {
        cout << "Fin pacifiste" << endl;
        cout << "Vous avez epargne tous les monstres rencontres." << endl;
        cout << "Votre compassion a apaise le monde d'ALTERDUNE." << endl;
    } else {
        cout << "Fin neutre" << endl;
        cout << "Vous avez parfois combattu, parfois epargne." << endl;
        cout << "Votre aventure laisse derriere elle un monde incertain." << endl;
    }

    cout << "========================================" << endl;
}
