#include "exclusion.h"

void exclusion(t_graphe* graphe){
    FILE * exclusion = fopen("exclusions.txt", "r"); //ouverture du fichier
    if(!exclusion){ //si le fichier ne s'ouvre pas
        printf("fichier exclusion introuvable"); // afficher message d'erreur
        exit(-1); //quitter le programme
    }

    graphe->mexclusion = (int**) malloc(graphe->ordre * sizeof (int *)); //allocation dynamique de la matrice
    for(int h = 0; h < graphe->ordre; h++){ //pour chaque ligne du tableau
        graphe->mexclusion[h] = (int*) malloc(graphe->ordre * sizeof (int)); //allouer dynamiquement un autre tableau pour former une matrice
    }

    for(int u = 0; u < graphe->ordre; u++){ //parcourir les lignes
        for(int j = 0; j < graphe->ordre; j++){ //parcourrir les colonnes
            graphe->mexclusion[u][j] = 0; //initialisation de toutes les cases de la matrice à 0
        }
    }

    int var1 = 0; //variable temporaire 1
    int var2 = 0; //variable temporaire 2
    while (fscanf(exclusion, "%d %d", &var1, &var2) != EOF){ //tant que le fichier n'est pas lu entierement -> poursuivre la lecture
        graphe->mexclusion[var1-1][var2-1] = 1; //mettre un 1 dans la matrice au coordonnée lu
        graphe->mexclusion[var2-1][var1-1] = 1; //même chose qu'en haut mais symétriquement
        //printf("%d %d\n", var1, var2);
    }

    /*
    for(int y = 0; y < graphe->ordre; y++){
        for(int u = 0; u < graphe->ordre; u++){
            printf("%d ", graphe->mexclusion[y][u]);
        }
        printf("\n");
    }
    printf("\n");
*/
    fclose(exclusion); //fermeture du fichier
}



