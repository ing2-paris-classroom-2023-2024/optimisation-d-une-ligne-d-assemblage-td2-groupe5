//
// Created by annap on 21/11/2023.
//

#ifndef PROJET_TG1_ANNA_H
#define PROJET_TG1_ANNA_H

#include "header.h"

typedef struct graphe{
    int nbSommets;
    int nbArcs;
    int matriceAdjacence[100][100];
    int degres[100];
    int sommetsTries[100];
    char couleurs[100][10];
} t_graphe;

void initialiserGraphe(t_graphe *graphe);

void lireFichier(char *nomFichier, t_graphe *graphe);

//int compterExclusions(char *nomFichier);

void calculerDegres(t_graphe *graphe);

void trierSommets(t_graphe *graphe);

void attribuerCouleurs(t_graphe *graphe);

void afficherGrapheTrie(t_graphe *graphe);

void afficherGrapheColorie(t_graphe *graphe);

void afficherSommetsAdjacents(t_graphe *graphe, int sommet);

void menuExclusions();

#endif //PROJET_TG1_ANNA_H
