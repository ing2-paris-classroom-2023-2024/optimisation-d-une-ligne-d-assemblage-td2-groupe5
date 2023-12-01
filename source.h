//
// Created by shaima on 23/11/2023.
//

#ifndef PROJET_ALGO_SOURCE_H
#define PROJET_ALGO_SOURCE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct { //structure d'un sommet
    int identite; //identifiant du sommet (numéro)
    int degre; //degré du sommet
    int couleur; //couleur du sommet
    int *voisins; //tableau des voisins du sommet
} t_sommet; //nom de la structure

typedef struct { //structure d'un graphe
    int nombredesommet; //nombre de sommets
    int nombredarcs; //nombre d'arcs
    int **matriceadjacente; //matrice d'adjacence du graphe qui est un tableau de tableau d'entiers
    t_sommet *sommets;  //tableau des sommets du graphe
    int **contraintes; //matrice des contraintes du graphe qui est un tableau de tableau d'entiers
} t_grapheS; //nom de la structure

void liberer_graphe(t_grapheS *graphe); //libère la mémoire allouée pour le graphe
int classerdecroissancesommets(const void *a, const void *b); //fonction de comparaison pour le tri des sommets
void trier_sommets_decroissant(t_grapheS *graphe); //trie les sommets du graphe par ordre décroissant de degré
void compter_sommets_arcs(char *nom_fichier, int *nombredesommet, int *nombredarcs); //compte le nombre de sommets et d'arcs dans le fichier
t_grapheS *creer_graphe(int nombredesommet, int nombredarcs); //crée un graphe
t_grapheS *lire_graphe(char *nom_fichier); //lit un graphe à partir d'un fichier
void afficher_graphe(t_grapheS *graphe); //affiche un graphe
void generer_fichier(char *nom_fichier, t_grapheS *graphe); //génère un fichier avec les informations de sommets et d'arêtes
void colorer_graphe(t_grapheS *graphe); //colorie le graphe
void afficher_coloration(t_grapheS *graphe); //affiche la coloration du graphe
void menuExcluS();

#endif //PROJET_ALGO_SOURCE_H
