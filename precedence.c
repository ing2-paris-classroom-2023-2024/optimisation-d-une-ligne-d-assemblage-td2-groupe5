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

//Affichage des sommets

    printf("les sommets : %d\n", nb_sommet);
    for(int l = 0; l < nb_sommet; l++){
        printf("%d ", tableau[l]);
    }
    printf("\n\n");


    graphe->nbsommetfini = 0;
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


    for(int y = 0; y < graphe->nb_arete; y++){
        fscanf(fichier, "%d %d", &sommet_avant, &sommet_apres);
        graphe->matrice[sommet_avant-1][sommet_apres-1] = 1;
    }



    //affichafge matrice adjacence
    /*
    printf("\n\n");
    for(int u = 0; u < graphe->ordre; u++){
        for(int j = 0; j < graphe->ordre; j++){
            printf("%d ", graphe->matrice[u][j]);
        }
        printf("\n");
    }
*/


    tacheassignation(chaine, graphe);

    fclose(fichier);

    free(chaine);
    return graphe;
}

t_usine * remplissagestation(t_graphe* graphe){
    t_usine * usine = creerusine(); //créer l'usine
    tachesinitiales(graphe, usine); //taches initiales du graphe
    autrestaches(usine, graphe); //mettre les autres taches dans l'usine

    return usine;
}

void tachesinitiales(t_graphe *graphe, t_usine *usine) {
    t_station * stationtemp = usine->stationtete;
    t_tache * tache = stationtemp->tachetete;
    t_tache * numerodetache = NULL;
    int sanspred = 0;
    int compteurcolonne = 0;
    int compteurligne = 0;


    //trouver les taches sans prédécesseurs (donc les premières taches du graphe)
    for (int g = 0; g < graphe->ordre; g++) {
        compteurcolonne = 0;
        compteurligne = 0;
        for (int h = 0; h < graphe->ordre; h++) {
            if (graphe->matrice[h][g] == 1) { //parcours colonne par colonne
                compteurcolonne++;
            }
            if (graphe->matrice[g][h] == 1) { //parcours ligne par ligne
                compteurligne++;
            }
        }
        if(compteurligne == 0 && compteurcolonne == 0){
            sanspred = 0;
        }else {
            numerodetache = trouvertachenum(graphe, g+1);

            if (compteurcolonne == 0 && compteurligne != 0 && numerodetache->placer == 0) { //si la tache n'a pas de précédent, a des suivants et n'est pas placé
                sanspred = 1; //tache à placer

            } else {
                sanspred = 0;
            }
        }

        if (sanspred == 1) {
            //trouver la tache associé à ce numero
            t_tache *tachetemp = trouvertachenum(graphe, g+1);
            //ajouter la tache a l'usine
            ajoutertachestationusine(tachetemp, usine, graphe);
            //ajouter cette tache à la premiere station disponible
        }
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

void tacheassignation(t_chaine* chaine, t_graphe* graphe) {

    FILE * fichiertemps = fopen("temps.txt", "r");
    if(!fichiertemps){
        printf("fichier temps introuvable");
        exit(-1);
    }
    int tache = 0;
    float duree = 0.1;
    int compteur = 0;

    while(compteur < 30){
        fscanf(fichiertemps, "%d %f", &tache, &duree);
        t_tache* tachetemporaire = creertache(tache, duree);
        enfilerdansgraphe(graphe, tachetemporaire);
        compteur++;
    }

    graphe->nbdetachetemp = compteur +1;


}

t_tache* creertache(int tachetemp, float duree){
    t_tache* tache = (t_tache*) malloc(sizeof (t_tache));
    tache->dureeTache = duree;
    tache->numeroTache = tachetemp;
    tache->placer = 0;
    tache->usuivant = NULL;
    tache->uprecedent = NULL;
    tache->precedent = NULL;
    tache->suivant = NULL;


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
    FILE * fichier3 = fopen("tempsmax.txt", "r");
    if(!fichier3){
        printf("fichier tempsmax introuvable");
        exit(-1);
    }
    float max;
    fscanf(fichier3, "%f ", &max);
    nouvstation->dureemax = max;
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
    fclose(fichier3);
    return nouvstation;
}

void ajoutertachestationusine(t_tache* tache, t_usine* usine, t_graphe* graphe){
    if(tache->placer == 0) {
        t_station *var = usine->stationtete;
        t_station *var2 = NULL;
        t_tache *temptache;
        //trouver la permière station disponible pour la tache
        int bonnestation = 10;

        while (bonnestation != 0) {

            if (bonnestation == 1) { //si il y a dejà eut une boucle mais que ce n'était pas la bonne
                var = var->suivant;
            }
            bonnestation = 0;
            if (var == NULL) { //si la station est pleine créer une autre station
                var = creerstation(usine);
            } else {
                while ((var->dureetotal + tache->dureeTache) > var->dureemax) {
                    var = var->suivant;
                    if (var == NULL) { //si la station est pleine créer une autre station
                        var = creerstation(usine);
                    }
                }
            }

            //verifier qu'il n'y a pas de tache precedente avant


            var2 = var->suivant;
            if(var2 != NULL) {
                temptache = var2->tachetete; //premiere tache de la station suivante
                while (temptache != NULL) {
                    if (graphe->matrice[temptache->numeroTache - 1][tache->numeroTache - 1] == 1) { //si il y a un predecesseur dans l'une des stations d'après
                        bonnestation = 1;
                    }
                    temptache = temptache->suivant;
                }
            }
        }

        //ajoutez la tache à la bonne station
        if (var->tachetete == NULL) {
            var->tachetete = tache;
            var->tachefin = tache;
            tache->usuivant = NULL;
            tache->uprecedent = NULL;
            var->dureetotal += tache->dureeTache;
            tache->placer = 1;
        } else {
            var->tachefin->usuivant = tache;
            tache->uprecedent = var->tachefin;
            tache->usuivant = NULL;
            var->tachefin = tache;
            var->dureetotal += tache->dureeTache;
            tache->placer = 1;
        }

        graphe->nbsommetfini++;

    }
}

t_tache * trouvertachenum(t_graphe *graphe, int num) {
    //printf("recherche de tache\n");
    t_tache *temp = graphe->tetetache;
    int trouve = 0;
    while (temp != NULL){
        if(temp->numeroTache == num){
            trouve = 1;
        }
        temp = temp->suivant;
    }
    temp = graphe->tetetache;
    if(trouve == 1) {
        while (temp->numeroTache != num) {
            temp = temp->suivant;
        }
    }
    else{
        //si la tache n'existe pas on l'a créée
        temp = creertache(num, 0);
        //on l'ajoute au graphe
        enfilerdansgraphe(graphe, temp);
    }

    return temp;
}

void affichageusine(t_usine* usine){
    t_station * station = usine->stationtete;
    t_tache * tache = station->tachetete;
    int compteur = 1;
    while (station != NULL){
        printf("\n\nStation %d : temps = %f\n", compteur, station->dureetotal);
        printf("Taches : ");
        tache = station->tachetete;
        while (tache != NULL){
            printf("%d ", tache->numeroTache);
            tache = tache->usuivant;
        }
        compteur++;
        station = station->suivant;
    }
    printf("\n\n");
}

void autrestaches(t_usine* usine, t_graphe* graphe){
    t_station * stationtemp = usine->stationtete;
    t_tache * tache = stationtemp->tachetete;
    t_tache * temp;
    t_tache * tempred;
    int erreur = 0;
    int aplacer = 0;

    //parcourir les suivants des arretes déjà validé
    while (stationtemp != NULL){ //parcours de toutes les stations de l'usine
        tache = stationtemp->tachetete;
        while (tache != NULL){ //parcours de toutes les taches de l'usine
            erreur = 0;
            aplacer = 0;
            for(int j = 0; j < graphe->ordre; j++){ //parcours de la matrice d'adjacence sur la ligne voulu
                erreur = 0;
                if(graphe->matrice[tache->numeroTache-1][j] == 1) { //suivant trouve
                    temp = trouvertachenum(graphe, j + 1); //le suivant s'appelle temp
                    if (temp->placer == 0) { //si la tache n'est pas déjà placé
                        aplacer = 1;
                    }


                    for (int m = 0; m < graphe->ordre; m++) { //parcours des predecesseurs
                        if (graphe->matrice[m][temp->numeroTache - 1] == 1) { //si predecesseur trouve
                            tempred = trouvertachenum(graphe, m + 1); //toruver la tache precedante
                            if (tempred->placer == 0) { //si la tache precedente n'est pas place
                                erreur++; //ajouter 1 à l'erreur
                            }
                        }
                    }
                    if (aplacer == 1 && erreur == 0) { //si on peut la placer et qu'il n'y a pas d'erreur
                        ajoutertachestationusine(temp, usine, graphe); //ajouter la tache
                    }

                }
            }

            tache = tache->usuivant; //passer à la tache suivante dans l'usine

        }

        stationtemp = stationtemp->suivant; //passer à la station suivante
    }

}