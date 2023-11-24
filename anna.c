//
// Created by annap on 21/11/2023.
//
#include "anna.h"

void initialiserGraphe(t_graphe *graphe) {
    graphe->nbSommets = MAX_SOMMETS;
    for (int i = 0; i < MAX_SOMMETS; i++) {
        graphe->degres[i] = 0;
        graphe->sommetsTries[i] = 0;
        for (int j = 0; j < MAX_SOMMETS; j++) {
            graphe->matriceAdjacence[i][j] = 0;
        }
        graphe->couleurs[i][0] = '\0';
    }
}

void lireFichier(char *nomFichier, t_graphe *graphe) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    fscanf(fichier, "%d %d", &graphe->nbSommets, &graphe->nbArcs);

    for (int i = 0; i < graphe->nbArcs; i++) {
        int sommet1, sommet2;
        fscanf(fichier, "%d %d", &sommet1, &sommet2);
        graphe->matriceAdjacence[sommet1][sommet2] = 1;
        graphe->matriceAdjacence[sommet2][sommet1] = 1;
    }

    fclose(fichier);
}

void calculerDegres(t_graphe *graphe) {
    for (int i = 0; i < graphe->nbSommets; i++) {
        int degre = 0;
        for (int j = 0; j < graphe->nbSommets; j++) {
            degre += graphe->matriceAdjacence[i][j];
        }
        graphe->degres[i] = degre;
    }
}

//trier les sommets par degres decroissants
void trierSommets(t_graphe *graphe) {
    for (int i = 0; i < graphe->nbSommets; i++) {
        graphe->sommetsTries[i] = i;
    }

    for (int i = 0; i < graphe->nbSommets - 1; i++) {
        for (int j = i + 1; j < graphe->nbSommets; j++) {
            if (graphe->degres[graphe->sommetsTries[i]] < graphe->degres[graphe->sommetsTries[j]]) {
                int temp = graphe->sommetsTries[i];
                graphe->sommetsTries[i] = graphe->sommetsTries[j];
                graphe->sommetsTries[j] = temp;
            }
        }
    }
}

void attribuerCouleurs(t_graphe *graphe) {
    int couleur = 0;
    for (int i = 0; i < graphe->nbSommets; i++) {
        if (i < 2) {
            sprintf(graphe->couleurs[graphe->sommetsTries[i]], "Couleur %d", couleur++);
        } else {
            sprintf(graphe->couleurs[graphe->sommetsTries[i]], "Couleur %d", couleur);
        }
    }
}

void afficherGrapheTrie(t_graphe *graphe) {
    printf("Graphe trie par ordre de degres decroissants :\n");
    for (int i = 0; i < graphe->nbSommets; i++) {
        printf("Sommet %d : Degre %d\n", graphe->sommetsTries[i], graphe->degres[graphe->sommetsTries[i]]);
    }
}

void afficherGrapheColorie(t_graphe *graphe) {
    printf("\nGraphe colorie avec les bonnes couleurs :\n");
    for (int i = 0; i < graphe->nbSommets; i++) {
        printf("Sommet %d : Couleur %s\n", graphe->sommetsTries[i], graphe->couleurs[graphe->sommetsTries[i]]);
    }
}

void afficherSommetsAdjacents(t_graphe *graphe, int sommet) {
    printf("\nSommets relies avec leurs couleurs respectives :\n");
    printf("Sommet %d : Couleur %s - Sommets adjacents: ", sommet, graphe->couleurs[sommet]);
    for (int i = 0; i < graphe->nbSommets; i++) {
        if (graphe->matriceAdjacence[sommet][i]) {
            printf("%d (Couleur %s) \n", i, graphe->couleurs[i]);
        }
    }
    //printf("\n");
}

void menuExclusions(){
    char nomFichier[100] ; // Nom du fichier à lire
    t_graphe graphe;

    do{
        printf("Veuillez entrer le nom du fichier a lire : \n");
        scanf("%s", nomFichier);

        if (strcmp(nomFichier, "exclusions.txt") != 0){
            printf("Choisissez un autre fichier qui existe.\n");
        }
    } while (strcmp(nomFichier, "exclusions.txt") != 0);

    initialiserGraphe(&graphe); // Initialiser le graphe

    lireFichier(nomFichier, &graphe); // Lecture du fichier

    calculerDegres(&graphe); // Calculer les degrés des sommets

    trierSommets(&graphe); // Trier les sommets par degrés décroissants

    attribuerCouleurs(&graphe); // Attribuer des couleurs aux sommets

    afficherGrapheTrie(&graphe); // Afficher le graphe trié par degrés

    afficherGrapheColorie(&graphe); // Afficher le graphe colorié

    afficherSommetsAdjacents(&graphe, 0); // Afficher les sommets adjacents pour le sommet 0
}
