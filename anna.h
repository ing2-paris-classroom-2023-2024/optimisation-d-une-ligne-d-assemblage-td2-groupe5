//
// Created by annap on 21/11/2023.
//

#ifndef PROJET_TG1_ANNA_H
#define PROJET_TG1_ANNA_H

#include "header.h"


void afficherFichier (char *nomFichier);
int compterContraintes(char *nomFichier);

//void menu(char *nomFichier, FILE *fichier);
void menu(char *nomFichier);

typedef struct grapheContraintes {
    int nbSommets;
    int nbArcs;
    int nbContraintes;

    //matrice que je parcours pour parcourir tous les trucs, ca explore et liste les contraintes
    int **matriceAdjacence;
    int *tabContraintes;
} t_grapheContraintes;


#endif //PROJET_TG1_ANNA_H
