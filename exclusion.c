#include "exclusion.h"

void exclusion(t_graphe* graphe){
    FILE * exclusion = fopen("exclusions.txt", "r");
    if(!exclusion){
        printf("fichier exclusion introuvable");
        exit(-1);
    }

    graphe->mexclusion = (int**) malloc(graphe->ordre * sizeof (int *));
    for(int h = 0; h < graphe->ordre; h++){
        graphe->mexclusion[h] = (int*) malloc(graphe->ordre * sizeof (int));
    }

    for(int u = 0; u < graphe->ordre; u++){
        for(int j = 0; j < graphe->ordre; j++){
            graphe->mexclusion[u][j] = 0;
        }
    }

    int var1 = 0;
    int var2 = 0;
    while (fscanf(exclusion, "%d %d", &var1, &var2) != EOF){
        graphe->mexclusion[var1-1][var2-1] = 1;
        graphe->mexclusion[var2-1][var1-1] = 1;
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
    fclose(exclusion);
}



