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


// ====================================================== GOTOXY =============================================
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
connexion : 
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

    if(strcmp(login, "bgras") != 0 || strcmp(password, "mdp") != 0)
    {
        gotoxy(60, 18); printf("Login ou password incorrect ! veuillez reessayer ");
        Sleep(3000);
        system("cls");
        goto connexion;

    }
    else {
        gotoxy(60, 18); printf("Connexion Reussie ! ");
        Sleep(2000);
        system("cls");}
    
}

//============================================== FONCTIO 8 ==============================================

void afficherPresences(Employe *tab, int n)
{
    int i;

    printf("\n================ LISTE DES PRESENCES =================\n");

    if(n == 0)
    {
        printf("Aucune presence.\n");
        return;
    }

    for(i = 0; i < n; i++)
    {
        printf("\n[%d]\n", i+1);
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

        if(tab[i].heure_depart.heure == -1)
            printf("Depart : Non enregistre\n");
        else
            printf("Depart : %02d:%02d\n",
                tab[i].heure_depart.heure,
                tab[i].heure_depart.minutes);
    }

    printf("\n=====================================================\n");
}



// =============================================== FONCTION 1 =================================================

void enregistrerPresence(Employe **tab, int *n)
{
    int i;

    // allocation dynamique
    *tab = (Employe*) realloc(*tab, (*n + 1) * sizeof(Employe));

    printf("===================== ENREGISTREMENT =========================\n");

    int num;
    printf("Numero : ");
    while (scanf("%d", &num) != 1)
    {
        printf("Numero invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    // verifier unicite du num
    for(i = 0; i < *n; i++)
    {
        if((*tab)[i].Num_enregistrement == num)
        {
            printf("Numero deja existant !\n");
            return;
        }
    }

    (*tab)[*n].Num_enregistrement = num;

    printf("Matricule : ");
    while (scanf("%d", &(*tab)[*n].matricule) != 1)
    {
        printf("Matricule invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    printf("Nom : ");
    scanf("%s", (*tab)[*n].Nom);

    printf("Prenom : ");
    scanf("%s", (*tab)[*n].Prenom);

    printf("Departement : ");
    scanf("%s", (*tab)[*n].Departement);

    printf("Date (jj mm aaaa) : ");
    while (scanf("%d %d %d",
        &(*tab)[*n].date_jour.jour,
        &(*tab)[*n].date_jour.mois,
        &(*tab)[*n].date_jour.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    // verifier doublon date
    for(i = 0; i < *n; i++)
    {
        if((*tab)[i].matricule == (*tab)[*n].matricule &&
           (*tab)[i].date_jour.jour == (*tab)[*n].date_jour.jour &&
           (*tab)[i].date_jour.mois == (*tab)[*n].date_jour.mois &&
           (*tab)[i].date_jour.annee == (*tab)[*n].date_jour.annee)
        {
            printf("Presence deja existante pour cette date !\n");
            return;
        }
    }

    printf("Heure arrivee (hh mm) : ");
    while (scanf("%d %d",
        &(*tab)[*n].heure_arrive.heure,
        &(*tab)[*n].heure_arrive.minutes) != 2)
    {
        printf("Heure invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    // heure depart vide
    (*tab)[*n].heure_depart.heure = -1;
    (*tab)[*n].heure_depart.minutes = -1;

    (*n)++;

    printf("Ajout reussi !\n");
}

// ================= FONCTION 3 =================

void enregistrerDepart(Employe *tab, int n)
{
    int mat, i, trouve = 0;
    Date d;

    printf("Matricule : ");
    while (scanf("%d", &mat) != 1)
    {
        printf("Matricule invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    printf("Date (jj mm aaaa) : ");
    while (scanf("%d %d %d", &d.jour, &d.mois, &d.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    for(i = 0; i < n; i++)
    {
        if(tab[i].matricule == mat &&
           tab[i].date_jour.jour == d.jour &&
           tab[i].date_jour.mois == d.mois &&
           tab[i].date_jour.annee == d.annee)
        {
            printf("Heure depart (hh mm) : ");
            while (scanf("%d %d",
                &tab[i].heure_depart.heure,
                &tab[i].heure_depart.minutes) != 2)
            {
                printf("Heure invalide ! Reessayez : ");
                while (getchar() != '\n');
            }

            printf("Heure de depart enregistree !\n");
            trouve = 1;
            break;
        }
    }

    if(!trouve)
    {
        printf("Presence non trouvee !\n");
    }
}

//===========================Fonction 2================================

void verifierPresence(Employe *tab, int n)
{
    int mat, i, trouve = 0;
    Date d;

    printf("Matricule : ");
    while (scanf("%d", &mat) != 1)
    {
        printf("Matricule invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    printf("Date (jj mm aaaa) : ");
    while (scanf("%d %d %d", &d.jour, &d.mois, &d.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    for(i = 0; i < n; i++)
    {
        if(tab[i].matricule == mat &&
           tab[i].date_jour.jour == d.jour &&
           tab[i].date_jour.mois == d.mois &&
           tab[i].date_jour.annee == d.annee)
        {
            printf("\nPresence trouvee !\n");

            printf("Numero : %d\n", tab[i].Num_enregistrement);
            printf("Nom : %s %s\n", tab[i].Nom, tab[i].Prenom);
            printf("Departement : %s\n", tab[i].Departement);

            printf("Arrivee : %02d:%02d\n",
                tab[i].heure_arrive.heure,
                tab[i].heure_arrive.minutes);

            if(tab[i].heure_depart.heure == -1)
                printf("Depart : Non enregistre\n");
            else
                printf("Depart : %02d:%02d\n",
                    tab[i].heure_depart.heure,
                    tab[i].heure_depart.minutes);

            trouve = 1;
            break;
        }
    }

    if(trouve == 0)
    {
        printf("Aucune presence trouvee pour cet employe a cette date.\n");
    }
}


//============================FONCTION 4 ==========================
void supprimerPresence(Employe *tab, int *n)
{
    int mat, i, j, trouve = 0;
    Date d;

    printf("Matricule : ");
    while (scanf("%d", &mat) != 1)
    {
        printf("Matricule invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    printf("Date (jj mm aaaa) : ");
    while (scanf("%d %d %d", &d.jour, &d.mois, &d.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    for(i = 0; i < *n; i++)
    {
        if(tab[i].matricule == mat &&
           tab[i].date_jour.jour == d.jour &&
           tab[i].date_jour.mois == d.mois &&
           tab[i].date_jour.annee == d.annee)
        {
            // décalage du tableau vers la gauche
            for(j = i; j < *n - 1; j++)
            {
                tab[j] = tab[j + 1];
            }

            (*n)--; // diminuer le nombre
            printf("Presence supprimee avec succes !\n");
            trouve = 1;
            break;
        }
    }

    if(trouve == 0)
    {
        printf("Presence non trouvee !\n");
    }
}


//========================FONCTION5=======================
void modifierPresence(Employe *tab, int n)
{
    int mat, i, trouve = 0;
    Date d;

    printf("Matricule : ");
    while (scanf("%d", &mat) != 1)
    {
        printf("Matricule invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    printf("Date (jj mm aaaa) : ");
    while (scanf("%d %d %d", &d.jour, &d.mois, &d.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    for(i = 0; i < n; i++)
    {
        if(tab[i].matricule == mat &&
           tab[i].date_jour.jour == d.jour &&
           tab[i].date_jour.mois == d.mois &&
           tab[i].date_jour.annee == d.annee)
        {
            printf("\nPresence trouvee ! Modification...\n");

            printf("Nouveau nom : ");
            scanf("%s", tab[i].Nom);

            printf("Nouveau prenom : ");
            scanf("%s", tab[i].Prenom);

            printf("Nouveau departement : ");
            scanf("%s", tab[i].Departement);

            printf("Nouvelle heure d'arrivee (hh mm) : ");
            while (scanf("%d %d",
                &tab[i].heure_arrive.heure,
                &tab[i].heure_arrive.minutes) != 2)
            {
                printf("Heure invalide ! Reessayez : ");
                while (getchar() != '\n');
            }

            printf("Nouvelle heure de depart (hh mm) : ");
            while (scanf("%d %d",
                &tab[i].heure_depart.heure,
                &tab[i].heure_depart.minutes) != 2)
            {
                printf("Heure invalide ! Reessayez : ");
                while (getchar() != '\n');
            }

            printf("Modification reussie !\n");
            trouve = 1;
            break;
        }
    }

    if(trouve == 0)
    {
        printf("Presence non trouvee !\n");
    }
}

//===========================FONCTION6==================
void nombrePresences(Employe *tab, int n)
{
    printf("Nombre total de presences : %d\n", n);

    if(n == 0)
    {
        printf("Aucune presence enregistree.\n");
    }
}

//==================FONCTION7=====================
void listePresencesParDate(Employe *tab, int n)
{
    int i, trouve = 0;
    Date d;

    printf("Entrer la date (jj mm aaaa) : ");
    while (scanf("%d %d %d", &d.jour, &d.mois, &d.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    printf("\n===== LISTE DES PRESENCES A CETTE DATE =====\n");

    for(i = 0; i < n; i++)
    {
        if(tab[i].date_jour.jour == d.jour &&
           tab[i].date_jour.mois == d.mois &&
           tab[i].date_jour.annee == d.annee)
        {
            printf("\nNumero : %d\n", tab[i].Num_enregistrement);
            printf("Matricule : %d\n", tab[i].matricule);
            printf("Nom : %s %s\n", tab[i].Nom, tab[i].Prenom);
            printf("Departement : %s\n", tab[i].Departement);

            printf("Arrivee : %02d:%02d\n",
                tab[i].heure_arrive.heure,
                tab[i].heure_arrive.minutes);

            if(tab[i].heure_depart.heure == -1)
                printf("Depart : Non enregistre\n");
            else
                printf("Depart : %02d:%02d\n",
                    tab[i].heure_depart.heure,
                    tab[i].heure_depart.minutes);

            trouve = 1;
        }
    }

    if(trouve == 0)
    {
        printf("Aucune presence pour cette date.\n");
    }
}


//======================FONCTION9=================
void presenceEmployeDate(Employe *tab, int n)
{
    int mat, i, trouve = 0;
    Date d;

    printf("Matricule : ");
    while (scanf("%d", &mat) != 1)
    {
        printf("Matricule invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    printf("Date (jj mm aaaa) : ");
    while (scanf("%d %d %d", &d.jour, &d.mois, &d.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    for(i = 0; i < n; i++)
    {
        if(tab[i].matricule == mat &&
           tab[i].date_jour.jour == d.jour &&
           tab[i].date_jour.mois == d.mois &&
           tab[i].date_jour.annee == d.annee)
        {
            printf("\nNom : %s %s\n", tab[i].Nom, tab[i].Prenom);
            printf("Arrivee : %02d:%02d\n",
                tab[i].heure_arrive.heure,
                tab[i].heure_arrive.minutes);

            trouve = 1;
        }
    }

    if(!trouve)
        printf("Aucune presence trouvee.\n");
}



//========================FONCTION10=======================
int comparerDates(Date d1, Date d2)
{
    if(d1.annee != d2.annee)
        return d1.annee - d2.annee;
    if(d1.mois != d2.mois)
        return d1.mois - d2.mois;
    return d1.jour - d2.jour;
}

void presenceEntreDeuxDates(Employe *tab, int n)
{
    int mat, i, trouve = 0;
    Date d1, d2;

    printf("Matricule : ");
    while (scanf("%d", &mat) != 1)
    {
        printf("Matricule invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    printf("Date debut (jj mm aaaa) : ");
    while (scanf("%d %d %d", &d1.jour, &d1.mois, &d1.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    printf("Date fin (jj mm aaaa) : ");
    while (scanf("%d %d %d", &d2.jour, &d2.mois, &d2.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    for(i = 0; i < n; i++)
    {
        if(tab[i].matricule == mat &&
           comparerDates(tab[i].date_jour, d1) >= 0 &&
           comparerDates(tab[i].date_jour, d2) <= 0)
        {
            printf("\nDate : %02d/%02d/%d\n",
                tab[i].date_jour.jour,
                tab[i].date_jour.mois,
                tab[i].date_jour.annee);

            trouve = 1;
        }
    }

    if(!trouve)
        printf("Aucune presence trouvee.\n");
}



//==================FONCTION11=========================
void toutesPresencesEmploye(Employe *tab, int n)
{
    int mat, i, trouve = 0;

    printf("Matricule : ");
    while (scanf("%d", &mat) != 1)
    {
        printf("Matricule invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    for(i = 0; i < n; i++)
    {
        if(tab[i].matricule == mat)
        {
            printf("\nDate : %02d/%02d/%d\n",
                tab[i].date_jour.jour,
                tab[i].date_jour.mois,
                tab[i].date_jour.annee);

            trouve = 1;
        }
    }

    if(!trouve)
        printf("Aucune presence trouvee.\n");
}


//===================FONCTION12===================
void presenceDepartementDate(Employe *tab, int n)
{
    char dep[50];
    int i, count = 0;
    Date d;

    printf("Departement : ");
    scanf("%s", dep);

    printf("Date (jj mm aaaa) : ");
    while (scanf("%d %d %d", &d.jour, &d.mois, &d.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    for(i = 0; i < n; i++)
    {
        if(strcmp(tab[i].Departement, dep) == 0 &&
           tab[i].date_jour.jour == d.jour &&
           tab[i].date_jour.mois == d.mois &&
           tab[i].date_jour.annee == d.annee)
        {
            count++;
        }
    }

    printf("Nombre de presences : %d\n", count);
}


//===========================FONCTION13====================
void presenceDepartementEntreDates(Employe *tab, int n)
{
    char dep[50];
    int i, count = 0;
    Date d1, d2;

    printf("Departement : ");
    scanf("%s", dep);

    printf("Date debut : ");
    while (scanf("%d %d %d", &d1.jour, &d1.mois, &d1.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    printf("Date fin : ");
    while (scanf("%d %d %d", &d2.jour, &d2.mois, &d2.annee) != 3)
    {
        printf("Date invalide ! Reessayez : ");
        while (getchar() != '\n');
    }

    for(i = 0; i < n; i++)
    {
        if(strcmp(tab[i].Departement, dep) == 0 &&
           comparerDates(tab[i].date_jour, d1) >= 0 &&
           comparerDates(tab[i].date_jour, d2) <= 0)
        {
            count++;
        }
    }

    printf("Nombre de presences : %d\n", count);
}



//===================FOCTION14==========================
void situationGlobale(Employe *tab, int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        int j, count = 0;

        for(j = 0; j < n; j++)
        {
            if(strcmp(tab[i].Departement, tab[j].Departement) == 0)
            {
                count++;
            }
        }

        printf("Departement %s : %d presences\n",
               tab[i].Departement, count);
    }
}


