#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./Serveur.h"
#include "./fonctionServeur.h"

extern int admin;

int actionRequeteCreer(requete req, reponse *rep) {

    if (strcmp(req.objet, "5") == 0) {
	    // Partie de creation d'Annuaire/Contact et Utilisateur (si l'on est admin)
        printf("Creation Contact\n");
        creationContatc(req, rep);
				
    } else if (strcmp(req.objet, "6") == 0) {
	    // Partie affichage d'Annuaire/Contact
        printf("Creation Annuaire\n");
	    creationAnnuaire(req, rep);
				
    } else if (strcmp(req.objet, "7") == 0) {
	    // Partie de modification d'Annuaire/Contact et Utilisateur (si l'on est admin)
        printf("Creation Utilisateur\n");
	    creationUtilisateur(req, rep);
			
    } else {
	    strcpy(rep->codeReponse, "102");
	    printf("Requete Action invalide");
    }
}

int creationContatc(requete req, reponse *rep){
    contact *contactLu = NULL;
    contactLu = malloc(1*sizeof(contact));

    contact *contactCree = NULL;
    contactCree = malloc(1*sizeof(contact));

    strcpy(contactCree->nom,req.data.Contact.nom);
    strcpy(contactCree->prenom,req.data.Contact.prenom);
    strcpy(contactCree->mail,req.data.Contact.mail);

    strcpy(contactCree->dateNaissance,req.data.Contact.dateNaissance);
    strcpy(contactCree->adresse,req.data.Contact.adresse);
    strcpy(contactCree->telephone,req.data.Contact.telephone);
    strcpy(contactCree->remarque,req.data.Contact.remarque);

    // Enregistrement dans un fichier
    FILE* fichierContact = NULL;

    fichierContact = fopen("./Stockage/Contact.txt", "a+");
    if (fichierContact != NULL) {
        // On peut lire et écrire dans le fichier
        printf("Enregistrement des données\n");
        fwrite(contactCree, sizeof(contact), 1, fichierContact);
    } else {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier Contact.txt");
    }
    fclose(fichierContact); // On ferme le fichier qui a été ouvert

    fichierContact = fopen("./Stockage/Contact.txt", "r");
    printf("Lecture des données\n");
    fseek(fichierContact, 0, SEEK_SET);
    fread(contactLu, sizeof(contact), 1, fichierContact);
    printf("%s ; %s ; %s ; %s ; %s ; %s ; %s ; %s\n", contactLu->nomAnnuaire, contactLu->nom, contactLu->prenom, contactLu->mail, contactLu->dateNaissance, contactLu->telephone, contactLu->adresse, contactLu->remarque);
    fclose(fichierContact); // On ferme le fichier qui a été ouvert
}
int creationAnnuaire(requete req, reponse *rep){

}
int creationUtilisateur(requete req, reponse *rep){

}