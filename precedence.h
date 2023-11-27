

#ifndef TESTPRECEDENCE_PRECEDENCE_H
#define TESTPRECEDENCE_PRECEDENCE_H

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
    int* tache;
    int ** matrice;
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




void tacheassignation(t_chaine* chaine, t_graphe* graphe);
void precedence(t_graphe* graphe);
t_graphe * lirefichier();
int dejadanstab(int sommet,int tableau[50], int nb_sommet);
void enfiler(t_chaine* chaine, t_maillon* maillon);
t_maillon * creermaillon(int depart, int fin);
t_chaine * creerchaine();
t_tache* creertache(int tachetemp, float duree);
void enfilerdansgraphe(t_graphe* graphe, t_tache* tache);
void lientempprecedence(t_graphe* graphe, t_chaine* chaine);
t_usine * remplissagestation(t_graphe* graphe);
t_usine * creerusine();
t_station * creerstation(t_usine* nouvelusine);
void ajoutertachestationusine(t_tache* tache, t_usine* usine, t_graphe* graphe);
t_tache * trouvertachenum(t_graphe *graphe, int sanspred);
void affichageusine(t_usine* usine);


#endif //TESTPRECEDENCE_PRECEDENCE_H
