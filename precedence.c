#include "precedence.h"
#include "exclusion.c"



void precedence(t_graphe* graphe){
    graphe = lirefichier(); //lire le fichier et remplissage du graphe
    t_usine * usine = remplissagestation(graphe); //créer une usine et la remplir
    affichageusine(usine); //afficher l'usine
    free(usine); //libérer la mémoire usine
    free(graphe);//libéré la mémoire grpahe
}

t_graphe* lirefichier(){//lecture fichier precedence
    FILE * fichier = fopen("precedences.txt", "r"); //ouvrir le fichier des précédences
    if(!fichier){//si le fichier n'est pas ouvert
        printf("fichier introuvable"); //afficher message erreur
        exit(-1); //sortir du programme
    }
    t_graphe * graphe = (t_graphe*) malloc(sizeof(t_graphe)); //allocation dynamique
    graphe->tetetache = NULL; //initialistaion de la file des taches
    graphe->fintache = NULL;//initialistaion de la file des taches
    int sommet_avant = 0;//initialistaion valeur de lecture 1
    int sommet_apres = 0;//initialistaion valeur de lecture 2
    graphe->nb_arete = 0;//initialistaion valeur comptage
    int nb_sommet = 0;//initialistaion nombre de sommet
    int tableau[50];//tableau de stockage des sommets dejà lu et créer

    //application des contraintes :
    graphe->time = 0; //temps
    graphe->excl = 0; //exclusion
    graphe->preced = 0; //precedence

    menu(graphe); //appel du menu

    int max =0; //le sommet maximum et aussi l'ordre du graphe et des matrices

    while(fscanf(fichier, "%d %d", &sommet_avant, &sommet_apres) != EOF){ //lire le fichier tant que la fin n'est pas trouvé
        graphe->nb_arete++; //ajouté 1 au nombre d'arc


        if(dejadanstab(sommet_avant, tableau, nb_sommet) == 0){ //si le sommet 1 n'est pas dans le tableau
            tableau[nb_sommet] = sommet_avant; //ajouter le sommet au tableau
            nb_sommet++; //ajouter 1 au nombre de sommet du tableau
        }
        if(dejadanstab(sommet_apres, tableau, nb_sommet) == 0){//si le sommet 2 n'est pas dans le tableau
            tableau[nb_sommet] = sommet_apres;//ajouter le sommet 2 au tableau
            nb_sommet++; //ajouter 1 au nombre de sommet du tableau
        }
        if(sommet_avant > max){ //si le sommet 1 est superieur au max
            max = sommet_avant; //redefinir le max
        }
        if(sommet_apres > max){//si le sommet 1=2 est superieur au max
            max = sommet_apres;//redefinir le max
        }
    }

    graphe->nbsommetfini = 0;
    graphe->ordre = max; //ordre vaut le numero max des sommets lu
    graphe->matrice = (int**) malloc(graphe->ordre * sizeof (int *));//allocation dynamique
    for(int h = 0; h < graphe->ordre; h++){
        graphe->matrice[h] = (int*) malloc(graphe->ordre * sizeof (int));//allocation dynamique
    }
    graphe->tache = (int*) malloc(graphe->ordre * sizeof (int));//allocation dynamique

    for(int u = 0; u < graphe->ordre; u++){ //parcourir la matrice de précédence
        for(int j = 0; j < graphe->ordre; j++){
            graphe->matrice[u][j] = 0; //initialiser toutes les valeurs à 0
        }
    }

    for(int j = 0; j < graphe->ordre; j++){ //parcourir le tableau des sommets lu
        graphe->tache[j] = tableau[j]; //le copier dans la liste des taches du graphe
    }

    exclusion(graphe); //lecture du fichier exclusion

    rewind(fichier); //revenir en haut du fichier


    for(int y = 0; y < graphe->nb_arete; y++){ //relire les aretes
        fscanf(fichier, "%d %d", &sommet_avant, &sommet_apres); //lecture des aretes
        graphe->matrice[sommet_avant-1][sommet_apres-1] = 1; //mettre les précédence dans la matrice de précédednce
    }


    tacheassignation(graphe);

    fclose(fichier);


    return graphe;
}

t_usine * remplissagestation(t_graphe* graphe){ //remplissage des station
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
        if(compteurligne == 0 && compteurcolonne == 0){ //si aucun précédent ni suivante
            sanspred = 0;
        }else {
            numerodetache = trouvertachenum(graphe, g+1); //toruver la tache de numéro g+1

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
            ajoutertachestationusine(tachetemp, usine, graphe, stationtemp);
            //ajouter cette tache à la premiere station disponible
        }
    }


}

int dejadanstab(int sommet,int tableau[50], int nb_sommet){
    int trouve = 0; //initialisation de la valeur test
    for(int i = 0; i < nb_sommet; i++){ //pour toutes les valeurs du tableau
        if(sommet == tableau[i]){ //si le nombre a déjà été placé
            trouve = 1; //nombre trouvé
        }
    }
    return trouve; //renvoie si le nombre à été trouvé ou pas
}

void tacheassignation(t_graphe* graphe) {
    FILE * fichiertemps = fopen("temps.txt", "r"); //lire fichier txt
    if(!fichiertemps){ //si fichier pas ouvert
        printf("fichier temps introuvable"); //message d'erreur
        exit(-1); //quitter le programme
    }
    int tache = 0;
    float duree = 0.0;
    int compteur = 0;
    while(fscanf(fichiertemps, "%d %f", &tache, &duree) != EOF){ //tant que ce n'est pas laa fin du fichier
        t_tache* tachetemporaire = creertache(tache, duree); //assignier la durée à une tache
        enfilerdansgraphe(graphe, tachetemporaire); //enfiler dans la file de tachhe du graphe
        compteur++; //ajouter 1 au compteur
    }

    graphe->nbdetachetemp = compteur +1;

    fclose(fichiertemps);
}

t_tache* creertache(int tachetemp, float duree){ //creer la tache
    t_tache* tache = (t_tache*) malloc(sizeof (t_tache)); //allocation dynamique
    tache->dureeTache = duree; //assignation de la durée
    tache->numeroTache = tachetemp; //numéro de tache
    tache->placer = 0;//pas placé
    tache->usuivant = NULL; //initialisation des files
    tache->uprecedent = NULL;//initialisation des files
    tache->precedent = NULL;//initialisation des files
    tache->suivant = NULL;//initialisation des files

    return tache; //renvoyer la taches créer
}

void enfilerdansgraphe(t_graphe* graphe, t_tache* tache){ //mettre une tache dans le graphe
    if(graphe->tetetache == NULL){ //si la file du graphe est nulle
        graphe->tetetache = tache; //tache est la seule tache de la file
        graphe->fintache = tache;
        tache->precedent = NULL;
        tache->suivant = NULL;
    }
    else{ //si la file n'est pas vide
        graphe->fintache->suivant = tache; //ajouter la tache à la fin
        tache->precedent = graphe->fintache;
        tache->suivant = NULL;
        graphe->fintache = tache;
    }
}

t_usine * creerusine(){ //creer une usine
    t_usine * nouvelusine = (t_usine*) malloc(sizeof (t_usine)); //allocation dynamique
    nouvelusine->stationtete = NULL; //initialisation des files
    nouvelusine->stationfin = NULL;//initialisation des files
    t_station * nouvstation = creerstation(nouvelusine); //creer la première station
    nouvelusine->stationtete = nouvstation; //mettre la nouvel station dans l'usine
    nouvelusine->stationfin = nouvstation;//mettre la nouvel station dans l'usine
    return nouvelusine; //renvoyer l'usine
}

t_station * creerstation(t_usine* nouvelusine){ //créer les stations des usines
    t_station * nouvstation = (t_station*) malloc(sizeof(t_station)); //allocation dynamique
    FILE * fichier3 = fopen("tempsmax.txt", "r"); //ouvrir fichier tempsmax.txt
    if(!fichier3){ //si le fichier ne s'ouvre pas
        printf("fichier tempsmax introuvable"); //afficher un message d'erreur
        exit(-1); //sortir du programme
    }
    float max; //variable de lecture
    fscanf(fichier3, "%f ", &max); //lire la valeur du fichier
    nouvstation->dureemax = max; //assigner
    nouvstation->dureetotal = 0; //durée total initialisé à 0
    nouvstation->tachetete = NULL; //initialisation file
    nouvstation->tachefin = NULL;//initialisation file
    nouvstation->suivant = NULL;//initialisation file usine
    nouvstation->precedent = NULL;//initialisation file usine

    if(nouvelusine->stationtete == NULL){ //si l'usine est vide
        nouvelusine->stationtete = nouvstation; //la seule station de l'usine est la nouvelle station
        nouvelusine->stationfin = nouvstation;

    }
    else{ //si l'usine n'est pas vide
        nouvstation->precedent = nouvelusine->stationfin; //ajouter la nouvelle station à la fin
        nouvelusine->stationfin->suivant = nouvstation;
        nouvelusine->stationfin = nouvstation;
    }
    fclose(fichier3); //fermer le fichier
    return nouvstation; //renvoyer la nouvelle station
}

void ajoutertachestationusine(t_tache* tache, t_usine* usine, t_graphe* graphe, t_station * stationmin){ //ajouter les taches à la station de l'usine
    if(tache->placer == 0) { //si la tache n'est pas placé
        t_station *var = stationmin; //on part de la station de la tache précédente
        t_station *var2 = NULL; //initialisation
        t_tache *temptache; //init

        //trouver la permière station disponible pour la tache
        int bonnestation = 10; //initi
        int exclusion = 2;//initi
        int compteur =0;//initi


        while (bonnestation != 0) { //tant que bonne station pas trouvé

            if (bonnestation == 1) { //si il y a dejà eut une boucle mais que la precedence ne marchait pas
                var = var->suivant; //passer à la station suivante
                exclusion = 2; //initi
                if (var == NULL) { //si la station est pleine créer une autre station
                    var = creerstation(usine); //créer la prochaine station
                }
            }
            bonnestation = 0; //initi
            if (var == NULL) { //si la station est pleine créer une autre station
                var = creerstation(usine);//créer la prochaine station
            } else {

                compteur = 0; //initi
                while (exclusion != 0) { //tant que les exclusion ne sont pas bonnes
                    exclusion = 0; //initi

                    ///contrainte de temps : trouvé une station qui à la capacité temporel d'accueillir la nouvel tache
                    if(graphe->time == 1) {
                        while ((var->dureetotal + tache->dureeTache) > var->dureemax) { //tant que la durée total avec le nouveau temps est supérieur au max
                            var = var->suivant; //tache suivante
                            if (var == NULL) { //si la station est pleine créer une autre station
                                var = creerstation(usine); //creer une nouvel station
                            }
                        }
                    }

                    ///contrainte d'exclusion : certaine tache ne doivent pas être ensemble
                    if(graphe->excl == 1) {
                        temptache = var->tachetete; //tache de tete de la station visé
                        while (temptache != NULL) { //parcourir toutes les taches de la station
                            if (graphe->mexclusion[temptache->numeroTache - 1][tache->numeroTache - 1] ==
                                1) { //si il y a une tache incompatible avec celle à ajouter
                                exclusion++; //noter
                            }
                            temptache = temptache->usuivant; //passer à la tache suivante
                        }

                        if (exclusion != 0) { //si il y a une tache incompatible
                            var = var->suivant; //passer à la station suivante
                            if (var == NULL) { //si la station est pleine créer une autre station
                                var = creerstation(usine); //creer une station
                            }
                            exclusion = 1; //mettre l'exclusion à 1 pour le haut de la boucle
                            compteur++; //compteur 1 pt
                        }
                    }
                    else{
                        exclusion = 0;
                    }

                }
            }


            var2 = var->suivant; //variable des station suivante

            ///contrainte de précédence : la tache ne doit pas etre réalisé avant ses précédentes ni après ses suivantes
            if(graphe->preced == 1) {
                if (var2 != NULL) { //tant que les stations n'ont pas toutes été controlé
                    temptache = var2->tachetete; //premiere tache de la station suivante
                    while (temptache != NULL) { //parcourir toutes les taches de la station
                        if (graphe->matrice[temptache->numeroTache - 1][tache->numeroTache - 1] ==
                            1) { //si il y a un predecesseur dans l'une des stations d'après
                            bonnestation = 1; //marqué que la station n'est pas la bonne pour le haut du ss prog
                        }
                        temptache = temptache->usuivant;//passer à la variable suivante
                    }
                    var2 = var2->suivant; //verifier toutes les stations suivantes
                }
            }
            else{
                bonnestation = 0;
            }

        }


        //ajoutez la tache à la bonne station
        if (var->tachetete == NULL) { //si la station est vide
            var->tachetete = tache; //la seule tache de la station est la nouvelle tache
            var->tachefin = tache;
            tache->usuivant = NULL;
            tache->uprecedent = NULL;
            var->dureetotal += tache->dureeTache;//ajouté la durée de la tache à la duree de la station
            tache->placer = 1; //mettre comme placé
        } else { //si la station n'est pas vide
            var->tachefin->usuivant = tache; //ajouter à la fin
            tache->uprecedent = var->tachefin;
            tache->usuivant = NULL;
            var->tachefin = tache;
            var->dureetotal += tache->dureeTache; //ajouté la durée de la tache à la duree de la station
            tache->placer = 1; //mettre comme placé
        }

        graphe->nbsommetfini++; //ajouter 1 au nombre de somemt fini

    }
}

t_tache * trouvertachenum(t_graphe *graphe, int num) { //renvoyer la tache correspondant à un numéro donné
    t_tache *temp = graphe->tetetache; //tache temporaire
    int trouve = 0; //pas trouvé
    while (temp != NULL){ //tant que la tache n'est pas trouvé
        if(temp->numeroTache == num){ //si le numéro de la tache parccouru est le numéro de la tache à trouvé
            trouve = 1; //mettre comme trouvé
        }
        temp = temp->suivant; //passer à la tache suivante
    }
    temp = graphe->tetetache; //retourner au début de la liste des tache
    if(trouve == 1) { //si la tache a ete trouvé
        while (temp->numeroTache != num) { //tant que la tache parcourut n'a pas le bon numéro
            temp = temp->suivant; //on passe à la tache suivante
        }
    }
    else{ //si la tache n'existe pas encore
        temp = creertache(num, 0);// on l'a créée
        enfilerdansgraphe(graphe, temp);//on l'ajoute au graphe
    }

    return temp; //renvoyer la tache
}

void affichageusine(t_usine* usine){ //affichage de l'usine
    t_station * station = usine->stationtete; //partir de la première station de l'usine
    t_tache * tache = station->tachetete; //partir de la première tache de la station visé
    int compteur = 1; //compteur de station
    while (station != NULL){ //parcourir toutes les stations
        printf("\n\nStation %d : temps = %f\n", compteur, station->dureetotal); //afficher le numéro de la station et sa durée total
        printf("Taches : "); //affichage
        tache = station->tachetete;//partir de la première tache de la station visé
        while (tache != NULL){ //parcourir les taches de la station
            printf("%d ", tache->numeroTache); //afficher leur numéro
            tache = tache->usuivant; //passer à la tache suivante
        }
        compteur++; //numéro station suivante
        station = station->suivant;//station suivante
    }
    printf("\n\n"); //affichage
}

void autrestaches(t_usine* usine, t_graphe* graphe){ //toruver les taches non initiales
    t_station * stationtemp = usine->stationtete; //premiere station de l'usine
    t_tache * tache = stationtemp->tachetete; //permiere tache de la station
    t_tache * temp; //temporaire
    t_tache * tempred; //temporaire 2
    int erreur = 0; //variable
    int aplacer = 0; //variable

    //parcourir les suivants des arretes déjà validé
    while (stationtemp != NULL){ //parcours de toutes les stations de l'usine
        tache = stationtemp->tachetete; //permiere tache de la station
        while (tache != NULL){ //parcours de toutes les taches de l'usine
            erreur = 0;//variable
            aplacer = 0;//variable

            for(int j = 0; j < graphe->ordre; j++){ //parcours de la matrice d'adjacence sur la ligne voulu
                erreur = 0;//variable d'erreur
                if(graphe->matrice[tache->numeroTache-1][j] == 1) { //suivant trouve
                    temp = trouvertachenum(graphe, j + 1); //le suivant s'appelle temp
                    if (temp->placer == 0) { //si la tache n'est pas déjà placé
                        aplacer = 1; //indiquer comme  a placer
                    }


                    for (int m = 0; m < graphe->ordre; m++) { //parcours des predecesseurs
                        if (graphe->matrice[m][temp->numeroTache - 1] == 1) { //si predecesseur trouve
                            tempred = trouvertachenum(graphe, m + 1); //trouver la tache precedante
                            if (tempred->placer == 0) { //si la tache precedente n'est pas place
                                erreur++; //ajouter 1 à l'erreur
                            }
                        }
                    }
                    if (aplacer == 1 && erreur == 0) { //si on peut la placer et qu'il n'y a pas d'erreur
                        ajoutertachestationusine(temp, usine, graphe, stationtemp); //ajouter la tache
                    }
                }
            }

            tache = tache->usuivant; //passer à la tache suivante dans l'usine

        }
        stationtemp = stationtemp->suivant; //passer à la station suivante
    }

}


void menu(t_graphe* graphe){
    int menuchoix = 0;
    while (menuchoix > 7 || menuchoix < 1){
        printf("MENU :\n");
        printf("Quelle contrainte voulez vous utiliser ?\n");
        printf("1- temps\n2- exclusion\n3-precedence et temps\n4-temps et exclusion\n5- precedence et exclusion\n6- temps, exclusion et precedence\n");
        printf("7- quitter\n");
        scanf("%d",&menuchoix);
    }
    if(menuchoix == 1 || menuchoix == 3 || menuchoix == 4 || menuchoix == 6){
        graphe->time = 1;
    }
    if(menuchoix == 2 || menuchoix == 4 || menuchoix == 5 || menuchoix == 6){
        graphe->excl = 1;
    }
    if(menuchoix == 3 || menuchoix == 5 || menuchoix == 6){
        graphe->preced = 1;
    }
    if(menuchoix == 7){
        exit(1);
    }

}