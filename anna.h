//
// Created by annap on 21/11/2023.
//

#ifndef PROJET_TG1_ANNA_H
#define PROJET_TG1_ANNA_H

#include "header.h"

//CHANGER LES VARIABLES GLOBALES
#define MAX_SOMMETS 100 // Nombre maximum de sommets dans le graphe
#define MAX_COULEURS 10 // Nombre maximum de couleurs

typedef struct graphe{
    int nbSommets;
    int nbArcs;
    int matriceAdjacence[MAX_SOMMETS][MAX_SOMMETS];
    int degres[MAX_SOMMETS];
    int sommetsTries[MAX_SOMMETS];
    char couleurs[MAX_SOMMETS][MAX_COULEURS];
} t_graphe;

void initialiserGraphe(t_graphe *graphe);

void lireFichier(char *nomFichier, t_graphe *graphe);

void calculerDegres(t_graphe *graphe);

void trierSommets(t_graphe *graphe);

void attribuerCouleurs(t_graphe *graphe);

void afficherGrapheTrie(t_graphe *graphe);

void afficherGrapheColorie(t_graphe *graphe);

void afficherSommetsAdjacents(t_graphe *graphe, int sommet);

void menuExclusions();

#endif //PROJET_TG1_ANNA_H
