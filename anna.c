//
// Created by annap on 21/11/2023.
//
#include "anna.h"

void afficherFichier(char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }
    char c;
    while ((c = fgetc(fichier)) != EOF) {
        printf("%c", c);
    }
    fclose(fichier);
}

int compterExclusions(char *nomFichier){
    FILE *fichier = fopen(nomFichier, "r");

    int nbExclusions = 0;
    char c = 0;

    while ((c = fgetc(fichier)) != EOF) {
        if (c == '\n') {
            nbExclusions++;
        }
    }

    fclose(fichier);
    return nbExclusions;
}



void menu(char *nomFichier) {
    t_grapheexclusions *grapheexclusions = malloc(sizeof(t_grapheexclusions));
    if (grapheexclusions == NULL) {
        printf("Erreur lors de l'allocation de la mémoire.\n");
        return;
    }

    grapheexclusions->nbExclusions = 0;

    FILE *fichier;

    do{
        printf("Choisissez le fichier a ouvrir : 1)exclusions \n");
        scanf("%s", nomFichier);

        fichier = fopen(nomFichier, "r");

        //ici faut mettre le nb de sommets/nb arcs/tab exclusions et matrices adjacentes


        if (fichier == NULL) {
            printf("Impossible d'ouvrir le fichier.\n");
        }else {
            fclose(fichier);
        }
    } while (fichier == NULL);

    printf("Voici le contenu du fichier de exclusions : \n");
    afficherFichier(nomFichier);

    if (strcmp(nomFichier, "exclusions.txt") == 0) {
        grapheexclusions->nbExclusions = compterExclusions(nomFichier);

        if (grapheexclusions->nbExclusions == -1) {
            printf("Erreur lors de la lecture du fichier.\n");
        } else if (grapheexclusions->nbExclusions == 0) {
            printf("Le fichier est vide.\n");
        } else {
            printf("Le nombre de exclusions est de : %d\n", grapheexclusions->nbExclusions);
        }

    }
    else {
        printf("Le fichier n'est pas valide.\n");
    }

    free(grapheexclusions);
}