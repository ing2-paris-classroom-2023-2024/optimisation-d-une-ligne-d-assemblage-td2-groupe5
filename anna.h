//
// Created by annap on 21/11/2023.
//

#ifndef PROJET_TG1_ANNA_H
#define PROJET_TG1_ANNA_H

#include "header.h"


typedef struct sommet {
    int couleur;
    int numerodesommet;
    //si le sommet est deja colorié alors on le passe a true
    bool colorie;
} t_sommet;

typedef struct graphe {
    int nbSommets;
    int nbArcs;
    t_sommet *tabSommets;
    int **matriceAdjacence;
} t_graphe;





typedef struct grapheExclusions {
    int nbSommets;
    int nbArcs;
    int nbExclusions;
    //matrice que je parcours pour parcourir tous les trucs, ca explore et liste les exclusions
    int **matriceAdjacence;
    int *tabExclusions;
} t_grapheExclusions;




void afficherFichier (char *nomFichier);

int compterExclusions(char *nomFichier);

void menu(char *nomFichier);




#endif //PROJET_TG1_ANNA_H
