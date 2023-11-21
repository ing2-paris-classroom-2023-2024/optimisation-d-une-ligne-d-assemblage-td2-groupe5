#include "anna.h"
//#include "anna.c"


void afficherFichier(char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }
    char c;
    while ((c = fgetc(fichier)) != EOF) {
        printf("%c", c);
    }
    fclose(fichier);
}

int compterContraintes(char *nomFichier){
    FILE *fichier = fopen(nomFichier, "r");

    int nbContraintes = 0;
    char c = 0;

    while ((c = fgetc(fichier)) != EOF) {
        if (c == '\n') {
            nbContraintes++;
        }
    }

    fclose(fichier);
    return nbContraintes;
}


int main(){
    //test();

    char nomFichier[100];
    FILE *fichier;

    do{
        printf("Choisissez le fichier a ouvrir : 1)contraintes \n");
        scanf("%s", nomFichier);

        fichier = fopen(nomFichier, "r");
        if (fichier == NULL) {
            printf("Impossible d'ouvrir le fichier.\n");
        }else {
            fclose(fichier);
        }
    } while (fichier == NULL);

    printf("Voici le contenu du fichier de contraintes : \n");
    afficherFichier(nomFichier);

    if (strcmp(nomFichier, "contraintes.txt") == 0) {
        int nbContraintes = compterContraintes(nomFichier);

        if (nbContraintes == -1) {
            printf("Erreur lors de la lecture du fichier.\n");
        } else if (nbContraintes == 0) {
            printf("Le fichier est vide.\n");
        } else {
            printf("Le nombre de contraintes est de : %d\n", nbContraintes);
        }

    }
    else {
        printf("Le fichier n'est pas valide.\n");
    }

    return 0;
}
