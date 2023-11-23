//
// Created by annap on 21/11/2023.
//

#ifndef PROJET_TG1_ANNA_H
#define PROJET_TG1_ANNA_H

#include "header.h"


void afficherFichier (char *nomFichier);
int compterExclusions(char *nomFichier);

void menu(char *nomFichier);

typedef struct grapheExclusions {
    int nbSommets;
    int nbArcs;
    int nbExclusions;

    //matrice que je parcours pour parcourir tous les trucs, ca explore et liste les exclusions
    int **matriceAdjacence;
    int *tabExclusions;
} t_grapheexclusions;


#endif //PROJET_TG1_ANNA_H
