#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "./Headers/Client.c"
#include "./ANSI-color-codes.h"

#define MAX_LEN 128

int print_image();

void viderBuffer(void);
int lire(char *chaine, int longueur);
int choixUtilisateur(char *choixUtilisateur);
void strtoupper(char *str);
char * strtolower( char * dest, const char * src );
int souhaitContinuer(char *phrase);

int identificationClient();

int menu();

int EnvoieRequeteAfficher();
int EnvoieRequeteAfficherContact();
int EnvoieRequeteAfficherAnnuaire();

int EnvoieRequeteCree();
int EnvoieRequeteCreeContact();
int EnvoieRequeteCreeAnnuaire();
int EnvoieRequeteCreeUtilisateur();

int EnvoieRequeteSupprimer();
int EnvoieRequeteSupprimerContact();
int EnvoieRequeteSupprimerAnnuaire();
int EnvoieRequeteSupprimerUtilisateur();

int EnvoieRequeteModifier();
int EnvoieRequeteModifierContact();
int EnvoieRequeteModifierAnnuaire();
int EnvoieRequeteModifierUtilisateur();


int main(int argc, char *argv[]) {
    char choix;

    if(Initialisation("localhost") != 1) {
		printf("Erreur d'initialisation\n");
		return 1;
	}

    while (1) {
        //system("clear");
        //print_image("./enTeteMenu/logoAnnuaire.txt");
        if(!identificationClient()){
            Terminaison();
            exit(0);
        }
        
        do {
            //print_image("./enTeteMenu/menuPrincipal.txt");
            choixUtilisateur(&choix);
            printf("%c",choix);

            switch (choix) {
            case 'A':    
                printf("    Vous avez choisi le choix A\n");
                EnvoieRequeteAfficher();
                break;
                
            case 'B':
                printf("    Vous avez choisi le choix B\n");
                EnvoieRequeteCree();
                break;

            case 'C':
                printf("    Vous avez choisi le choix C\n");
                EnvoieRequeteSupprimer();
                break;
                
            case 'D':
                printf("    Vous avez choisi le choix D\n\n");
                EnvoieRequeteModifier();
                break;

            case 'E':
                printf("    Au revoir et à bientôt !!\n");
                Terminaison();
                exit(0);

            default:
                printf("    Mauvais choix\n");
            }
        } while (choix != 'A' && choix != 'B' && choix != 'C' && choix != 'D' && choix != 'E');
    }
    return 0;
}

int souhaitContinuer(char *phrase) { 
    char choix[1];

    do {
        printf("%s [o/n] : ", phrase);
        lire(choix, 2);
        strtolower(choix, choix);
        if (*choix == 'o') {
            return 1;
        } else {
            return 0;
        }  
    } while (*choix != 'o' && *choix != 'n');
}

int identificationClient() {
    int auth = 0;
    int ret = 0;
    do {
        requete *reqIdentification = NULL;
        reqIdentification = malloc(1*sizeof(requete));

        reponse repIdentification;

        strcpy(reqIdentification->action, "0\0");
        strcpy(reqIdentification->objet, "0\0");
        printf("Saisir votre Identifiant : ");
        lire(reqIdentification->data.Utilisateur.identifiant, 255);     
        strtoupper(reqIdentification->data.Utilisateur.identifiant);

        printf("Saisir votre mot de passe : ");
        lire(reqIdentification->data.Utilisateur.motDePasse, 255);

        EmissionStrucRequete(*reqIdentification);
        free(reqIdentification);

        repIdentification = receptionStrucReponse();

        if (strcmp(repIdentification.codeReponse, "200") == 0) {
            printf(GRN"Acces Autoriser par le serveur\n"reset);
            auth = 1;
            ret = 1;
        } else if (strcmp(repIdentification.codeReponse, "301") == 0) {
            printf(YEL"Identifiant non saisie\n"reset);
        } else if (strcmp(repIdentification.codeReponse, "401") == 0) {
            printf(YEL"Mot de passe non saisie\n"reset);
        } else if (strcmp(repIdentification.codeReponse, "512") == 0) {
            printf(RED"Acces non autoriser sur le serveur \n"reset);
            auth = 1;
        } else if (strcmp(repIdentification.codeReponse, "202") == 0) {
            printf(RED"Requete Invalide\n"reset);
            exit(0);
        } else {
            printf(RED"ERREUR"reset);
            exit(0);
        }
    } while (auth != 1);
    return ret;
}

char * strtolower( char * dest, const char * src ) {
    char * result = dest;
    while( *dest++ = tolower( *src++ ) );
    return result;
}

void strtoupper(char *str) {
    for ( ; *str ; str++)
        *str = toupper(*str);
}

int lire(char *chaine, int longueur) {
    char *positionEntree = NULL;
 
    if (fgets(chaine, longueur, stdin) != NULL) {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL) {
            *positionEntree = '\0';
            return 1;
        } else {
            viderBuffer();
            return 0;
        }
    } else {
        viderBuffer();
        return 0;
    }
}

void viderBuffer(void) {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

int print_image(char *path) {
    char *filename = path;
    FILE *fptr = NULL;
 
    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"Erreur lors de l'ouverture du fichier\n Verifier que le chemin d\'accès vers : %s est valide\n", filename);
        return 1;
    }

    char read_string[MAX_LEN];
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);

    fclose(fptr);
    printf("\n");
}

int choixUtilisateur(char *choixUtilisateur) {
    do {
        printf("    Choisissez ce que vous voulez faire : ");
    } while (lire(choixUtilisateur, 3) != 1 );
    strtoupper(choixUtilisateur);
    return 0;
}

// Fonction Partie Affichage 
int EnvoieRequeteAfficher() {
    char choix;

    do {
        system("@cls||clear");
        print_image("./enTeteMenu/logoAnnuaire.txt");
        print_image("./enTeteMenu/menuAffichage.txt");

        choixUtilisateur(&choix);

        switch (choix) {
        case 'A':
            printf("    Vous avez choisi le choix A\n");
            EnvoieRequeteAfficherContact();
            break;
        
        case 'B':
            printf("    Vous avez choisi le choix B\n");
            EnvoieRequeteAfficherAnnuaire();
            break;

        case 'C':
            printf("    Retout au Menu Précédent\n");
            break;

        default:
            printf("    Mauvais choix\n");
        }
    } while (choix != 'A' && choix != 'B' && choix != 'C');
}

int EnvoieRequeteAfficherContact(){
    //test
}

int EnvoieRequeteAfficherAnnuaire() {
    //test
}

// Fonction Partie Création
int EnvoieRequeteCree(){
    char choix;
    
    do {
        //system("@cls||clear");
        //print_image("./enTeteMenu/logoAnnuaire.txt");
        //print_image("./enTeteMenu/menuCreation.txt");
    
        choixUtilisateur(&choix);

        switch (choix) {
        case 'A':
            printf("    Vous avez choisi le choix A\n");
            EnvoieRequeteCreeContact();
            break;
        
        case 'B':
            printf("    Vous avez choisi le choix B\n");
            EnvoieRequeteCreeAnnuaire();
            break;
        
        case 'C':
            printf("    Vous avez choisi le choix B\n");
            EnvoieRequeteCreeUtilisateur();
            break;

        case 'D':
            printf("    Retout au Menu Précédent\n");
            break;

        default:
            printf("    Mauvais choix\n");
        }
    } while (choix != 'A' && choix != 'B' && choix != 'C' && choix != 'D');
}

int EnvoieRequeteCreeContact() {
    requete *reqCreationContact = NULL;
    reqCreationContact = malloc(1*sizeof(requete));

    reponse repCreationContact;

    strcpy(reqCreationContact->action, "1\0");
    strcpy(reqCreationContact->objet, "5\0");

    printf("Saisir le nom de l'annuaire : ");
    lire(reqCreationContact->data.Contact.nomAnnuaire, 255);

    printf("Saisir le nom du contact a crée : ");
    lire(reqCreationContact->data.Contact.nom, 255);

    printf("Saisir le prenom : ");
    lire(reqCreationContact->data.Contact.prenom, 255);

    printf("Saisir l'adresse mail : ");
    lire(reqCreationContact->data.Contact.mail, 255);

    if (souhaitContinuer("Souhaitez-vous remplir les champs supplémentaires ?")) {
        printf("Saisir le numero de téléphone (Ex : 0612345678) : ");
        lire(reqCreationContact->data.Contact.telephone, 11);

        printf("Saisir l'adresse postale : ");
        lire(reqCreationContact->data.Contact.adresse, 255);

        printf("Saisir la date de naissance (JJ/MM/AAAAA) : ");
        lire(reqCreationContact->data.Contact.dateNaissance, 11);
        
        printf("Saisir une remarque : ");
        lire(reqCreationContact->data.Contact.remarque, 255);
    }
    EmissionStrucRequete(*reqCreationContact);
    free(reqCreationContact);
}

int EnvoieRequeteCreeAnnuaire() {
    requete *reqIdentification = NULL;
    reqIdentification = malloc(1*sizeof(requete));

    reponse repIdentification;

    strcpy(reqIdentification->action, "1\0");
    strcpy(reqIdentification->objet, "6\0");

    EmissionStrucRequete(*reqIdentification);
    free(reqIdentification);
}

int EnvoieRequeteCreeUtilisateur() {
    requete *reqIdentification = NULL;
    reqIdentification = malloc(1*sizeof(requete));

    reponse repIdentification;

    strcpy(reqIdentification->action, "1\0");
    strcpy(reqIdentification->objet, "7\0");

    EmissionStrucRequete(*reqIdentification);
    free(reqIdentification);
}

// Fonction Partie Suppression 
int EnvoieRequeteSupprimer(){
    char choix;

    do {
        system("@cls||clear");
        print_image("./enTeteMenu/logoAnnuaire.txt");
        print_image("./enTeteMenu/menuSuppression.txt");

        choixUtilisateur(&choix);

        switch (choix) {
        case 'A':
            printf("    Vous avez choisi le choix A\n");
            EnvoieRequeteSupprimerContact();
            break;
        
        case 'B':
            printf("    Vous avez choisi le choix B\n");
            EnvoieRequeteSupprimerAnnuaire();
            break;

        case 'C':
            printf("    Vous avez choisi le choix C\n");
            EnvoieRequeteSupprimerUtilisateur();
            break;

        case 'D':
            printf("    Retout au Menu Précédent\n");
            break;

        default:
            printf("    Mauvais choix\n");
        }
    } while (choix != 'A' && choix != 'B' && choix != 'C' && choix != 'D');
}

int EnvoieRequeteSupprimerContact() {
    //test
}

int EnvoieRequeteSupprimerAnnuaire() { 
    //test
}

int EnvoieRequeteSupprimerUtilisateur() {
    //test
}

// Fonction Partie Modification 
int EnvoieRequeteModifier(){
    char choix;

    do {
        system("@cls||clear");
        print_image("./enTeteMenu/logoAnnuaire.txt");
        print_image("./enTeteMenu/menuModification.txt");

        choixUtilisateur(&choix);

        switch (choix) {
        case 'A':
            printf("    Vous avez choisi le choix A\n");
            EnvoieRequeteModifierContact();
            break;
        
        case 'B':
            printf("    Vous avez choisi le choix B\n");
            EnvoieRequeteModifierAnnuaire();
            break;

        case 'C':
            printf("    Vous avez choisi le choix C\n");
            EnvoieRequeteModifierUtilisateur();
            break;

        case 'D':
            printf("    Retout au Menu Précédent\n");
            break;

        default:
            printf("    Mauvais choix\n");
        }
    } while (choix != 'A' && choix != 'B' && choix != 'C' && choix != 'D');
}

int EnvoieRequeteModifierContact() { 
    //test
}

int EnvoieRequeteModifierAnnuaire() {
    //test
}

int EnvoieRequeteModifierUtilisateur() {
    //test
}