#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define b 6 //changez ce nombre si vous voulez une autre amplitude dans l'etageres

typedef struct enreg{ //enregistrement d'une seule donnée (livre et ses etats)
  char titre[50]; 
  char ISBN[1024]; //clé unique represantant chaque livre,qu'on utilise pour la recherche
  bool emprunte ; //si emprunte = true , le livre emprunte
}livre ;
// pour mieux comprendre la structure de livre 
/* un livre ici est un cache de livre qui contient le livre en papier mais aussi 
une etiquette ISBN et une feuille rouge ou vert selon l'etat d'emprunte, du coup 
le livre peut etre non disponible mais sa pochette existe dans l'etagere */

typedef struct Tenreg{ //enregistrement d'un seul etager
 livre Tab[b] ; //b nombre maximal de livre par etage
 int nbr ; //et le nombre de livres existantes avec eff = 0
 int last_posi ;//et la position du dernier livre sur l'etagere , exemple : .. 20 .. 30 (nbr = 2 , last_posi = 3)
}etagere ;

typedef struct Entet{ // // de l'entète
 int nbr_livre;//nbr de livres total ( memeu )
 int nbr_etagere;
 int nbr_emprunte ;//nbr de livres non dispo avec eff = 1 (logiquement supprimée)
}Ent;

//determiner (afficher) les elements de l'entete
int Entete(char *bib , int n);

// affecter des valeurs aux éléments de l'entète
void aff_entete(char *bib , int n , int x);

//creation d'un TOF de taille tai
void Creation_TOF(char *bib, int tai);


//copie du fichier 1 vers le fichier 2
void fcpy(char *bib1 , char *bib2);

//lire les valeurs d'un TOF (les titres des livres et leurs etat de chaque etage)
void Lect_TOF(char *bib);

//reorganisation de la bib TOF
void Reorganisation_TOF(char *bib);

//recherche de l'element d et retourne le numero du bloc i et la position j
void Recherch_Dicho_TOF(char *bib , char *D , bool *trouv , int *i , int *j);

//supression logique de la valeur D
void Suppression_logique_TOF(char *bib , char ISBN[1024]);

int compareISBN(const void *y, const void *z) ;
