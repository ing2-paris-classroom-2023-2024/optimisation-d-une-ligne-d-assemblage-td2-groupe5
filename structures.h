
#ifndef PRECEDEXCLUSTEMPS_STRUCTURES_H
#define PRECEDEXCLUSTEMPS_STRUCTURES_H
#include <stdio.h>
#include <stdlib.h>

typedef struct tache{ // structure tache
    int numeroTache; //numéro de la tache
    float dureeTache;// duree de la tache
    struct tache* precedent; //precedent dans la file "chaine"
    struct tache* suivant; //suivant dans la file "chaine"
    struct tache* usuivant; //suivante dans "usine" et "station"
    struct tache* uprecedent; //precedent dans "usine" et "station"
    int placer; //indicateur placé ou non
}t_tache;

typedef struct graphe{ //structure graphe
    int ordre; //nombre de sommet
    int nbdetachetemp;
    int* tache; //tableau des taches temporaire
    int nbsommetfini; //nombre de sommet temporaire
    int ** matrice; //matrice de précedence
    int ** mexclusion; //matrice d'exclusion
    int nb_arete; //nombre de contrainte de précédence
    t_tache * tetetache; //tete file des taches
    t_tache * fintache; //fin de la file des taches
    int preced; //choix du menu
    int excl; //choix du menu
    int time; //choix du menu
}t_graphe;



typedef struct station{ //structure station
    t_tache * tachetete; //tache tete de la file
    t_tache * tachefin; //tache fin de la file
    float dureetotal; //durée total de la station
    float dureemax; //durée maximal de la station
    struct station* suivant; //suivant dans la file usine
    struct station* precedent; //précédent dans la file usine

}t_station;

typedef struct usine{ //structure usine
    t_station *stationtete; //station tete de la file
    t_station *stationfin;//station fin de la file
}t_usine;



#endif //PRECEDEXCLUSTEMPS_STRUCTURES_H
