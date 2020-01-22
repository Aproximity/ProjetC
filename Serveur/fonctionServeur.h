#ifndef __FONCTION_SERVEUR_H__
#define __FONCTION_SERVEUR_H__

#include "../Structures.h"
#include "./Serveur.h"

int actionRequeteModifier(requete req, reponse *rep);


int actionRequeteCreer(requete req, reponse *rep);
int creationContatc(requete req, reponse *rep);
int creationAnnuaire(requete req, reponse *rep);
int creationUtilisateur(requete req, reponse *rep);


int actionRequeteSupprimer(requete req, reponse *rep);


int actionRequeteAfficher(requete req, reponse *rep);

#endif
