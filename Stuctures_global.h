//
// Created by Utilisateur on 21/11/2023.
//

#ifndef PROJET_TG1_STUCTURES_GLOBAL_H
#define PROJET_TG1_STUCTURES_GLOBAL_H

typedef struct chaine{

}t_chaine;

typedef struct station{

}t_station;

typedef struct tache{
    int numeroTache;
    float dureeTache;
    struct tache* precedence;
}t_tache;




#endif //PROJET_TG1_STUCTURES_GLOBAL_H
