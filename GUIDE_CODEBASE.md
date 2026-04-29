# Guide néophyte de la codebase ALTERDUNE

Ce document sert de **carte d’orientation** pour comprendre rapidement le projet.

## 1) À quoi sert ce projet ?

ALTERDUNE est un petit jeu en ligne de commande en C++:
- on crée un joueur ;
- on charge des objets et des monstres depuis des CSV ;
- on enchaîne des combats au tour par tour ;
- on peut soit tuer les monstres, soit les épargner via une mécanique de Mercy ;
- la fin dépend du style de jeu (pacifiste, neutre, génocidaire).

## 2) Structure générale

- `main.cpp` : point d’entrée, démarre simplement la classe `Game`.
- `Game.h/.cpp` : **chef d’orchestre** du jeu (boucle principale, menus, combats, chargement des fichiers, fin de partie).
- `Entite.h/.cpp` : classe de base `Entity` (nom, PV, ATK, DEF, dégâts, soin).
- `Joueur.h/.cpp` : `Player` hérite de `Entity` et gère l’inventaire + statistiques de victoire.
- `Monster.h/.cpp` : `Monster` hérite de `Entity` et ajoute la jauge Mercy + actions ACT ; variantes `NormalMonster`, `MiniBossMonster`, `BossMonster`.
- `Objet.h/.cpp` : classe `Item` (nom, type, valeur, quantité, usage).
- `ActAction.h/.cpp` : action sociale/verbale (id, texte, impact Mercy).
- `Utilitaires.h/.cpp` : includes communs + nettoyage de texte.
- `items.csv` : objets initiaux du joueur.
- `monsters.csv` : définition des monstres et des actions ACT disponibles.

## 3) Flux d’exécution (vue simple)

1. `main()` crée `Game` puis appelle `lancer()`.
2. `lancer()` :
   - lit le nom du joueur ;
   - crée `Player` ;
   - charge `items.csv` puis `monsters.csv` ;
   - affiche les infos ;
   - entre dans la boucle menu.
3. Depuis le menu principal:
   - combat,
   - statistiques,
   - inventaire,
   - bestiaire,
   - quitter.
4. En combat:
   - actions possibles: `FIGHT`, `ACT`, `ITEM`, `MERCY` ;
   - victoire si monstre KO **ou** épargné ;
   - après victoire, soin complet du joueur ;
   - fin de partie à 10 victoires.
5. À 10 victoires, le jeu affiche une fin selon le compteur tués/épargnés.

## 4) Concepts importants à maîtriser

### Héritage et polymorphisme
- `Entity` est abstraite (`afficherInfo()` pure virtuelle).
- `Player` et `Monster` implémentent leur propre affichage.
- `Monster` a une méthode virtuelle pure `obtenirNombreActions()`, surchargée selon la catégorie du monstre (2/3/4 actions ACT).

### Composition des données de jeu
- `Game` contient:
  - un pointeur vers `Player` ;
  - un catalogue global d’`ActAction` ;
  - des monstres « modèles » chargés depuis CSV ;
  - un bestiaire des rencontres.
- Pour chaque combat, on clone un monstre modèle (`creerCopieMonstre`) pour éviter de modifier l’original.

### Data-driven via CSV
- La plupart du contenu gameplay (objets, monstres, actions disponibles) vient de CSV.
- Modifier un CSV change le comportement sans toucher au code C++.

## 5) Points de repère pour progresser

### Étape A — Lire l’architecture en 20 minutes
1. `main.cpp`
2. signatures dans `Game.h`
3. `Game::lancer()` puis `Game::demarrerCombat()`
4. `Player::utiliserObjet()`
5. `Monster::modifierMercy()` et `Monster::obtenirActDisponibles()`

### Étape B — Faire de petites modifications sûres
- Ajouter un nouvel objet dans `items.csv`.
- Ajouter un monstre dans `monsters.csv`.
- Ajouter une action dans `initialiserCatalogue()` et la référencer dans un monstre.

### Étape C — Changements code intéressants
- Refactoriser les pointeurs bruts (`new/delete`) vers des smart pointers.
- Introduire des tests sur le parsing CSV.
- Isoler le système de combat dans une classe dédiée.

## 6) Pièges et limites actuelles (à connaître tôt)

- Dégâts aléatoires basés sur `pvMax` de la cible, pas sur ATK/DEF (peut donner des résultats surprenants).
- `Player` stocke des `Item` par valeur ; quantité décrémentée localement au vecteur (ok ici, mais à surveiller si on partage les objets ailleurs).
- Gestion mémoire manuelle (`new/delete`) dans `Game` et pour les monstres clonés.
- Entrées utilisateur `cin`/`getline` mélangées: le code gère déjà certains cas (`fail`, `ignore`), mais il faut rester prudent lors des évolutions.

## 7) Roadmap d’apprentissage recommandée

1. Comprendre la boucle de jeu (`Game::lancer`).
2. Comprendre le combat (`demarrerCombat`) en traçant un tour complet.
3. Expérimenter avec les CSV.
4. Étudier l’héritage (`Entity` → `Player`/`Monster`).
5. Faire une mini-feature (nouveau type d’action ACT ou nouvel objet).

---

Si vous débutez en C++, ce projet est bien pour pratiquer:
- classes / héritage ;
- conteneurs STL (`vector`, `map`) ;
- lecture de fichiers ;
- gestion d’état dans une boucle de jeu.
