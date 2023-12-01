//
// Created by shaima on 23/11/2023.
//

#include "source.h" //bibliothèque contenant les prototypes des fonctions et les structures

void liberer_graphe(t_grapheS *graphe) { //fonction qui libère la mémoire allouée pour le graphe

    for (int i = 0; i < graphe->nombredesommet; i++) { //parcours de la matrice d'adjacence
        free(graphe->matriceadjacente[i]); //libération de la mémoire allouée pour chaque ligne de la matrice d'adjacence
        free(graphe->sommets[i].voisins); //libération de la mémoire allouée pour chaque ligne du tableau des voisins
    }
    free(graphe->matriceadjacente); //libération de la mémoire allouée pour la matrice d'adjacence
    free(graphe->sommets); //libération de la mémoire allouée pour le tableau des sommets
    free(graphe); //libération de la mémoire allouée pour le graphe
}

int classerdecroissancesommets(const void *a, const void *b) { //fonction de comparaison pour le tri des sommets
    t_sommet *sommet1 = (t_sommet *)a; //on cast le void * en t_sommet * pour pouvoir accéder aux champs de la structure t_sommet
    t_sommet *sommet2 = (t_sommet *)b; //on cast le void * en t_sommet * pour pouvoir accéder aux champs de la structure t_sommet
    return (sommet2->degre - sommet1->degre); //on retourne la différence entre le degré du sommet 2 et le degré du sommet 1
}

void trier_sommets_decroissant(t_grapheS *graphe) { //fonction qui trie les sommets du graphe par ordre décroissant de degré
    qsort(graphe->sommets, graphe->nombredesommet, sizeof(t_sommet), classerdecroissancesommets); //appel de la fonction qsort qui trie les sommets du graphe par ordre décroissant de degré
} //qsort est une fonction de la bibliothèque standard du langage C qui permet de trier un tableau

void compter_sommets_arcs(char *nom_fichier, int *nombredesommet, int *nombredarcs) { //fonction qui compte le nombre de sommets et d'arcs dans le fichier

    FILE *fichier = fopen(nom_fichier, "r"); //ouverture du fichier en mode lecture
    if (fichier == NULL) { //si le fichier n'est pas ouvert ou n'existe pas
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier); //affichage d'un message d'erreur
        exit(EXIT_FAILURE); //arrêt du programme
    } //sinon
    int sommet1, sommet2; //déclaration des variables sommet1 et sommet2
    *nombredesommet = 0; //initialisation du nombre de sommets à 0
    *nombredarcs = 0; //initialisation du nombre d'arcs à 0
    while (fscanf(fichier, "%d %d", &sommet1, &sommet2) != EOF) { //tant qu'on n'est pas à la fin du fichier
        if (sommet1 > *nombredesommet) { //si le sommet 1 est supérieur au nombre de sommets
            *nombredesommet = sommet1; //le nombre de sommets prend la valeur du sommet 1
        }
        if (sommet2 > *nombredesommet) { //si le sommet 2 est supérieur au nombre de sommets
            *nombredesommet = sommet2; //le nombre de sommets prend la valeur du sommet 2
        } //on fait cela pour avoir le nombre de sommets maximum
        (*nombredarcs)++; //on incrémente le nombre d'arcs
    } //on fait cela pour avoir le nombre d'arcs
    fclose(fichier); //fermeture du fichier
    (*nombredesommet)++; //on incrémente le nombre de sommets pour avoir le nombre de sommets réel
}

t_grapheS *creer_graphe(int nombredesommet, int nombredarcs) { //fonction qui crée un graphe

    t_grapheS *graphe = malloc(sizeof(t_grapheS)); //allocation de la mémoire pour le graphe
    graphe->nombredesommet = nombredesommet; //initialisation du nombre de sommets
    graphe->nombredarcs = nombredarcs; //initialisation du nombre d'arcs
    graphe->sommets = malloc(nombredesommet * sizeof(t_sommet)); //allocation de la mémoire pour le tableau des sommets
    graphe->matriceadjacente = malloc(nombredesommet * sizeof(int *)); //allocation de la mémoire pour la matrice d'adjacence
    for (int i = 0; i < nombredesommet; i++) { //parcours de la matrice d'adjacence
        graphe->matriceadjacente[i] = malloc(nombredesommet * sizeof(int)); //allocation de la mémoire pour chaque ligne de la matrice d'adjacence
        for (int j = 0; j < nombredesommet; j++) { //parcours de la matrice d'adjacence
            graphe->matriceadjacente[i][j] = 0; //initialisation de la matrice d'adjacence à 0
        } //on fait cela pour avoir une matrice d'adjacence vide
    }
    for (int i = 0; i < nombredesommet; i++) { //parcours de la matrice d'adjacence
        graphe->sommets[i].identite = i; //initialisation de l'identité du sommet
        graphe->sommets[i].degre = 0; //initialisation du degré du sommet
        graphe->sommets[i].voisins = malloc(nombredesommet * sizeof(int)); //allocation de la mémoire pour le tableau des voisins
    } //on fait cela pour avoir un tableau des voisins vide
    return graphe; //on retourne le graphe
}

t_grapheS *lire_graphe(char *nom_fichier) { //fonction qui lit un graphe à partir d'un fichier

    int nombredesommet, nombredarcs; //déclaration des variables nombredesommet et nombredarcs
    compter_sommets_arcs(nom_fichier, &nombredesommet, &nombredarcs); //appel de la fonction compter_sommets_arcs

    t_grapheS *graphe = creer_graphe(nombredesommet, nombredarcs); //appel de la fonction creer_graphe

    FILE *fichier = fopen(nom_fichier, "r"); //ouverture du fichier en mode lecture
    if (fichier == NULL) { //si le fichier n'est pas ouvert ou n'existe pas
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier); //affichage d'un message d'erreur
        exit(EXIT_FAILURE); //arrêt du programme
    }

    int sommet1, sommet2; //déclaration des variables sommet1 et sommet2
    while (fscanf(fichier, "%d %d", &sommet1, &sommet2) != EOF) { //tant qu'on n'est pas à la fin du fichier
        sommet1--; //on décrémente le sommet 1
        sommet2--; //on décrémente le sommet 2
        graphe->matriceadjacente[sommet1][sommet2] = 1; //on met à 1 la case de la matrice d'adjacence correspondant au sommet 1 et au sommet 2
        graphe->matriceadjacente[sommet2][sommet1] = 1; //on met à 1 la case de la matrice d'adjacence correspondant au sommet 2 et au sommet 1
        graphe->sommets[sommet1].voisins[graphe->sommets[sommet1].degre] = sommet2; //on ajoute le sommet 2 dans le tableau des voisins du sommet 1
        graphe->sommets[sommet1].degre++; //on incrémente le degré du sommet 1
        graphe->sommets[sommet2].voisins[graphe->sommets[sommet2].degre] = sommet1; //on ajoute le sommet 1 dans le tableau des voisins du sommet 2
        graphe->sommets[sommet2].degre++; //on incrémente le degré du sommet 2
    } //on fait cela pour avoir la matrice d'adjacence et le tableau des voisins

    fclose(fichier); //fermeture du fichier
    return graphe; //on retourne le graphe
}

void afficher_graphe(t_grapheS *graphe) { //fonction qui affiche un graphe
    printf("Nombre de sommets : %d\n", graphe->nombredesommet); //affichage du nombre de sommets
    printf("Nombre de contraintes : %d\n", graphe->nombredarcs); //affichage du nombre d'arcs
    printf("Matrice d'adjacence :\n"); //affichage de la matrice d'adjacence
    for (int i = 0; i < graphe->nombredesommet; i++) { //parcours de la matrice d'adjacence
        for (int j = 0; j < graphe->nombredesommet; j++) { //parcours de la matrice d'adjacence
            printf("%d ", graphe->matriceadjacente[i][j]); //affichage de la matrice d'adjacence
        } //on fait cela pour afficher la matrice d'adjacence
        printf("\n"); //retour à la ligne
    } //on fait cela pour afficher la matrice d'adjacence
    printf("Liste des sommets par degre :\n"); //affichage de la liste des sommets par degré
    trier_sommets_decroissant(graphe); //appel de la fonction trier_sommets_decroissant
    for (int i = 0; i < graphe->nombredesommet; i++) { //parcours de la matrice d'adjacence
        printf("Sommet %d (degre %d):", graphe->sommets[i].identite + 1, graphe->sommets[i].degre); //affichage du sommet et de son degré
        for (int j = 0; j < graphe->sommets[i].degre; j++) { //parcours de la matrice d'adjacence
            printf(" %d", graphe->sommets[i].voisins[j] + 1); //affichage des voisins du sommet
        } //on fait cela pour afficher les voisins du sommet
        printf("\n"); //retour à la ligne
    } //on fait cela pour afficher la liste des sommets par degré
} //on fait cela pour afficher le graphe

void generer_fichier(char *nom_fichier, t_grapheS *graphe) { //fonction qui génère un fichier avec les informations de sommets et d'arêtes

    FILE *fichier = fopen(nom_fichier, "w"); //ouverture du fichier en mode écriture
    if (fichier == NULL) { //si le fichier n'est pas ouvert ou n'existe pas
        printf("Erreur lors de la création du fichier %s\n", nom_fichier); //affichage d'un message d'erreur
        exit(EXIT_FAILURE); //arrêt du programme
    }
    fprintf(fichier, "%d\n%d\n", graphe->nombredesommet, graphe->nombredarcs); //écriture du nombre de sommets et du nombre d'arcs dans le fichier
    for (int i = 0; i < graphe->nombredesommet; i++) { //parcours de la matrice d'adjacence
        for (int j = i + 1; j < graphe->nombredesommet; j++) { //parcours de la matrice d'adjacence
            if (graphe->matriceadjacente[i][j] == 1) { //si la case de la matrice d'adjacence correspondant au sommet 1 et au sommet 2 est égale à 1
                fprintf(fichier, "%d %d\n", i + 1, j + 1); //écriture du sommet 1 et du sommet 2 dans le fichier
            } //on fait cela pour avoir les informations de sommets et d'arêtes
        }
    }
    fclose(fichier); //fermeture du fichier
}

void colorer_graphe(t_grapheS *graphe) { //fonction qui colorie le graphe
    trier_sommets_decroissant(graphe); //appel de la fonction trier_sommets_decroissant

    for (int i = 0; i < graphe->nombredesommet; i++) { //parcours de la matrice d'adjacence
        graphe->sommets[i].couleur = -1; //initialisation de la couleur du sommet à -1 (aucune couleur)
    } //on fait cela pour avoir un graphe non colorié

    int couleur_actuelle = 0; //initialisation de la couleur actuelle à 0
    for (int i = 0; i < graphe->nombredesommet; i++) { //parcours de la matrice d'adjacence
        t_sommet *sommet = &graphe->sommets[i]; //initialisation du sommet
        int couleur_disponible = 1; //initialisation de la couleur disponible à 1 (vrai)
        for (int j = 0; j < sommet->degre; j++) { //parcours de la matrice d'adjacence
            int voisin = sommet->voisins[j]; //initialisation du voisin du sommet
            if (graphe->sommets[voisin].couleur == couleur_actuelle) { //si la couleur du voisin du sommet est égale à la couleur actuelle
                couleur_disponible = 0; //la couleur disponible prend la valeur 0 (faux)
                break; //on sort de la boucle
            }
        }

        if (couleur_disponible) { //si la couleur disponible est égale à 1 (vrai)
            sommet->couleur = couleur_actuelle; //la couleur du sommet prend la valeur de la couleur actuelle
        } else { //sinon
            couleur_actuelle++; //on incrémente la couleur actuelle
            sommet->couleur = couleur_actuelle; //la couleur du sommet prend la valeur de la couleur actuelle
        }
    }
}

void afficher_coloration(t_grapheS *graphe) { //fonction qui affiche la coloration du graphe
    printf("Coloration du graphe :\n"); //affichage de la coloration du graphe
    for (int i = 0; i < graphe->nombredesommet; i++) { //parcours de la matrice d'adjacence
        printf("Sommet %d : Couleur %d\n", graphe->sommets[i].identite + 1, graphe->sommets[i].couleur + 1); //affichage du sommet et de sa couleur
    } //on fait cela pour afficher la coloration du graphe
}

void menuExcluS(){//fonction principale du programme
    t_grapheS *graphe = lire_graphe("exclusions.txt"); //lecture du graphe à partir du fichier "exclusions.txt"
    afficher_graphe(graphe); //affichage du graphe
    generer_fichier("graphe.txt", graphe); //génération du fichier "graphe.txt" contenant les informations du graphe
    colorer_graphe(graphe); //coloration du graphe (welsch-powell)
    afficher_coloration(graphe); //affichage de la coloration du graphe
    liberer_graphe(graphe); //libération de la mémoire allouée pour le graphe
}//fin de la fonction principale