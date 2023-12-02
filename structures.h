
#ifndef PRECEDEXCLUSTEMPS_STRUCTURES_H
#define PRECEDEXCLUSTEMPS_STRUCTURES_H
#include <stdio.h>
#include <stdlib.h>

typedef struct tache{
    int numeroTache;
    float dureeTache;
    struct tache* precedent;
    struct tache* suivant;
    struct tache* usuivant;
    struct tache* uprecedent;
    int placer;
}t_tache;

typedef struct graphe{
    int ordre;
    int nbdetachetemp;
    int* tache;
    int nbsommetfini;
    int ** matrice;
    int ** mexclusion;
    int nb_arete;
    t_tache * tetetache;
    t_tache * fintache;
}t_graphe;


typedef struct maillon{
    int depart;
    int fin;
    struct maillon* precedent;
    struct maillon* suivant;
}t_maillon;

typedef struct chaine{
    t_maillon * tete;
    t_maillon * fin;
}t_chaine;



typedef struct station{
    t_tache * tachetete;
    t_tache * tachefin;
    float dureetotal;
    float dureemax;
    struct station* suivant;
    struct station* precedent;

}t_station;

typedef struct usine{
    t_station *stationtete;
    t_station *stationfin;
}t_usine;



#endif //PRECEDEXCLUSTEMPS_STRUCTURES_H
