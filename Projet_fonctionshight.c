#include "Projet_Header.h"

// ============================================== GOTOXY =========================================
void gotoxy(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}

//ce projet a ete devellope avec amour par les Mdevs

// ====================================================== presentation =============================================
void pesentation()
{
    gotoxy(35, 10);
    printf("********************************* BIENVENUE *******************************************");
    gotoxy(35, 13);
    printf("Ceci est une application de controle de presence des employes d'une Entreprise");
    gotoxy(35, 15);
    printf("         Devellope par Saikou -- Alpha -- Lookman -- Aly -- Souleymane        ");
    gotoxy(35, 18);
    printf("****************************************************************************************");
    gotoxy(35, 21);
    printf("Appuyez sur une touche pour vous connecter... ");
    gotoxy(78, 21);

    getch();
    system("cls");
}

//============================================== Fonction Authentification ===================================
void auth()
{
    char login[20];
    char password[8];
connexion:
    gotoxy(60, 10);
    printf("*************** CONNEXION ***************");
    gotoxy(60, 13);
    printf("Login : ");
    gotoxy(60, 15);
    printf("Password : ");
    gotoxy(60, 17);
    printf("******************************************");

    gotoxy(68, 13);
    scanf("%s", &login);
    gotoxy(71, 15);
    scanf("%s", &password);

    if (strcmp(login, "bgras") != 0 || strcmp(password, "mdp") != 0)
    {
        gotoxy(60, 18);
        printf("Login ou password incorrect ! veuillez reessayer ");
        Sleep(3000);
        system("cls");
        goto connexion;
    }
    else
    {
        gotoxy(60, 18);
        printf("Connexion Reussie ! ");
        Sleep(2000);
        system("cls");
    }
}

//============================================== AFFICHER ERREUR ===================================
void afficherErreur(int x, int y, char message[])
{
    gotoxy(x, y);
    printf("                                                                                        ");
    gotoxy(x, y);
    printf("%s", message);

    Sleep(2000);

    gotoxy(x, y);
    printf("                                                                                         ");

    gotoxy(x, y);
}

// =============================================== FONCTION 1 =================================================

void enregistrerPresence(Employe **tab, int *n)
{

    // allocation dynamique
    *tab = (Employe *)realloc(*tab, (*n + 1) * sizeof(Employe));

    system("cls");
    gotoxy(30, 2);
    printf("===================== ENREGISTREMENT =====================");

    gotoxy(5, 5);
    printf("Numero d'enregistrement :  ");

    gotoxy(5, 7);
    printf("Matricule               :  ");

    gotoxy(5, 9);
    printf("Nom                     :  ");

    gotoxy(5, 11);
    printf("Prenom                  :  ");

    gotoxy(5, 13);
    printf("Departement             :  ");

    gotoxy(5, 15);
    printf("Date (jj mm aaaa)       :  ");

    gotoxy(5, 17);
    printf("Heure arrivee(hh mm)    :  ");

    // saisie du num
    int i;
    int num;
    int existe;

    do
    {
        existe = 0;

        gotoxy(33, 5);

        while (scanf("%d", &num) != 1)
        {
            while (getchar() != '\n')
                ;
            afficherErreur(33, 5, "Numero invalide !");
        }

        for (i = 0; i < *n; i++)
        {
            if ((*tab)[i].Num_enregistrement == num)
            {
                existe = 1;
                afficherErreur(33, 5, "Numero deja existant !");
            }
        }

    } while (existe);

    (*tab)[*n].Num_enregistrement = num;

    // saisie du matricule
    int matri;

    gotoxy(33, 7);

    while (scanf("%d", &matri) != 1)
    {
        while (getchar() != '\n')
            ;

        afficherErreur(33, 7, "Matricule invalide !");
    }

    (*tab)[*n].matricule = matri;

    // saisie du nom
    gotoxy(33, 9);
    scanf("%s", (*tab)[*n].Nom);

    // saisie du prenom
    gotoxy(33, 11);
    scanf("%s", (*tab)[*n].Prenom);

    // saisie du departement
    gotoxy(33, 13);
    scanf("%s", (*tab)[*n].Departement);

    // saisie de date
reprise:
    gotoxy(33, 15);
    while (scanf("%d %d %d",
                 &(*tab)[*n].date_jour.jour,
                 &(*tab)[*n].date_jour.mois,
                 &(*tab)[*n].date_jour.annee) != 3)
    {
        while (getchar() != '\n')
            ;

        afficherErreur(33, 15, "Date invalide !");
    }

    if ((*tab)[*n].date_jour.jour < 1 ||
        (*tab)[*n].date_jour.jour > 31 ||
        (*tab)[*n].date_jour.mois < 1 ||
        (*tab)[*n].date_jour.mois > 12 ||
        (*tab)[*n].date_jour.annee < 1900 ||
        (*tab)[*n].date_jour.annee > 9999)
    {
        afficherErreur(33, 15, "Date invalide !");
        goto reprise;
    }

    // Verification de presence double a la meme date
    for (i = 0; i < *n; i++)
    {
        if ((*tab)[i].matricule == matri &&
            (*tab)[i].date_jour.jour ==
                (*tab)[*n].date_jour.jour &&
            (*tab)[i].date_jour.mois ==
                (*tab)[*n].date_jour.mois &&
            (*tab)[i].date_jour.annee ==
                (*tab)[*n].date_jour.annee)
        {
            afficherErreur(33, 15, "une Presence avec le meme matricule a deja ete enregistree a cette date!");
            Sleep(3000);
            goto reprise;
        }
    }

    // saisie de l'heure

repriseH:
    gotoxy(33, 17);

    while (scanf("%d %d",
                 &(*tab)[*n].heure_arrive.heure,
                 &(*tab)[*n].heure_arrive.minutes) != 2)
    {
        while (getchar() != '\n')
            ;

        afficherErreur(33, 17, "Heure invalide !");
    }

    if ((*tab)[*n].heure_arrive.heure < 0 ||
        (*tab)[*n].heure_arrive.heure > 24 ||
        (*tab)[*n].heure_arrive.minutes < 0 ||
        (*tab)[*n].heure_arrive.minutes > 59)
    {
        afficherErreur(33, 17, "Heure invalide !");
        goto repriseH;
    }

    (*tab)[*n].heure_depart.heure = -1;
    (*tab)[*n].heure_depart.minutes = -1;

    (*n)++;

    gotoxy(33, 20);
    printf("Ajout reussi !");
}
//============================================== FONCTION 8 ==============================================

void afficherPresences(Employe *tab, int n)
{
    int i;

    printf("\n================ LISTE DES PRESENCES =================\n");

    if (n == 0)
    {
        printf("Aucune presence.\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        printf("\n[%d]\n", i + 1);
        printf("Numero : %d\n", tab[i].Num_enregistrement);
        printf("Matricule : %d\n", tab[i].matricule);
        printf("Nom : %s %s\n", tab[i].Nom, tab[i].Prenom);
        printf("Departement : %s\n", tab[i].Departement);

        printf("Date : %02d/%02d/%d\n",
               tab[i].date_jour.jour,
               tab[i].date_jour.mois,
               tab[i].date_jour.annee);

        printf("Arrivee : %02d:%02d\n",
               tab[i].heure_arrive.heure,
               tab[i].heure_arrive.minutes);

        if (tab[i].heure_depart.heure == -1)
            printf("Depart : Non enregistre\n");
        else
            printf("Depart : %02d:%02d\n",
                   tab[i].heure_depart.heure,
                   tab[i].heure_depart.minutes);
    }

    printf("\n=====================================================\n");
}
// ===================================================== FONCTION 2 =================================================

void enregistrerDepart(Employe *tab, int n)
{
    int mat, i, trouve = 0;
    Date d;

    if (n == 0)
    {
        gotoxy(45, 9);
        printf("==============================================================================================================");
        gotoxy(45, 10);
        printf("==                                 Desoler Aucune presence n'est enregistree !                             ==\n");
        gotoxy(45, 12);
        printf("==     Pour pouvoir Enregistrer le depart d'un employe, vous devez d'abord enregistrer les presences !     ==\n");
        gotoxy(45, 14);
        printf("==============================================================================================================");

        gotoxy(45, 16);
        printf("Appuyez sur une touche pour continuer...");
        getch();

        return;
    }

    gotoxy(45, 10);
    printf("============================= Enregistrer l'heure de depart ==============================");
    gotoxy(45, 13);
    printf("Pour enregistrer l'heure de depart d'un employe, veillez saisir son matricule, renseigner \n\t\t\t\t\t\t\t la date puis l'heure de depart souhaitee");

    gotoxy(45, 16);
    printf("==   Matricule : ");
    gotoxy(45, 17);
    printf("==   Date (jj mm aaaa) : ");
    gotoxy(45, 18);
    printf("==   Heure depart (hh mm) : ");
    gotoxy(45, 21);
    printf("===========================================================================================");

    gotoxy(62, 16);
    while (scanf("%d", &mat) != 1)
    {
        afficherErreur(62, 16, "Matricule invalide, Reesayer...");
        Sleep(3000);
        while (getchar() != '\n')
            ;
    }
    gotoxy(69, 17);
    while (scanf("%d %d %d", &d.jour, &d.mois, &d.annee) != 3)
    {
        afficherErreur(69, 17, "date invalide, Reesayer...");
        Sleep(3000);
        while (getchar() != '\n')
            ;
    }

    for (i = 0; i < n; i++)
    {
        if (tab[i].matricule == mat &&
            tab[i].date_jour.jour == d.jour &&
            tab[i].date_jour.mois == d.mois &&
            tab[i].date_jour.annee == d.annee)
        {
        demH: // printf("Heure depart (hh mm) : ");
            gotoxy(73, 18);

            while (scanf("%d %d",
                         &tab[i].heure_depart.heure,
                         &tab[i].heure_depart.minutes) != 2)
            {
                afficherErreur(73, 18, "Heure invalide ! Reessayez..");
                while (getchar() != '\n')
                    ;
            }

            if (tab[i].heure_arrive.heure > tab[i].heure_depart.heure)
            {
                afficherErreur(73, 18, "Heure de depart ne peut pas etre inferieur a l'heure d'arrive");
                while (getchar() != '\n')
                    ;
                goto demH;
            }

            gotoxy(45, 23);

            printf("Heure de depart enregistree !\n");
            Sleep(3000);
            trouve = 1;
            break;
        }
    }

    if (trouve != 1)
    {
        gotoxy(45, 22);

        printf("Aucune presence trouvee pour cet employe a cette date.\n");
        Sleep(3000);
    }
}

//=======================================================Fonction 3==================================================

void verifierPresence(Employe *tab, int n)
{
    int mat, i, trouve = 0;
    Date d;

    if (n == 0)
    {
        gotoxy(45, 9);
        printf("=================================================================================================");
        gotoxy(45, 10);
        printf("==                      Desoler Aucune presence n'est enregistree !                            ==\n");
        gotoxy(45, 12);
        printf("==     Pour pouvoir verifier les presences, vous devez d'abord enregistrer les presences !     ==\n");
        gotoxy(45, 14);
        printf("=================================================================================================");

        gotoxy(45, 16);
        printf("Appuyez sur une touche pour continuer...");
        getch();

        return;
    }

    gotoxy(45, 10);
    printf("========================= Verification de presence a une date ==========================");
    gotoxy(45, 13);
    printf("Pour verifier la presence d'un employe, veillez saisir son matricule et renseigner \n\t\t\t\t\t\t\t la date a la quelle vous souhaiter verifier la presence");

    gotoxy(45, 16);
    printf("==   Matricule : ");
    gotoxy(45, 17);
    printf("==   Date (jj mm aaaa) : ");
    gotoxy(45, 19);
    printf("=========================================================================================");

    gotoxy(62, 16);
    while (scanf("%d", &mat) != 1)
    {
        afficherErreur(62, 16, "Matricule invalide, Reesayer...");
        Sleep(3000);
        while (getchar() != '\n')
            ;
    }
    gotoxy(69, 17);
    while (scanf("%d %d %d", &d.jour, &d.mois, &d.annee) != 3)
    {
        afficherErreur(69, 17, "date invalide, Reesayer...");
        Sleep(3000);
        while (getchar() != '\n')
            ;
    }

    gotoxy(45, 22);

    for (i = 0; i < n; i++)
    {
        if (tab[i].matricule == mat &&
            tab[i].date_jour.jour == d.jour &&
            tab[i].date_jour.mois == d.mois &&
            tab[i].date_jour.annee == d.annee)
        {
            printf("\nPresence trouvee avec succes !\n");

            printf("Numero d'enregistrement: %d\n", tab[i].Num_enregistrement);
            printf("Nom : %s %s\n", tab[i].Nom, tab[i].Prenom);
            printf("Departement : %s\n", tab[i].Departement);

            printf("Heure d'Arrivee : %02d:%02d\n",
                   tab[i].heure_arrive.heure,
                   tab[i].heure_arrive.minutes);

            if (tab[i].heure_depart.heure == -1)
                printf("heure de Depart : Non enregistre\n");
            else
                printf("Heure de Depart : %02d:%02d\n",
                       tab[i].heure_depart.heure,
                       tab[i].heure_depart.minutes);

            printf("Appuyez sur une touche pour continuer...");
            getch();

            trouve = 1;
            break;
        }
    }

    if (trouve == 0)
    {
        gotoxy(45, 22);

        printf("Aucune presence trouvee pour cet employe a cette date.\n");
        Sleep(3000);
    }
}

//=======================================================FONCTION 4 =================================================
void supprimerPresence(Employe *tab, int *n)
{
    int mat, i, j, trouve = 0;
    Date d;

    if (*n == 0)
    {
        gotoxy(45, 9);
        printf("=================================================================================================");
        gotoxy(45, 10);
        printf("==                      Desoler Aucune presence n'est enregistree !                            ==\n");
        gotoxy(45, 12);
        printf("==     Pour pouvoir Supprimer les presences, vous devez d'abord enregistrer les presences !     ==\n");
        gotoxy(45, 14);
        printf("=================================================================================================");

        gotoxy(45, 16);
        printf("Appuyez sur une touche pour continuer...");
        getch();

        return;
    }

    gotoxy(45, 10);
    printf("========================= Supprimer une Presence ==========================");
    gotoxy(45, 13);
    printf("Pour supprimer la presence d'un employe, veillez saisir son matricule et renseigner \n\t\t\t\t\t\t\t la date a la quelle il a ete present ");

    gotoxy(45, 16);
    printf("==   Matricule : ");
    gotoxy(45, 17);
    printf("==   Date (jj mm aaaa) : ");
    gotoxy(45, 19);
    printf("=========================================================================================");

    gotoxy(62, 16);
    while (scanf("%d", &mat) != 1)
    {
        afficherErreur(62, 16, "Matricule invalide, Reesayer...");
        Sleep(3000);
        while (getchar() != '\n')
            ;
    }
    gotoxy(70, 17);
    while (scanf("%d %d %d", &d.jour, &d.mois, &d.annee) != 3)
    {
        afficherErreur(69, 17, "date invalide, Reesayer...");
        Sleep(3000);
        while (getchar() != '\n')
            ;
    }

    for (i = 0; i < *n; i++)
    {
        if (tab[i].matricule == mat &&
            tab[i].date_jour.jour == d.jour &&
            tab[i].date_jour.mois == d.mois &&
            tab[i].date_jour.annee == d.annee)
        {
            // décalage du tableau vers la gauche
            for (j = i; j < *n - 1; j++)
            {
                tab[j] = tab[j + 1];
            }

            (*n)--; // diminuer le nombre
            gotoxy(45, 22);
            printf("Presence supprimee avec succes !\n");
            Sleep(3000);
            trouve = 1;
            break;
        }
    }

    if (trouve == 0)
    {
        gotoxy(45, 22);

        printf("Suppression impossible car Aucune presence trouvee pour cet employe a cette date. \n");
        Sleep(3000);
    }
}

//=======================================================FONCTION5=====================================================
void modifierPresence(Employe *tab, int n)
{
    int mat, i, trouve = 0;
    Date d;

    if (n == 0)
    {
        gotoxy(45, 9);
        printf("=================================================================================================");
        gotoxy(45, 10);
        printf("==                      Desoler Aucune presence n'est enregistree !                            ==\n");
        gotoxy(45, 12);
        printf("==     Pour pouvoir modifier les presences, vous devez d'abord les enregistrer !     ==\n");
        gotoxy(45, 14);
        printf("=================================================================================================");

        gotoxy(45, 16);
        printf("Appuyez sur une touche pour continuer...");
        getch();
        return;
    }
    gotoxy(45, 10);
    printf("========================= Modification de Presence ==========================");
    gotoxy(45, 13);
    printf("Pour modifier la presence d'un employe, veillez saisir son matricule et renseigner \n\t\t\t\t\t\t\t la date a la quelle il a ete present ");

    gotoxy(45, 16);
    printf("==   Matricule : ");
    gotoxy(45, 17);
    printf("==   Date (jj mm aaaa) : ");
    gotoxy(45, 19);
    printf("=========================================================================================");

    gotoxy(62, 16);
    while (scanf("%d", &mat) != 1)
    {
        afficherErreur(62, 16, "Matricule invalide, Reesayer...");
        Sleep(3000);
        while (getchar() != '\n')
            ;
    }
    gotoxy(70, 17);
    while (scanf("%d %d %d", &d.jour, &d.mois, &d.annee) != 3)
    {
        afficherErreur(69, 17, "date invalide, Reesayer...");
        Sleep(3000);
        while (getchar() != '\n')
            ;
    }

    for (i = 0; i < n; i++)
    {
        if (tab[i].matricule == mat &&
            tab[i].date_jour.jour == d.jour &&
            tab[i].date_jour.mois == d.mois &&
            tab[i].date_jour.annee == d.annee)
        {
            printf("\nPresence trouvee ! \n Modification...\n");
            printf("Indice trouve = %d\n", i);
            Sleep(3000);

            system("cls");
            gotoxy(30, 2);
            printf("======================================= MODIFICATION DE PRESENCE =============================================");

            gotoxy(5, 5);
            printf("nouveau Numero d'enregistrement :  ");

            gotoxy(5, 7);
            printf("nouveau Matricule               :  ");

            gotoxy(5, 9);
            printf("nouveau Nom                     :  ");

            gotoxy(5, 11);
            printf("nouveau Prenom                  :  ");

            gotoxy(5, 13);
            printf("nouveau Departement             :  ");

            gotoxy(5, 15);
            printf("nouvelle Date (jj mm aaaa)      :  ");

            gotoxy(5, 17);
            printf("nouvelle Heure arrivee(hh mm)   :  ");

            gotoxy(5, 19);
            printf("nouvelle Heure depart(hh mm)    :  ");

            int j;
            int num;
            int existe;

            // saisie du numero d'enregistrement

            do
            {
                existe = 0;

                gotoxy(41, 5);

                while (scanf("%d", &num) != 1)
                {
                    while (getchar() != '\n')
                        ;
                    afficherErreur(41, 5, "Numero invalide !");
                }

                for (j = 0; j < n; j++)
                {
                    if (j != i &&
                        tab[j].Num_enregistrement == num)
                    {
                        existe = 1;
                        afficherErreur(41, 5, "Numero deja existant !");
                    }
                }

            } while (existe);

            tab[i].Num_enregistrement = num;

            // saisie du matricule

            gotoxy(41, 7);

            while (scanf("%d", &mat) != 1)
            {
                while (getchar() != '\n')
                    ;
                afficherErreur(41, 7, "Matricule invalide !");
            }

            tab[i].matricule = mat;

            // saisie du nom

            gotoxy(41, 9);
            scanf("%s", tab[i].Nom);

            // saisie du prenom

            gotoxy(41, 11);
            scanf("%s", tab[i].Prenom);

            // saisie du departement

            gotoxy(41, 13);
            scanf("%s", tab[i].Departement);

            // saisie de la date

        dateModif:

            gotoxy(41, 15);

            while (scanf("%d %d %d",
                         &tab[i].date_jour.jour,
                         &tab[i].date_jour.mois,
                         &tab[i].date_jour.annee) != 3)
            {
                while (getchar() != '\n')
                    ;
                afficherErreur(41, 15, "Date invalide !");
            }

            if (tab[i].date_jour.jour < 1 ||
                tab[i].date_jour.jour > 31 ||
                tab[i].date_jour.mois < 1 ||
                tab[i].date_jour.mois > 12 ||
                tab[i].date_jour.annee < 1900 ||
                tab[i].date_jour.annee > 9999)
            {
                afficherErreur(41, 15, "Date invalide !");
                goto dateModif;
            }

            for (j = 0; j < n; j++)
            {
                if (j != i &&
                    tab[j].matricule == tab[i].matricule &&
                    tab[j].date_jour.jour == tab[i].date_jour.jour &&
                    tab[j].date_jour.mois == tab[i].date_jour.mois &&
                    tab[j].date_jour.annee == tab[i].date_jour.annee)
                {
                    afficherErreur(41, 15,
                                   "Presence deja enregistree !");
                    goto dateModif;
                }
            }

            // saisie de heure d'arrive

        heureArrivee:

            gotoxy(41, 17);

            while (scanf("%d %d",
                         &tab[i].heure_arrive.heure,
                         &tab[i].heure_arrive.minutes) != 2)
            {
                while (getchar() != '\n')
                    ;
                afficherErreur(41, 17,
                               "Heure invalide !");
            }

            if (tab[i].heure_arrive.heure < 0 ||
                tab[i].heure_arrive.heure > 23 ||
                tab[i].heure_arrive.minutes < 0 ||
                tab[i].heure_arrive.minutes > 59)
            {
                afficherErreur(41, 17, "Heure invalide !");
                goto heureArrivee;
            }

            // saisie de heure de depart

        heureDepart:

            gotoxy(41, 19);

            while (scanf("%d %d",
                         &tab[i].heure_depart.heure,
                         &tab[i].heure_depart.minutes) != 2)
            {
                while (getchar() != '\n')
                    ;
                afficherErreur(41, 19,
                               "Heure invalide !");
            }

            if (tab[i].heure_depart.heure < 0 ||
                tab[i].heure_depart.heure > 23 ||
                tab[i].heure_depart.minutes < 0 ||
                tab[i].heure_depart.minutes > 59)
            {
                afficherErreur(41, 19,
                               "Heure invalide !");
                goto heureDepart;
            }

            if (tab[i].heure_depart.heure <
                tab[i].heure_arrive.heure)
            {
                afficherErreur(41, 19,
                               "Depart inferieur a arrivee !");
                goto heureDepart;
            }

            gotoxy(41, 22);
            printf("Modification reussie !");

            Sleep(3000);

            trouve = 1;
            break;
        }
    }

    if (trouve == 0)
    {
        printf("Presence non trouvee !\n");
    }
}

//=======================================================FONCTION6=====================================================
void nombrePresences(Employe *tab, int n)
{

    if (n == 0)
    {
        gotoxy(45, 9);
        printf("=================================================================================================");
        gotoxy(45, 10);
        printf("==                      Desoler Aucune presence n'est enregistree !                            ==\n");
        gotoxy(45, 12);
        printf("==      Pour voir le nombre de presences, vous devez d'abord les enregistrer !                 ==\n");
        gotoxy(45, 14);
        printf("=================================================================================================");

        gotoxy(45, 16);
        printf("Appuyez sur une touche pour continuer...");
        getch();
    }
    else
    {

        gotoxy(45, 9);
        printf("=================================================================================================");
        gotoxy(45, 10);
        printf("==                                 Nombre total de presences                                  ==\n");
        gotoxy(45, 12);
        printf("==                                         %d                                                  ==\n", n);
        gotoxy(45, 14);
        printf("=================================================================================================");

        gotoxy(45, 16);
        printf("Appuyez sur une touche pour continuer...");
        getch();
    }
}

//=======================================================FONCTION7=====================================================
void listePresencesParDate(Employe *tab, int n)
{
    int i, trouve = 0;
    Date d;
    if (n == 0)
    {
        gotoxy(45, 9);
        printf("=================================================================================================");
        gotoxy(45, 10);
        printf("==                      Desoler Aucune presence n'est enregistree !                            ==\n");
        gotoxy(45, 12);
        printf("==      Pour voir le nombre de presences, vous devez d'abord les enregistrer !                 ==\n");
        gotoxy(45, 14);
        printf("=================================================================================================");

        gotoxy(45, 16);
        printf("Appuyez sur une touche pour continuer...");
        getch();
        return;
    }

    printf("Entrer la date (jj mm aaaa) : ");
    while (scanf("%d %d %d", &d.jour, &d.mois, &d.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n')
            ;
    }

    printf("\n==================== LISTE DES PRESENCES A CETTE DATE ==================\n");

    for (i = 0; i < n; i++)
    {
        if (tab[i].date_jour.jour == d.jour &&
            tab[i].date_jour.mois == d.mois &&
            tab[i].date_jour.annee == d.annee)
        {
            printf("\nNumero d'enregistrement: %d\n", tab[i].Num_enregistrement);
            printf("Matricule : %d\n", tab[i].matricule);
            printf("Nom : %s %s\n", tab[i].Nom, tab[i].Prenom);
            printf("Departement : %s\n", tab[i].Departement);

            printf("Arrivee : %02d:%02d\n",
                   tab[i].heure_arrive.heure,
                   tab[i].heure_arrive.minutes);

            if (tab[i].heure_depart.heure == -1)
                printf("Depart : Non enregistre\n");
            else
                printf("Depart : %02d:%02d\n",
                       tab[i].heure_depart.heure,
                       tab[i].heure_depart.minutes);

            trouve = 1;
            printf("\nAppuyez sur une touche pour continuer...");
            getch();
        }
    }

    if (trouve == 0)
    {
        printf("Aucune presence pour cette date.\n");
        Sleep(3000);
    }
}

//=======================================================FONCTION9=====================================================
void presenceEmployeDate(Employe *tab, int n)
{
    int mat, i, trouve = 0;
    Date d;

    if (n == 0)
    {
        gotoxy(45, 9);
        printf("============================================================================================================");
        gotoxy(45, 10);
        printf("==                           Desoler Aucune presence n'est enregistree !                                  ==\n");
        gotoxy(45, 12);
        printf("==      Pour voir la presence d'un employé par date, vous devez d'abord les enregistrer !                 ==\n");
        gotoxy(45, 14);
        printf("============================================================================================================");

        gotoxy(45, 16);
        printf("Appuyez sur une touche pour continuer...");
        getch();
        return;
    }

    gotoxy(45, 10);
    printf("========================= Verification de la presence d'un employe par date ==========================");
    gotoxy(45, 13);
    printf("Pour verifier la presence d'un employe, veillez saisir son matricule et renseigner \n\t\t\t\t\t\t\t la date a la quelle vous souhaiter verifier la presence");

    gotoxy(45, 16);
    printf("==   Matricule : ");
    gotoxy(45, 17);
    printf("==   Date (jj mm aaaa) : ");
    gotoxy(45, 19);
    printf("========================================================================================================");

    gotoxy(62, 16);
    while (scanf("%d", &mat) != 1)
    {
        afficherErreur(62, 16, "Matricule invalide, Reesayer...");
        Sleep(3000);
        while (getchar() != '\n')
            ;
    }
    gotoxy(69, 17);
    while (scanf("%d %d %d", &d.jour, &d.mois, &d.annee) != 3)
    {
        afficherErreur(69, 17, "date invalide, Reesayer...");
        Sleep(3000);
        while (getchar() != '\n')
            ;
    }
    gotoxy(45, 22);

    for (i = 0; i < n; i++)
    {
        if (tab[i].matricule == mat &&
            tab[i].date_jour.jour == d.jour &&
            tab[i].date_jour.mois == d.mois &&
            tab[i].date_jour.annee == d.annee)
        {
            printf("\nPresence trouvee avec succes !\n");

            printf("Numero d'enregistrement: %d\n", tab[i].Num_enregistrement);
            printf("Nom : %s %s\n", tab[i].Nom, tab[i].Prenom);
            printf("Departement : %s\n", tab[i].Departement);

            printf("Heure d'Arrivee : %02d:%02d\n",
                   tab[i].heure_arrive.heure,
                   tab[i].heure_arrive.minutes);

            if (tab[i].heure_depart.heure == -1)
                printf("heure de Depart : Non enregistre\n");
            else
                printf("Heure de Depart : %02d:%02d\n",
                       tab[i].heure_depart.heure,
                       tab[i].heure_depart.minutes);

            printf("Appuyez sur une touche pour continuer...");
            getch();

            trouve = 1;
            break;
        }
    }

    if (trouve == 0)
    {
        gotoxy(45, 22);

        printf("Aucune presence trouvee pour cet employe a cette date.\n");
        Sleep(3000);
    }
}

//=======================================================FONCTION10===================================================
int comparerDates(Date d1, Date d2)
{

    if (d1.annee != d2.annee)
        return d1.annee - d2.annee;
    if (d1.mois != d2.mois)
        return d1.mois - d2.mois;
    return d1.jour - d2.jour;
}

void presenceEntreDeuxDates(Employe *tab, int n)
{
    int mat, i, trouve = 0;
    int ligne = 17;
    Date d1, d2;

    if (n == 0)
    {
        gotoxy(45, 9);
        printf("============================================================================================================");
        gotoxy(45, 10);
        printf("==                           Desoler Aucune presence n'est enregistree !                                  ==");
        gotoxy(45, 12);
        printf("==     Pour voir les presences entre deux dates, vous devez d'abord les enregistrer !                    ==");
        gotoxy(45, 14);
        printf("============================================================================================================");

        return;
    }

    system("cls");

    gotoxy(5, 2);
    printf("=========================== PRESENCE ENTRE DEUX DATES ===========================");

    gotoxy(5, 6);
    printf("Matricule                 : ");

    gotoxy(5, 8);
    printf("Date debut (jj mm aaaa)   : ");

    gotoxy(5, 10);
    printf("Date fin (jj mm aaaa)     : ");

    gotoxy(5, 12);
    printf("===============================================================================");

    // Saisie du matricule

    gotoxy(33, 6);
    while (scanf("%d", &mat) != 1)
    {
        while (getchar() != '\n')
            ;

        afficherErreur(33, 6, "Matricule invalide !");
    }

    // Saisie date debut

dateDebut:

    gotoxy(33, 8);
    while (scanf("%d %d %d",
                 &d1.jour,
                 &d1.mois,
                 &d1.annee) != 3)
    {
        while (getchar() != '\n')
            ;

        afficherErreur(33, 8, "Date invalide !");
    }

    if (d1.jour < 1 || d1.jour > 31 ||
        d1.mois < 1 || d1.mois > 12 ||
        d1.annee < 1900 || d1.annee > 9999)
    {
        afficherErreur(33, 8, "Date invalide !");
        goto dateDebut;
    }

    // Saisie date fin

dateFin:

    gotoxy(33, 10);
    while (scanf("%d %d %d",
                 &d2.jour,
                 &d2.mois,
                 &d2.annee) != 3)
    {
        while (getchar() != '\n')
            ;

        afficherErreur(33, 10, "Date invalide !");
    }

    if (d2.jour < 1 || d2.jour > 31 ||
        d2.mois < 1 || d2.mois > 12 ||
        d2.annee < 1900 || d2.annee > 9999)
    {
        afficherErreur(33, 10, "Date invalide !");
        goto dateFin;
    }

    // Vérification de la période

    if (comparerDates(d1, d2) > 0)
    {
        afficherErreur(33, 10, "La Date de debut ne peut pas etre superieure a la Date fin !");
        goto dateFin;
    }

    gotoxy(5, 15);
    printf("==================== PRESENCES TROUVEES ====================");

    for (i = 0; i < n; i++)
    {
        if (tab[i].matricule == mat &&
            comparerDates(tab[i].date_jour, d1) >= 0 &&
            comparerDates(tab[i].date_jour, d2) <= 0)
        {
            gotoxy(5, ligne);

            printf("Presence trouvee le : %02d/%02d/%d",
                   tab[i].date_jour.jour,
                   tab[i].date_jour.mois,
                   tab[i].date_jour.annee);

            ligne += 2;
            trouve = 1;
        }
    }

    if (!trouve)
    {
        gotoxy(5, 17);
        printf("Aucune presence trouvee !");
    }

}

//=======================================================FONCTION11======================================================
void toutesPresencesEmploye(Employe *tab, int n)
{
    int mat, i, trouve = 0;
    if (n == 0)
    {
        printf("Aucune presence enregistree !\n");
        return;
    }

    printf("Matricule : ");
    while (scanf("%d", &mat) != 1)
    {
        printf("Matricule invalide ! Reessayez : ");
        while (getchar() != '\n')
            ;
    }

    for (i = 0; i < n; i++)
    {
        if (tab[i].matricule == mat)
        {
            printf("\nDate : %02d/%02d/%d\n",
                   tab[i].date_jour.jour,
                   tab[i].date_jour.mois,
                   tab[i].date_jour.annee);

            trouve = 1;
        }
    }

    if (!trouve)
        printf("Aucune presence trouvee.\n");
}

//=======================================================FONCTION12========================================================
void presenceDepartementDate(Employe *tab, int n)
{
    char dep[50];
    int i, count = 0;
    Date d;
    if (n == 0)
    {
        printf("Aucune presence enregistree !\n");
        return;
    }

    printf("Departement : ");
    scanf("%s", dep);

    printf("Date (jj mm aaaa) : ");
    while (scanf("%d %d %d", &d.jour, &d.mois, &d.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n')
            ;
    }

    for (i = 0; i < n; i++)
    {
        if (strcmp(tab[i].Departement, dep) == 0 &&
            tab[i].date_jour.jour == d.jour &&
            tab[i].date_jour.mois == d.mois &&
            tab[i].date_jour.annee == d.annee)
        {
            count++;
        }
    }

    printf("Nombre de presences : %d\n", count);
}

//========================================================FONCTION13======================================================
void presenceDepartementEntreDates(Employe *tab, int n)
{
    char dep[50];
    int i, count = 0;
    Date d1, d2;
    if (n == 0)
    {
        printf("Aucune presence enregistree !\n");
        return;
    }
    printf("Departement : ");
    scanf("%s", dep);

    printf("Date debut : ");
    while (scanf("%d %d %d", &d1.jour, &d1.mois, &d1.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n')
            ;
    }

    printf("Date fin : ");
    while (scanf("%d %d %d", &d2.jour, &d2.mois, &d2.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n')
            ;
    }

    for (i = 0; i < n; i++)
    {
        if (strcmp(tab[i].Departement, dep) == 0 &&
            comparerDates(tab[i].date_jour, d1) >= 0 &&
            comparerDates(tab[i].date_jour, d2) <= 0)
        {
            count++;
        }
    }

    printf("Nombre de presences : %d\n", count);
}

//========================================================FOCTION14========================================================
void situationGlobale(Employe *tab, int n)
{
    if (n == 0)
    {
        printf("Aucune presence enregistree !\n");
        return;
    }

    int i;

    for (i = 0; i < n; i++)
    {
        int j, count = 0;

        for (j = 0; j < n; j++)
        {
            if (strcmp(tab[i].Departement, tab[j].Departement) == 0)
            {
                count++;
            }
        }

        printf("Departement %s : %d presences\n",
               tab[i].Departement, count);
    }
}
