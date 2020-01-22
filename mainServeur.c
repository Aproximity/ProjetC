#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./Serveur/Serveur.h"
#include "./Serveur/fonctionServeur.h"

int authentification(requete req, reponse *rep);
int admin = 0;

int main(void) {
	Initialisation();

	while(1) {
		int fini = 0;
		printf("Attente d'un client \n");
		AttenteClient();
	
		while(!fini) {
			requete req;

			reponse *rep = NULL;
			rep = malloc(1*sizeof(reponse));

			req = receptionStrucRequete();
			if (strcmp(req.action, "0") == 0) {
				if (strcmp(req.objet, "0") == 0) {
					// Authentification
					fini = authentification(req, rep);
					printf("Admin : %d\n", admin);
				} else {
					strcpy(rep->codeReponse, "202");
					printf("Requete Objet invalide");
					fini = 1;
				}
			} else if (strcmp(req.action, "1") == 0) {
				// Partie de creation d'Annuaire/Contact et Utilisateur (si l'on est admin)
				actionRequeteCreer(req, rep);
				//exit(0);
				
			} else if (strcmp(req.action, "2") == 0) {
				// Partie affichage d'Annuaire/Contact
				actionRequeteAfficher(req, rep);
				
			} else if (strcmp(req.action, "3") == 0) {
				// Partie de modification d'Annuaire/Contact et Utilisateur (si l'on est admin)
				actionRequeteModifier(req, rep);
				
			} else if (strcmp(req.action, "4") == 0) {
				// Partie de suppression d'Annuaire/Contact et Utilisateur (si l'on est admin)
				actionRequeteSupprimer(req, rep);
				
			} else {
				strcpy(rep->codeReponse, "102");
				printf("Requete Action invalide");
				EmissionStrucReponse(*rep);
				free(rep);
				fini = 1;
			}
		}
		TerminaisonClient();
	}
    return 0;
}

int authentification(requete req, reponse *rep) {
	int ret = 0;

	utilisateur user1;
	strcpy(user1.identifiant,"123");
    strcpy(user1.motDePasse,"123");
    user1.admin = 1;

	if ((strcmp(req.data.Utilisateur.identifiant,user1.identifiant) == 0) && (strcmp(req.data.Utilisateur.motDePasse,user1.motDePasse) == 0)) {
		if (user1.admin == 1) {
			admin = 1;
		}
		printf("Acces autoriser\n");
		printf("IDENTIFIANT : %s\n", req.data.Utilisateur.identifiant);
		printf("MOT DE PASSE: %s\n\n", req.data.Utilisateur.motDePasse);
		strcpy(rep->codeReponse, "200");
	} else if (strcmp(req.data.Utilisateur.identifiant,"\0") == 0) {
		strcpy(rep->codeReponse, "301");
		printf("Identifiant NULL\n\n");
	} else if (strcmp(req.data.Utilisateur.motDePasse,"\0") == 0) {
		strcpy(rep->codeReponse, "401");
		printf("Mot de passe NULL\n\n");
	} else {
		strcpy(rep->codeReponse, "512");
		printf("Acces non autoriser\n\n");
		ret = 1;
	}
	EmissionStrucReponse(*rep);
	free(rep);
	return ret;
}