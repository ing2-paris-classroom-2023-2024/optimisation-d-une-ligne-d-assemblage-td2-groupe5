//
// Created by shaima on 23/11/2023.
//

#include "source.h"

void liberer_graphe(t_graphe *graphe) {
    // Libération des ressources
    for (int i = 0; i < graphe->nombredesommet; i++) {
        free(graphe->matriceadjacente[i]);
        free(graphe->sommets[i].voisins);
    }
    free(graphe->matriceadjacente);
    free(graphe->sommets);
    free(graphe);
}

int classerdecroissancesommets(const void *a, const void *b) {
    t_sommet *sommet1 = (t_sommet *)a;
    t_sommet *sommet2 = (t_sommet *)b;
    return (sommet2->degre - sommet1->degre);
}

void trier_sommets_decroissant(t_graphe *graphe) {
    qsort(graphe->sommets, graphe->nombredesommet, sizeof(t_sommet), classerdecroissancesommets);
}

void compter_sommets_arcs(char *nom_fichier, int *nombredesommet, int *nombredarcs) {
    // Comptage des sommets et des arêtes dans le fichier
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        exit(EXIT_FAILURE);
    }
    int sommet1, sommet2;
    *nombredesommet = 0;
    *nombredarcs = 0;
    while (fscanf(fichier, "%d %d", &sommet1, &sommet2) != EOF) {
        if (sommet1 > *nombredesommet) {
            *nombredesommet = sommet1;
        }
        if (sommet2 > *nombredesommet) {
            *nombredesommet = sommet2;
        }
        (*nombredarcs)++;
    }
    fclose(fichier);
    (*nombredesommet)++;
}

t_graphe *creer_graphe(int nombredesommet, int nombredarcs) {
    // Création d'un graphe
    t_graphe *graphe = malloc(sizeof(t_graphe));
    graphe->nombredesommet = nombredesommet;
    graphe->nombredarcs = nombredarcs;
    graphe->sommets = malloc(nombredesommet * sizeof(t_sommet));
    graphe->matriceadjacente = malloc(nombredesommet * sizeof(int *));
    for (int i = 0; i < nombredesommet; i++) {
        graphe->matriceadjacente[i] = malloc(nombredesommet * sizeof(int));
        for (int j = 0; j < nombredesommet; j++) {
            graphe->matriceadjacente[i][j] = 0;
        }
    }
    for (int i = 0; i < nombredesommet; i++) {
        graphe->sommets[i].identite = i;
        graphe->sommets[i].degre = 0;
        graphe->sommets[i].voisins = malloc(nombredesommet * sizeof(int));
    }
    return graphe;
}

t_graphe *lire_graphe(char *nom_fichier) {
    // Lecture du graphe depuis le fichier
    int nombredesommet, nombredarcs;
    compter_sommets_arcs(nom_fichier, &nombredesommet, &nombredarcs);

    t_graphe *graphe = creer_graphe(nombredesommet, nombredarcs);

    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        exit(EXIT_FAILURE);
    }

    int sommet1, sommet2;
    while (fscanf(fichier, "%d %d", &sommet1, &sommet2) != EOF) {
        sommet1--;
        sommet2--;
        graphe->matriceadjacente[sommet1][sommet2] = 1;
        graphe->matriceadjacente[sommet2][sommet1] = 1;
        graphe->sommets[sommet1].voisins[graphe->sommets[sommet1].degre] = sommet2;
        graphe->sommets[sommet1].degre++;
        graphe->sommets[sommet2].voisins[graphe->sommets[sommet2].degre] = sommet1;
        graphe->sommets[sommet2].degre++;
    }

    fclose(fichier);
    return graphe;
}

void afficher_graphe(t_graphe *graphe) {
    printf("Nombre de sommets : %d\n", graphe->nombredesommet);
    printf("Nombre de contraintes : %d\n", graphe->nombredarcs);
    printf("Matrice d'adjacence :\n");
    for (int i = 0; i < graphe->nombredesommet; i++) {
        for (int j = 0; j < graphe->nombredesommet; j++) {
            printf("%d ", graphe->matriceadjacente[i][j]);
        }
        printf("\n");
    }
    printf("Liste des sommets par degre :\n");
    trier_sommets_decroissant(graphe);
    for (int i = 0; i < graphe->nombredesommet; i++) {
        printf("Sommet %d (degre %d):", graphe->sommets[i].identite + 1, graphe->sommets[i].degre);
        for (int j = 0; j < graphe->sommets[i].degre; j++) {
            printf(" %d", graphe->sommets[i].voisins[j] + 1);
        }
        printf("\n");
    }
}

void generer_fichier(char *nom_fichier, t_graphe *graphe) {
    // Génération du fichier avec les informations de sommets et d'arêtes
    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de la création du fichier %s\n", nom_fichier);
        exit(EXIT_FAILURE);
    }
    fprintf(fichier, "%d\n%d\n", graphe->nombredesommet, graphe->nombredarcs);
    for (int i = 0; i < graphe->nombredesommet; i++) {
        for (int j = i + 1; j < graphe->nombredesommet; j++) {
            if (graphe->matriceadjacente[i][j] == 1) {
                fprintf(fichier, "%d %d\n", i + 1, j + 1);
            }
        }
    }
    fclose(fichier);
}

void colorer_graphe(t_graphe *graphe) {
    trier_sommets_decroissant(graphe);

    for (int i = 0; i < graphe->nombredesommet; i++) {
        graphe->sommets[i].couleur = -1;
    }

    int couleur_actuelle = 0;
    for (int i = 0; i < graphe->nombredesommet; i++) {
        t_sommet *sommet = &graphe->sommets[i];

        int couleur_disponible = 1;
        for (int j = 0; j < sommet->degre; j++) {
            int voisin = sommet->voisins[j];
            if (graphe->sommets[voisin].couleur == couleur_actuelle) {
                couleur_disponible = 0;
                break;
            }
        }

        if (couleur_disponible) {
            sommet->couleur = couleur_actuelle;
        } else {
            couleur_actuelle++;
            sommet->couleur = couleur_actuelle;
        }
    }
}

void afficher_coloration(t_graphe *graphe) {
    printf("Coloration du graphe :\n");
    for (int i = 0; i < graphe->nombredesommet; i++) {
        printf("Sommet %d : Couleur %d\n", graphe->sommets[i].identite + 1, graphe->sommets[i].couleur + 1);
    }
}
