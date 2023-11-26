//
// Created by shaima on 23/11/2023.
//

#ifndef PROJET_ALGO_SOURCE_H
#define PROJET_ALGO_SOURCE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int identite;
    int degre;
    int couleur;
    int *voisins;
} t_sommet;

typedef struct {
    int nombredesommet;
    int nombredarcs;
    int **matriceadjacente;
    t_sommet *sommets;
    int **contraintes;
} t_graphe;

void liberer_graphe(t_graphe *graphe);
int classerdecroissancesommets(const void *a, const void *b);
void trier_sommets_decroissant(t_graphe *graphe);
void compter_sommets_arcs(char *nom_fichier, int *nombredesommet, int *nombredarcs);
t_graphe *creer_graphe(int nombredesommet, int nombredarcs);
t_graphe *lire_graphe(char *nom_fichier);
void afficher_graphe(t_graphe *graphe);
void generer_fichier(char *nom_fichier, t_graphe *graphe);
void colorer_graphe(t_graphe *graphe);
void afficher_coloration(t_graphe *graphe);

#endif //PROJET_ALGO_SOURCE_H
