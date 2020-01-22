#ifndef __STRUCTURE_H__
#define __STRUCTURE_H__

#include <stdbool.h>
//fichier contenant les structures
typedef struct annuaire annuaire;
struct annuaire {
    char nomAnnuaire[255];
    char identifiant[255];
    char droit[10][255];
};

typedef struct contact contact;
struct contact {
    char nomAnnuaire[255];
    char nom[255];
    char prenom[255];
    char telephone[11];
    char adresse[255];
    char mail[255];
    char dateNaissance[11];
    char remarque[255];
};

typedef struct utilisateur utilisateur;
struct utilisateur {
    char identifiant[255];
    char motDePasse[255];
    int admin;
};

union data {
    contact Contact;
    utilisateur Utilisateur;
    annuaire Annuaire;
    char data[1555];
} data;

typedef struct requete requete;
struct requete {
    char action[2];
    char objet[2];
    union data data;
};

typedef struct reponse reponse;
struct reponse {
    char codeReponse[4];
    union data data;
};

#endif
