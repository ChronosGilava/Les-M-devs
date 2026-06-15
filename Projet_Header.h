#ifndef __PROJET_HEADER__
#define __PROJET_HEADER__


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

// ===================================================== STRUCTURES ==============================================================

typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct {
    int heure;
    int minutes;
} Heure;

typedef struct {
    int Num_enregistrement;
    int matricule;
    char Nom[50];
    char Prenom[50];
    char Departement[50];
    Date date_jour;
    Heure heure_arrive;
    Heure heure_depart;
} Employe;

//====================================================================================================================================


void gotoxy(int x, int y);
void pesentation();
void auth();
void afficherErreur(int x, int y, char message[]);
void afficherPresences(Employe *tab, int n);
void enregistrerPresence(Employe **tab, int *n);
void enregistrerDepart(Employe *tab, int n);
void verifierPresence(Employe *tab, int n);
void supprimerPresence(Employe *tab, int *n);
void modifierPresence(Employe *tab, int n);
void nombrePresences(Employe *tab, int n);
void listePresencesParDate(Employe *tab, int n);
void presenceEmployeDate(Employe *tab, int n);
int comparerDates(Date d1, Date d2);
void toutesPresencesEmploye(Employe *tab, int n);
void presenceDepartementDate(Employe *tab, int n);
void situationGlobale(Employe *tab, int n);













#endif