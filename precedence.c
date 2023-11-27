#include "precedence.h"


void precedence(t_graphe* graphe){
    //t_graphe* graphe;
    graphe = lirefichier();

    printf("graphe : %d", graphe->ordre);
    t_usine * usine = (t_usine*) malloc(sizeof(t_usine));
    usine = remplissagestation(graphe);
    affichageusine(usine);
    free(usine);
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



    t_maillon* repere = chaine->tete;
    //printf("\ndebut file\n");
    while (repere != NULL){
        //graphe->matrice[repere->depart][repere->fin] = 1;
        //printf("%d %d\n", repere->depart, repere->fin);
        repere = repere->suivant;
    }
    //printf("fin file\n");

    //printf("\n\n%d \n", graphe->nb_arete);


    //affichafge matrice adjacence
    for(int u = 0; u < graphe->ordre; u++){
        for(int j = 0; j < graphe->ordre; j++){
            printf("%d ", graphe->matrice[u][j]);
        }
        printf("\n");
    }

    //printf("\n\n\npour le 6 - 15 : %d\n\n", graphe->matrice[6][15]);


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


    free(chaine);
    return graphe;
}

t_usine * remplissagestation(t_graphe* graphe){
    t_usine * usine = creerusine();
    t_station * stationtemp = usine->stationtete;
    t_tache * tache = stationtemp->tachetete;

    int sanspred = 10;
    int compteurcolonne = 0;
    int compteurligne = 0;

    printf("\npredeceseur : \n");
    while (sanspred != 0) { //

        sanspred = 0;
        //trouver les taches sans prédécesseurs (donc les premières taches du graphe)
        for (int g = 0; g < graphe->ordre; g++) {
            printf("ligne %d\n",g);
            for (int h = 0; h < graphe->ordre; h++) {
                //printf("colonne %d\n", h);
                if (graphe->matrice[h][g] == 1) { //parcours colonne par colonne
                    //printf("colonne trouvé : ");
                    compteurcolonne++;
                    printf("%d \n", compteurcolonne);
                }
                if (graphe->matrice[g][h] == 1) { //parcours ligne par ligne
                    compteurligne++;
                    //printf("ligne toruvé : %d\n", compteurligne);
                }
            }
            if (compteurcolonne == 0 && compteurligne != 0) {
                printf("tache initiale trouvé\n");
                while (stationtemp != NULL){
                    ///A revoir
                    while (tache != NULL){
                        if(tache->numeroTache == g && tache->placer == 0){
                            printf("la tache est deja place\n");
                            sanspred = 1;
                            //printf("%d ", sanspred);
                        }
                        tache = tache->suivant;
                    }
                    stationtemp = stationtemp->suivant;
                }
                if(sanspred != 0){ //si la tache n'est pas deja placé
                    sanspred = g;
                }

            }

            compteurcolonne = 0;
            compteurligne = 0;
        }
        if(sanspred != 0) {
            //trouver la tache associé à ce numero
            t_tache *tachetemp = trouvertachenum(graphe, sanspred);

            //ajouter la tache a l'usine
            ajoutertachestationusine(tachetemp, usine, graphe);
            //ajouter cette tache à la premiere station disponible
        }
    }


    ///parcourir les predecesseurs ou suivant des taches ajoutés




    return usine;

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

void ajoutertachestationusine(t_tache* tache, t_usine* usine, t_graphe* graphe){
    printf("ajouter une tache\n");
    t_station * var = usine->stationtete;
    t_station * var2 = var;
    //trouver la permière station disponible pour la tache
    int bonnestation = 10;

    while (bonnestation != 0) {

        if(bonnestation == 1){ //si il y a dejà eut une boucle mais que ce n'était pas la bonne
            var = var->suivant;
        }
        bonnestation = 0;
        if (var == NULL) { //si la station est pleine créer une autre station
            var = creerstation(usine);
        }
        else {
            while ((var->dureetotal + tache->dureeTache) > var->dureemax) {
                var = var->suivant;
                if (var == NULL) { //si la station est pleine créer une autre station
                    var = creerstation(usine);
                }
            }
        }

        //verifier qu'il n'y a pas de tache precedente avant
        var2 = var->suivant;
        while(var2 != NULL){
            t_tache * temptache = var2->tachetete; //premiere tache de la station suivante
            while (temptache != NULL) {
                if (graphe->matrice[temptache->numeroTache][tache->numeroTache] == 1){ //si il y a un predecesseur dans l'une des stations d'après
                    bonnestation = 1;
                }
                temptache = temptache->suivant;
            }
            var2 = var2->suivant; //verifier toutes les stations suivantes
        }
    }

    //ajoutez la tache à la bonne station
    if(var->tachetete == NULL){
        var->tachetete = tache;
        var->tachefin = tache;
        tache->usuivant = NULL;
        tache->uprecedent = NULL;
        var->dureetotal += tache->dureeTache;
        tache->placer = 1;
    }
    else{
        var->tachefin->usuivant = tache;
        tache->uprecedent = var->tachefin;
        tache->usuivant = NULL;
        var->tachefin = tache;
        var->dureetotal += tache->dureeTache;
        tache->placer = 1;
    }
}

t_tache * trouvertachenum(t_graphe *graphe, int sanspred) {
    printf("recherche de tache\n");
    t_tache *temp = graphe->tetetache;
    while (temp->numeroTache != sanspred) {
        printf("1 ");
        temp = temp->suivant;
    }
    printf("tache trouve\n");
    return temp;
}

void affichageusine(t_usine* usine){
    t_station * station = usine->stationtete;
    t_tache * tache = station->tachetete;
    int compteur = 1;
    while (station != NULL){
        printf("\n\nStation %d : temps = %f\n", compteur, station->dureetotal);
        printf("Taches : ");
        while (tache != NULL){
            printf("%d ", tache->numeroTache);
            tache = tache->suivant;
        }
        compteur++;
        station = station->suivant;
    }
}

