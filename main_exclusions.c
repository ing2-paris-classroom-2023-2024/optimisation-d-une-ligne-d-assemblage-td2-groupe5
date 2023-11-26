#include "source.h"
#include "source.c"

int main() {
    t_graphe *graphe = lire_graphe("exclusions.txt");
    afficher_graphe(graphe);

    // Génération du fichier avec les informations de sommets et d'arêtes
    generer_fichier("graphe.txt", graphe);

    // Coloration du graphe
    colorer_graphe(graphe);

    // Affichage de la coloration
    afficher_coloration(graphe);

    // Libération des ressources
    liberer_graphe(graphe);

    return 0;
}

