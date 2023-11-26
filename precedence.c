#include <stdio.h>
#include <stdlib.h>
//Sous programme qui fait la precedence de la chaine
#include "precedence.h"


void precedence(t_graphe* graphe){
    //t_graphe* graphe;
    graphe = lirefichier();
    printf("graphe : %d", graphe->ordre);
    free(graphe);
}

t_maillon * creermaillon(int depart, int fin){
    t_maillon* maillon = (t_maillon*) malloc(sizeof (t_maillon));
    maillon->depart = depart;
    maillon->fin = fin;
    return maillon;
}

t_chaine * creerchaine(){
    t_chaine * chaine = (t_chaine*) malloc(sizeof (t_chaine));
    chaine->tete = NULL;
    chaine->fin = NULL;
    return chaine;
}


t_graphe* lirefichier(){
    FILE * fichier = fopen("precedences.txt", "r");
    if(!fichier){
        printf("fichier introuvable");
        exit(-1);
    }
    t_graphe * graphe = (t_graphe*) malloc(sizeof(t_graphe));
    graphe->tetetache = NULL;
    graphe->fintache = NULL;
    int sommet_avant = 0;
    int sommet_apres = 0;
    graphe->nb_arete = 0;
    int nb_sommet = 0;
    int tableau[50];

    t_chaine* chaine = creerchaine();
    int max =0;

    while(fscanf(fichier, "%d %d", &sommet_avant, &sommet_apres) != EOF){
        graphe->nb_arete++;
        //printf("%d %d\n", sommet_avant, sommet_apres);
        t_maillon* maillon = creermaillon(sommet_avant, sommet_apres);
        enfiler(chaine, maillon);
        if(dejadanstab(sommet_avant, tableau, nb_sommet) == 0){
            tableau[nb_sommet] = sommet_avant;
            nb_sommet++;
        }
        if(dejadanstab(sommet_apres, tableau, nb_sommet) == 0){
            tableau[nb_sommet] = sommet_apres;
            nb_sommet++;
        }
        if(sommet_avant > max){
            max = sommet_avant;
        }
        if(sommet_apres > max){
            max = sommet_apres;
        }
    }

    printf("nb sommet : %d\n", nb_sommet);
    for(int l = 0; l < nb_sommet; l++){
        printf("%d ", tableau[l]);
    }

    graphe->ordre = max;
    graphe->matrice = (int**) malloc(graphe->ordre * sizeof (int *));
    for(int h = 0; h < graphe->ordre; h++){
        graphe->matrice[h] = (int*) malloc(graphe->ordre * sizeof (int));
    }
    graphe->tache = (int*) malloc(graphe->ordre * sizeof (int));

    for(int u = 0; u < graphe->ordre; u++){
        for(int j = 0; j < graphe->ordre; j++){
            graphe->matrice[u][j] = 0;
        }
    }

    for(int j = 0; j < graphe->ordre; j++){
        graphe->tache[j] = tableau[j];
    }

    rewind(fichier); //revenir en haut du fichier
    //fseek(fichier, 0, SEEK_SET);

/*
    fclose(fichier);

    FILE * fichier2 = fopen("precedences.txt", "r");
    if(!fichier2){
        printf("fichier introuvable");
        exit(-1);
    }*/


    for(int y = 0; y < graphe->nb_arete; y++){
        fscanf(fichier, "%d %d", &sommet_avant, &sommet_apres);
        graphe->matrice[sommet_avant][sommet_apres] = 1;
    }



///Le problème est que la matrice ne comporte pas tout les numéro car il y a des sommets qui ne sont pas dans le graphe


    t_maillon* repere = chaine->tete;
    //printf("\ndebut file\n");
    while (repere != NULL){
        //graphe->matrice[repere->depart][repere->fin] = 1;
        //printf("%d %d\n", repere->depart, repere->fin);
        repere = repere->suivant;
    }
    //printf("fin file\n");

    //printf("\n\n%d \n", graphe->nb_arete);


    for(int u = 0; u < graphe->ordre; u++){
        for(int j = 0; j < graphe->ordre; j++){
            printf("%d ", graphe->matrice[u][j]);
        }
        printf("\n");
    }

    printf("\n\n\npour le 6 - 15 : %d\n\n", graphe->matrice[6][15]);


    tacheassignation(chaine, graphe);
/*
    printf("\n\n");
    printf("debut tache duree\n");
    t_tache * temp = graphe->tetetache;
    while (temp != NULL){
        printf("%d %f\n", temp->numeroTache, temp->dureeTache);
        temp = temp->suivant;
    }
    printf("fin tache duree\n");
*/
    fclose(fichier);

    //lientempprecedence(graphe, chaine);
    remplissagestation(graphe);

    free(chaine);
    return graphe;
}

void remplissagestation(t_graphe* graphe){
    t_usine * usine = creerusine();
    t_station * stationtemp = usine->stationtete;
    //trouver la tache qui n'a pas de suivant (donc la dernière tache du graphe)
    //ou trouver la tache sans predecesseur (donc la permiere tache du graphe)

    //ajouter cette tache à la premiere station disponible
    //parcourir les predecesseurs ou suivant des taches ajoutés
    //verifier que la tache a déjà toit ses predecesseurs dans l'usine
    //si la station est pleine creer une autre station
    if(stationtemp->dureetotal == stationtemp->dureemax){
        stationtemp->suivant = creerstation(usine);
    }


}

int dejadanstab(int sommet,int tableau[50], int nb_sommet){
    int trouve = 0;
    for(int i = 0; i < nb_sommet; i++){
        if(sommet == tableau[i]){
            trouve = 1;
        }
    }
    return trouve;
}


void enfiler(t_chaine* chaine, t_maillon* maillon){
    if(chaine->tete == NULL){
        chaine->tete = maillon;
        chaine->fin = maillon;
        maillon->precedent = NULL;
        maillon->suivant = NULL;
    }
    else{
        chaine->fin->suivant = maillon;
        maillon->precedent = chaine->fin;
        maillon->suivant = NULL;
        chaine->fin = maillon;
    }
}

void tacheassignation(t_chaine* chaine, t_graphe* graphe){
    printf("temps\n");
    FILE * fichiertemps = fopen("temps.txt", "r");
    if(!fichiertemps){
        printf("fichier temps introuvable");
        exit(-1);
    }
    int tache;
    float duree;
    int compteur = 0;
    //printf("1");
    while(compteur < 30){
        //printf("2");
        fscanf(fichiertemps, "%d %f", &tache, &duree);
        t_tache* tachetemporaire = creertache(tache, duree);
        printf("%d %f\n", tache, duree);
        enfilerdansgraphe(graphe, tachetemporaire);
        compteur++;
    }
    //printf("3");
    printf("\n\n");
    /*
    printf("debut tache duree\n");
    t_tache * temp = graphe->tetetache;
    while (temp != NULL){
        printf("%d %f\n", temp->numeroTache, temp->dureeTache);
        temp = temp->suivant;
    }
    printf("fin tache duree\n");
     */

}

t_tache* creertache(int tachetemp, float duree){
    t_tache* tache = (t_tache*) malloc(sizeof (t_tache));
    tache->dureeTache = duree;
    tache->numeroTache = tachetemp;
    tache->placer = 0;

    /*
    tache->tacheprecedentetete = NULL; //(t_tache**)malloc(sizeof (t_tache*));
    tache->tachesuivantetete = NULL; //(t_tache**) malloc(sizeof (t_tache*));
    tache->tacheprecedentefin = NULL; //(t_tache**)malloc(sizeof (t_tache*));
    tache->tachesuivantefin = NULL; //(t_tache**) malloc(sizeof (t_tache*));
     */
    //printf("tache : %d %d /     duree : %f %f\n", tachetemp, tache->numeroTache, duree, tache->dureeTache);
    return tache;
}


void enfilerdansgraphe(t_graphe* graphe, t_tache* tache){
    if(graphe->tetetache == NULL){
        graphe->tetetache = tache;
        graphe->fintache = tache;
        tache->precedent = NULL;
        tache->suivant = NULL;
    }
    else{
        graphe->fintache->suivant = tache;
        tache->precedent = graphe->fintache;
        tache->suivant = NULL;
        graphe->fintache = tache;
    }
}

void lientempprecedence(t_graphe* graphe, t_chaine* chaine){
    t_maillon* test = chaine->tete;
    t_tache* vartemp = graphe->tetetache;
    while (test != NULL){
        while (vartemp != NULL){
            if (test->depart == vartemp->numeroTache){
                //enfiler dans la file des suivantes sur la tache

            }
            if(test->fin == vartemp->numeroTache){
                //enfiler dans la file des précédent sur la tache
            }


            vartemp = vartemp->suivant;
        }

        test = test->suivant;
    }
}

void enfilertachedanstache(t_tache* nouveau, t_tache* base){
    /*
    if(base->tacheprecedentetete == NULL){
        base->tacheprecedentetete = nouveau;
        base->tacheprecedentefin = nouveau;
        nouveau->precedent = NULL;
        nouveau->suivant = NULL;
    }
    else{
        base->tacheprecedentefin. = maillon;
        maillon->precedent = chaine->fin;
        maillon->suivant = NULL;
        chaine->fin = maillon;
    }
     */
}


t_usine * creerusine(){
    t_usine * nouvelusine = (t_usine*) malloc(sizeof (t_usine));
    nouvelusine->stationtete = NULL;
    nouvelusine->stationfin = NULL;
    t_station * nouvstation = creerstation(nouvelusine);
    nouvelusine->stationtete = nouvstation;
    nouvelusine->stationfin = nouvstation;
    return nouvelusine;
}

t_station * creerstation(t_usine* nouvelusine){
    t_station * nouvstation = (t_station*) malloc(sizeof(t_station));
    nouvstation->dureemax = 10;
    nouvstation->dureetotal = 0;
    nouvstation->tachetete = NULL;
    nouvstation->tachefin = NULL;
    nouvstation->suivant = NULL;
    nouvstation->precedent = NULL;

    if(nouvelusine->stationtete == NULL){
        nouvelusine->stationtete = nouvstation;
        nouvelusine->stationfin = nouvstation;

    }
    else{
        nouvstation->precedent = nouvelusine->stationfin;
        nouvelusine->stationfin->suivant = nouvstation;
        nouvelusine->stationfin = nouvstation;
    }
    return nouvstation;
}

