//
// Created by annap on 21/11/2023.
//

#ifndef PROJET_TG1_ANNA_H
#define PROJET_TG1_ANNA_H

#include "header.h"


/*typedef struct sommet{
    int op;
    int couleur;
}t_sommet;

//pointeur sur un sommet
typedef t_sommet *psommet;


typedef struct exclusion {
    int op1;
    int op2;
} t_exclusion;

//pointeur sur une exclusion
typedef t_exclusion *pexclusion;

typedef struct grapheExclusions {
    int nbSommets;
    psommet *psommets;
    int nbAretes;
    pexclusion *pexclusions;
} t_grapheExclusions;*/





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
