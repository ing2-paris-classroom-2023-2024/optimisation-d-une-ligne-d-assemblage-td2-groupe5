#include "source.h" //bibliotheque contenant les prototypes des fonctions et les structures
#include "source.c" //bibliotheque contenant les fonctions du projet implémentées

int main() { //fonction principale du programme 
    t_graphe *graphe = lire_graphe("exclusions.txt"); //lecture du graphe à partir du fichier "exclusions.txt"
    afficher_graphe(graphe); //affichage du graphe
    generer_fichier("graphe.txt", graphe); //génération du fichier "graphe.txt" contenant les informations du graphe
    colorer_graphe(graphe); //coloration du graphe (welsch-powell)
    afficher_coloration(graphe); //affichage de la coloration du graphe 
    liberer_graphe(graphe); //libération de la mémoire allouée pour le graphe
    return 0; //fin du programme
} //fin de la fonction principale



