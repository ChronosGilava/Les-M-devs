#include "Projet_Header.h"

int main()
{

    setlocale(LC_ALL, "");
    
    //pesentation();
    //auth();


    Employe *tab_presences = NULL; // creationn tableau
    int n = 0;
    int choix;
    do
    {
        system("cls");

        gotoxy(45, 10); 
        printf("================================ MENU ==================================");
        gotoxy(45, 11);
        printf("1. Enregistrer une presence ");
        gotoxy(45, 12);
        printf("2. Enregistrer l'heure de depart d'un employe ");
        gotoxy(45, 13);
        printf("3. Verification des presences d'un employe a une date donnee ");
        gotoxy(45, 14);
        printf("4. Supprimer la presence d'un employe ");
        gotoxy(45, 15);
        printf("5. Modifier une presence");
        gotoxy(45, 16);
        printf("6. nombre de presences ");
        gotoxy(45, 17);
        printf("7. Liste des presences a une date donnee ");
        gotoxy(45, 18);
        printf("8. Liste de toutes les presences ");
        gotoxy(45, 19);
        printf("9. Verifier la presence d'un employe a une date donnee");
        gotoxy(45, 20);
        printf("10. Liste des presences d'un employe entre deux dates ");
        gotoxy(45, 21);
        printf("11. Liste de toutes les presences d'un employe ");
        gotoxy(45, 22);
        printf("12. Situation des presences par departement a une date donnee");
        gotoxy(45, 23);
        printf("13. Situation des presences par departement entre deux dates donnees ");
        gotoxy(45, 24);
        printf("14. Situation globale des presences par departement");
        gotoxy(45, 25);
        printf("0. Quitter");
        gotoxy(45, 26);
        printf("======================================================================");

        gotoxy(45, 27);
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1)
        {
            afficherErreur(59, 27, "Vous ne pouvez entrer que des nombres !\n");

            // vider le clavier
            while (getchar() != '\n');

            choix = -1;
        }
        
        else
        {
        
        system("cls");
        switch(choix)
        {
            case 1:
                enregistrerPresence(&tab_presences, &n);
                afficherPresences(tab_presences, n);
                printf("\nAppuyez sur une touche pour continuer...");
                getch();
                break;
            case 2:
                enregistrerDepart(tab_presences, n);
                afficherPresences(tab_presences, n);
                break;


            case 3:
                verifierPresence(tab_presences, n);
                break;


            case 4:
                supprimerPresence(tab_presences, &n);
                break;
            case 5:
                modifierPresence(tab_presences, n);
                afficherPresences(tab_presences, n);
                printf("\nAppuyez sur une touche pour continuer...");
                getch();
                break;

            case 6:
                nombrePresences(tab_presences, n);
                break;
            case 7:
                listePresencesParDate(tab_presences, n);
                break;
            case 8:
                afficherPresences(tab_presences, n);
                printf("\nAppuyez sur une touche pour continuer...");
                getch();
                break;

            case 9:
                presenceEmployeDate(tab_presences, n);
                break;

            case 10:
                presenceEntreDeuxDates(tab_presences, n);
                printf("\nAppuyez sur une touche pour continuer...");
                getch();
                break;

            case 11:
                toutesPresencesEmploye(tab_presences, n);
                printf("\nAppuyez sur une touche pour continuer...");
                getch();
                break;

            case 12:
                presenceDepartementDate(tab_presences, n);
                printf("\nAppuyez sur une touche pour continuer...");
                getch();
                break;

            case 13:
                presenceDepartementEntreDates(tab_presences, n);
                printf("\nAppuyez sur une touche pour continuer...");
                getch();
                break;

            case 14:
                situationGlobale(tab_presences, n);
                printf("\nAppuyez sur une touche pour continuer...");
                getch();
                break;

            case 0:
                printf("Fermeture du programme...\n");
                Sleep(1500);
                break;

            default:

                gotoxy(59, 27);
                printf("Choix invalide !\n");
                Sleep(1500);
        }
        }
    } while(choix != 0);

    // libération mémoire
    free(tab_presences);

    return 0;
}