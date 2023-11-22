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

int compterContraintes(char *nomFichier){
    FILE *fichier = fopen(nomFichier, "r");

    int nbContraintes = 0;
    char c = 0;

    while ((c = fgetc(fichier)) != EOF) {
        if (c == '\n') {
            nbContraintes++;
        }
    }

    fclose(fichier);
    return nbContraintes;
}



void menu(char *nomFichier) {
    t_grapheContraintes *grapheContraintes = malloc(sizeof(t_grapheContraintes));
    if (grapheContraintes == NULL) {
        printf("Erreur lors de l'allocation de la mémoire.\n");
        return;
    }

    grapheContraintes->nbContraintes = 0;

    FILE *fichier;

    do{
        printf("Choisissez le fichier a ouvrir : 1)contraintes \n");
        scanf("%s", nomFichier);

        fichier = fopen(nomFichier, "r");

        //ici faut mettre le nb de sommets/nb arcs/tab contraintes et matrices adjacentes


        if (fichier == NULL) {
            printf("Impossible d'ouvrir le fichier.\n");
        }else {
            fclose(fichier);
        }
    } while (fichier == NULL);

    printf("Voici le contenu du fichier de contraintes : \n");
    afficherFichier(nomFichier);

    if (strcmp(nomFichier, "contraintes.txt") == 0) {
        grapheContraintes->nbContraintes = compterContraintes(nomFichier);

        if (grapheContraintes->nbContraintes == -1) {
            printf("Erreur lors de la lecture du fichier.\n");
        } else if (grapheContraintes->nbContraintes == 0) {
            printf("Le fichier est vide.\n");
        } else {
            printf("Le nombre de contraintes est de : %d\n", grapheContraintes->nbContraintes);
        }

    }
    else {
        printf("Le fichier n'est pas valide.\n");
    }

    free(grapheContraintes);
}