

#ifndef TESTPRECEDENCE_PRECEDENCE_H
#define TESTPRECEDENCE_PRECEDENCE_H
#include "structures.h"


void tacheassignation(t_graphe* graphe); //assigner le temps aux taches avec lecture fichier temps.txt
void precedence(t_graphe* graphe); //sous programme général
t_graphe * lirefichier(); //lire le fichier precedence.txt
int dejadanstab(int sommet,int tableau[50], int nb_sommet); //verifier si un nombre a déjà été placé dans le tableau
t_tache* creertache(int tachetemp, float duree); //créer une tache
void enfilerdansgraphe(t_graphe* graphe, t_tache* tache); //enfiler la tache dans la file de tache du graphe
t_usine * remplissagestation(t_graphe* graphe); //remplir les usines
t_usine * creerusine(); //créer une usine
t_station * creerstation(t_usine* nouvelusine); //créer une station
void ajoutertachestationusine(t_tache* tache, t_usine* usine, t_graphe* graphe, t_station* stationmin); //ajouter une tache dans l'usine
t_tache * trouvertachenum(t_graphe *graphe, int num); //renvoie la tache associé à un numéro
void affichageusine(t_usine* usine); //affichage de l'usine
void tachesinitiales(t_graphe *graphe, t_usine *usine); //trouve les taches de départ du graphe
void autrestaches(t_usine* usine, t_graphe* graphe); //trouve les autres taches à placer dans l'usine du graphe
void menu(t_graphe* graphe);

#endif //TESTPRECEDENCE_PRECEDENCE_H
