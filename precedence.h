

#ifndef TESTPRECEDENCE_PRECEDENCE_H
#define TESTPRECEDENCE_PRECEDENCE_H
#include "structures.h"


void tacheassignation(t_chaine* chaine, t_graphe* graphe);
void precedence(t_graphe* graphe);
t_graphe * lirefichier();
int dejadanstab(int sommet,int tableau[50], int nb_sommet);
void enfiler(t_chaine* chaine, t_maillon* maillon);
t_maillon * creermaillon(int depart, int fin);
t_chaine * creerchaine();
t_tache* creertache(int tachetemp, float duree);
void enfilerdansgraphe(t_graphe* graphe, t_tache* tache);
t_usine * remplissagestation(t_graphe* graphe);
t_usine * creerusine();
t_station * creerstation(t_usine* nouvelusine);
void ajoutertachestationusine(t_tache* tache, t_usine* usine, t_graphe* graphe, t_station* stationmin);
t_tache * trouvertachenum(t_graphe *graphe, int num);
void affichageusine(t_usine* usine);
void tachesinitiales(t_graphe *graphe, t_usine *usine);
void autrestaches(t_usine* usine, t_graphe* graphe);


#endif //TESTPRECEDENCE_PRECEDENCE_H
