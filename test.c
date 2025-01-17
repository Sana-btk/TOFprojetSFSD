#include "TOF.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main() {
    char *bib;
    int nbr_etagere, nbr_emprunte, nbr_livre;
    

    bib = (char *)malloc(30 * sizeof(char));
    if (bib == NULL) {
        printf("Erreur d'allocation de mémoire pour le nom de la bib\n");
        return 1; // Quittez le programme avec un code d'erreur
    }

    // Saisir le nom du fichier
    printf("Entrez le nom de la bib : ");
    scanf("%s", bib);

    // Saisir le nombre de livres
    printf("Entrez le nombre de livres : ");
    scanf("%d", &nbr_livre);
    
    //creation de la bib
    Creation_TOF(bib,nbr_livre);
    Reorganisation_TOF(bib);
    Lect_TOF(bib);
    printf("\n");
   
    int choix;
    do {
        // Afficher le menu
        printf("\nMenu:\n");
        printf("1. Insertion\n");
        printf("2. Suppression\n");
        printf("3. Lecture\n");
        printf("4. Recherche\n");
        printf("5. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                char ISBN[1024],titre[1024];
                
                // Saisir les infos des livres pour l'insertion
                printf("Entrez la ISBN : ");
                scanf("%s", &ISBN);
                printf("Entrez le titre du livre : ");
                scanf("%s", &titre);
                // Appeler la fonction d'insertion
                Insertion_TOF(bib, ISBN, titre);
                //reorganisation apres l'insertion
                Reorganisation_TOF(bib);
                Lect_TOF(bib);
                
                break;
            }
            case 2: {
                char ISBN[1024];
                // Saisir l'ISBN du livre à supprimer
                printf("Entrez la ISBN du livre a supprimer : ");
                scanf("%s", &ISBN);
                // Appeler la fonction de suppression logique
                Suppression_logique_TOF(bib, ISBN);
                //reorganisation apres la supp
                Reorganisation_TOF(bib);
                Lect_TOF(bib);
                
                break;
            }
            case 3:
                // Appeler la fonction de lecture
                Lect_TOF(bib);
                
                break;
            
            case 4: {
                char D[1024];
                bool trouv;
                int i, j;
                // Saisir l'élément à rechercher
                printf("Entrez l'ISBN du livre a rechercher : ");
                scanf("%s",D);
                // Appeler la fonction de recherche
                Recherch_Dicho_TOF(bib ,D , &trouv , &i , &j);
                if (trouv) {
                    printf("Livre trouve dans l'etagere %d, position %d.\n", i, j);
                } else {
                    printf("Livre non trouve.\n");
                }
                break;
                
            }
             
            case 5:
                // Quitter le programme
                printf("Au revoir!\n");
                
                break;
            default:
                // Gérer les choix invalides
                printf("Choix invalide. Veuillez entrer un nombre entre 1 et 5.\n");
                
        }

    } while (choix != 5);

    return 0;
}

