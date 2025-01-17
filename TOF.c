#include "TOF.h"

int Entete(char *bib, int n) {
    Ent e;
    FILE *f = fopen(bib, "rb");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return -1;
    }

    fread(&e, sizeof(e), 1, f);
    fclose(f);

    if (n == 1) {
        return e.nbr_etagere; // afficher le nombre d'etageres
    } else if (n == 2) {
        return e.nbr_livre; // afficher le nombre de livres
    } else if (n == 3) {
        return e.nbr_emprunte; // afficher le nombre de livres empruntes
    } else {
        fprintf(stderr, "!!ERREUR!!\n");
        return 0;
    }
}



void fcpy(char *bib1, char *bib2) {
    Ent t;
    etagere buff;

    FILE *copy = fopen(bib1, "rb");
    FILE *paste = fopen(bib2, "wb");

    // Vérifier l'ouverture des fichiers
    if (copy == NULL || paste == NULL) {
        perror("Erreur lors de l'ouverture des fichiers");
        return;
    }

    fread(&t, sizeof(t), 1, copy);
    fwrite(&t, sizeof(t), 1, paste);  // déplacer l'entete d'abord

    int i;
    // on déplace tous le contenu de la bib, le contenu d'un etage en utilisant le buffer
    // le buffer est un etagere vide non inclu dans la bib qui sert a stoker nos livre temporairement 
    for (i = 1; i <= Entete(bib1, 1); i++) {
        fread(&buff, sizeof(buff), 1, copy);
        fwrite(&buff, sizeof(buff), 1, paste);
    }

    fclose(copy);
    fclose(paste); // fermer les portes des deux bib
}


void aff_entete(char *bib, int n, int x) {
    Ent e;

    FILE *f = fopen(bib, "rb+");
    
    // Vérifier l'ouverture du fichier
    if (f == NULL) {
       printf("Erreur lors de l'ouverture du fichier");
       return;
    }

    fread(&e, sizeof(e), 1, f); // lire l'entête
    fseek(f, 0, SEEK_SET); // retourner le pointeur au début

    if (n == 1) {
        e.nbr_etagere = x; // modifier le nombre d'etageres
        fwrite(&e , sizeof(e) , 1 , f);
        fclose(f) ;
        return ;
    } else if (n == 2) {
        e.nbr_livre = x; // modifier le nombre de livres
        fwrite(&e , sizeof(e) , 1 , f);
        fclose(f) ;
        return ;
    } else if (n == 3) {
        e.nbr_emprunte = x; // modifier le nombre de livres empruntes
        fwrite(&e , sizeof(e) , 1 , f);
        fclose(f) ;
        return ;
    } else {
        printf("!!ERREUR!!\n"); // y'a une erreur
        fclose(f);
        return;
    }

  
     printf("il y a une erreur dans l'aff_entete.\n"); //ceci est un sinon be tkhebya
    fclose(f);
}

void Creation_TOF(char *bib, int nb_livres) {
    char titre[50];
    etagere Buff;
    int j = 0, i = 0, result;
    char ISBN[1024], pre[1024] = "";
    FILE *f = fopen(bib, "wb");

    if (f == NULL)
        return;

    fseek(f, sizeof(Ent), SEEK_SET);

    int k;
    for (k = 1; k <= nb_livres; k++) {
        printf("%d : ", k);
        printf("Entrez l'ISBN : ");
        scanf("%s",ISBN );
        printf("Entrez le titre du livre: ");
        scanf("%s", titre);

        if (j < b) {
            strcpy( Buff.Tab[j].titre , titre);
            Buff.Tab[j].emprunte = false;
            Buff.last_posi = j;
            strcpy(Buff.Tab[j].ISBN, ISBN);
            j++;
        } else {
            if (j < b) {
                strcpy (Buff.Tab[j].titre , titre);
                Buff.Tab[j].emprunte = false;
                Buff.last_posi = j;
                strcpy(Buff.Tab[j].ISBN, ISBN);
                j++;
            } else {
                Buff.nbr = b;
                fwrite(&Buff, sizeof(Buff), 1, f);
                j = 1;
                i++;
               strcpy( Buff.Tab[0].titre , titre);
                Buff.Tab[0].emprunte = false;
                strcpy(Buff.Tab[0].ISBN, ISBN);
            }
            strcpy(pre, ISBN);
        }
    }

    Buff.nbr = j;
    Buff.last_posi = j - 1;

    for (k = j; k <= b - 1; k++)
        Buff.Tab[k].emprunte = 1;

    fwrite(&Buff, sizeof(Buff), 1, f);

    i++;

    fclose(f);

    aff_entete(bib, 1, i);
    aff_entete(bib, 2, nb_livres);
    aff_entete(bib, 3, b - j);

    return;
}



//lire une bib
void Lect_TOF(char *bib){ 

etagere buff ;//buffer
FILE *f = fopen(bib , "rb") ;
 if(f == NULL) return ;
fseek(f , sizeof(Ent) , SEEK_SET) ; //sauter l'entete (fonction seek) cad mettre le pointeur juste apres l'entete

 int i;
 for( i = 1 ; i <= Entete(bib , 1) ; i++){ //parcourire les blocs aka les etageres
  fread(&buff , sizeof(buff) , 1 , f);
  printf("\netagere %d : ",i);

   int j;
   for( j = 0 ; j <= b - 1 ; j++){ //parcourire les livres de chaque etagere
   
    if( !buff.Tab[j].emprunte) printf("[%s] ",buff.Tab[j].titre); 
    // si le livre est disponible on affiche son titre
    else printf(".."); // si l'element empurnte ou bien n'existe pas 
   }

 }

 fclose(f) ;
 return ;
}



// Fonction de comparaison pour qsort
int compareISBN(const void *y, const void *z) {
    return strcmp(((livre *)y)->ISBN, ((livre *)z)->ISBN);
}
//reorganiser un fichier TOF
void Reorganisation_TOF(char *bib) {
    FILE *f1 = fopen(bib, "rb");
    FILE *f2 = fopen("brouillant.bin", "wb");

    fseek(f1, sizeof(Ent), SEEK_SET);
    fseek(f2, sizeof(Ent), SEEK_SET);

    etagere Buff1, Buff2;
    int i2 = 0, j2 = 0;

    int i;
    for (i = 1; i <= Entete(bib, 1); i++) {
        fread(&Buff1, sizeof(Buff1), 1, f1);

        qsort(Buff1.Tab, Buff1.last_posi + 1, sizeof(livre), compareISBN);

        int j;
        for (j = 0; j <= Buff1.last_posi; j++) {
            if (!Buff1.Tab[j].emprunte) {
                if (j2 < b) {
                    strcpy(Buff2.Tab[j2].titre, Buff1.Tab[j].titre);
                    Buff2.Tab[j2].emprunte = false;
                    strcpy(Buff2.Tab[j2].ISBN, Buff1.Tab[j].ISBN);
                    Buff2.last_posi = j2;
                    j2++;
                } else {
                    Buff2.nbr = b;
                    fwrite(&Buff2, sizeof(Buff2), 1, f2);
                    j2 = 1;
                    i2++;
                    strcpy(Buff2.Tab[0].titre, Buff1.Tab[j].titre);
                    Buff2.Tab[0].emprunte = false;
                    strcpy(Buff2.Tab[0].ISBN, Buff2.Tab[j].ISBN);
                }
            }
        }
    }

    Buff2.nbr = j2;
    Buff2.last_posi = j2 - 1;
    int k;
    for (k = j2; k <= b - 1; k++) Buff2.Tab[k].emprunte = 1;
    fwrite(&Buff2, sizeof(Buff2), 1, f2);
    i2++;
    aff_entete("brouillant.bin", 1, i2);
    aff_entete("brouillant.bin", 2, Entete(bib, 2));
    aff_entete("brouillant.bin", 3, b - j2);

    fclose(f1);
    fclose(f2);

    fcpy("brouillant.bin", bib);
}

void Recherch_Dicho_TOF(char *bib ,char D[1024] , bool *trouv , int *i , int *j){ //recherher un livre D et le trouver dans l'etagere i et position j

etagere Buff ; //Buffer
int Binf = 1 , Bsup = Entete(bib , 1) , inf , sup; 
int result1, result2, result3;                                      
bool  Stop = false ;
*j = 0 ;
*trouv=false;

FILE *f = fopen(bib , "rb") ;
 if(f == NULL){
  printf("livre non trouve...") ;  //si lr livre n'existe pas 
  return ;
 }

 while( Binf <= Bsup && !(*trouv) && !Stop){
  *i = (int) (Binf + Bsup) / 2 ;
  fseek(f ,sizeof(Ent) + (*i-1)*sizeof(Buff) , SEEK_SET) ; //aller vers l'etagere i , la mediane entre Bsup et Binf
  fread(&Buff , sizeof(Buff) , 1 , f) ;
   result1 = strcmp(D,Buff.Tab[0].ISBN);
   result2 = strcmp(D,Buff.Tab[Buff.last_posi].ISBN);
   if(result1 >= 0 && result2 <= 0){ //si D est dans le bloc i
    inf = 0 ;
    sup = Buff.last_posi ;

     while(inf <= sup && !(*trouv)){
      *j = (inf+sup) / 2 ; //prendre la position milieu j entre sup et inf
       result3 = strcmp(D,Buff.Tab[*j].ISBN);
      
       if(result3 == 0 && Buff.Tab[*j].emprunte== false) *trouv = true ; //si D est trouvé à position j
       else{ //sinon faire bouger sup ou inf
        if( result3 > 0 ) inf = *j+1 ;
        else sup = *j - 1 ;
       }
     }
      Stop = true ;
      if(!(*trouv)) *j = inf ; // si D pas trouvé , on ramène j à la position crédible à l'insertion de D
   }
   else if(result2 > 0) Binf = *i + 1 ; //sinon bouger vers prochaine interval [Binf ; Bsup] d'etageres
   else Bsup = *i - 1 ;
 }

 if(!(*trouv)){ // si on trouve pas D , il y a des cas spécial de j et i pour l'insertion
   if(*j == 0 && result2 > 0){
    if(Buff.last_posi < b - 1) *j = Buff.last_posi + 1 ; //si l'etagere n'est pas plein et D > Max de TOF , j et à droite de last_posi à l'insertion
    else *i = Binf ; //si l'etagere est plein et D > Max de TOF , i va ètre le nbr_etagere + 1 pour ajouter un etagere dans l'insertion
   }
 }

 fclose(f) ;
}




void Suppression_logique_TOF(char *bib , char ISBN[1024]){
    /* Cette fonction réalise la suppression logique d'un livre dans la bibliothèque.
     Elle utilise la fonction Recherch_Dicho_TOF pour localiser le livre,
     puis elle marque le livre comme "emprunté" (supprimé logiquement) dans le bloc. */
    /* la suppression logique du livre veut dire que le cadre du livre est disponible 
     mais à l'intérieur on ne trouve pas le livre mais plutôt la feuille rouge
     qui veut dire qu'il est emprunté */
    etagere Buff; //buffer
    int i , j , k ;
    bool trouv ;

    Recherch_Dicho_TOF(bib, ISBN, &trouv, &i, &j);
    // localiser le livre
    if(trouv == false) return ; //on sort du programme si le livre n'existe pas
    
    FILE *f = fopen(bib, "rb+");

    fseek(f, sizeof(Ent) + (i-1) * sizeof(Buff), SEEK_SET); //aller vers le bloc i où se trouve le livre
    fread(&Buff, sizeof(Buff), 1, f);

    fseek(f, -(long)sizeof(Buff), SEEK_CUR);
    // retourner le pointeur où il était à cause de fread, pour pouvoir l'utiliser

    Buff.Tab[j].emprunte = true; //emprunte = 1 
    if(j == Buff.last_posi){//si le livre est le dernier de l'étage, ajuster last position
        k = j ;
        while(Buff.Tab[k].emprunte == 1 && k >= 0){
            Buff.last_posi--;
            k--;
        }
        if(Buff.last_posi == -1) Buff.last_posi = 0 ;//Bloc vide donc last_posi n'aura pas de valeur , -1 va donner des erreurs si on le laisse
    }
    Buff.nbr-- ;// nbr total des livres dans l'étage

    fwrite(&Buff , sizeof(Buff) , 1 , f);
    // écrire le bloc modifié dans le fichier
    aff_entete(bib, 3, Entete(bib, 3) + 1);
    aff_entete(bib, 2, Entete(bib, 2) - 1);
    // Maj de l'entête

    fclose(f);
}


void Insertion_TOF(char *bibliotheque, char ISBN[1024], char titre[]) {
    etagere Buff;
    int i, j;
    bool trouv, state = 1;
    char sauvc[1024], sauvc2[1024];
    strcpy(sauvc, ISBN);

    Recherch_Dicho_TOF(bibliotheque, ISBN, &trouv, &i, &j);

    if (trouv == true)
        return;

    FILE *f = fopen(bibliotheque, "rb+");

    while (state && i <= Entete(bibliotheque, 1)) {
        fseek(f, sizeof(Ent) + (i - 1) * sizeof(Buff), SEEK_SET);
        fread(&Buff, sizeof(Buff), 1, f);
        fseek(f, -(long)sizeof(Buff), SEEK_CUR);

        if (Buff.Tab[j].emprunte) {
            Buff.Tab[j].emprunte = 0;
            strcpy(Buff.Tab[j].titre, titre);
            strcpy(Buff.Tab[j].ISBN, sauvc);
            Buff.nbr++;

            if (j > Buff.last_posi)
                Buff.last_posi = j;

            aff_entete(bibliotheque, 3, Entete(bibliotheque, 3) - 1);
            fwrite(&Buff, sizeof(Buff), 1, f);
            state = !state;
        } else if (Buff.last_posi < b - 1) {
            int k;
            for (k = b - 1; k >= j + 1; k--) {
                strcpy(Buff.Tab[k].titre, Buff.Tab[k - 1].titre);
                Buff.Tab[k].emprunte = Buff.Tab[k - 1].emprunte;
                strcpy(Buff.Tab[k].ISBN, Buff.Tab[k - 1].ISBN);
            }

            strcpy(Buff.Tab[j].titre, titre);
            Buff.Tab[j].emprunte = 0;
            strcpy(Buff.Tab[j].ISBN, sauvc);
            fwrite(&Buff, sizeof(Buff), 1, f);
            state = !state;
        } else {
            int k;
            for (k = b - 1; k >= j + 1; k--) {
                strcpy(Buff.Tab[k].titre, Buff.Tab[k - 1].titre);
                Buff.Tab[k].emprunte = Buff.Tab[k - 1].emprunte;
                strcpy(Buff.Tab[k].ISBN, Buff.Tab[k - 1].ISBN);
            }

            strcpy(sauvc2, Buff.Tab[Buff.last_posi].titre);

            strcpy(Buff.Tab[j].titre, titre);
            Buff.Tab[j].emprunte = 0;
            strcpy(Buff.Tab[j].ISBN, sauvc);
            fwrite(&Buff, sizeof(Buff), 1, f);
            i++;
            j = 0;
            strcpy(titre, sauvc2);
        }
    }

    if (state) {
        aff_entete(bibliotheque, 1, Entete(bibliotheque, 1) + 1);
        aff_entete(bibliotheque, 3, Entete(bibliotheque, 3) + b - 1);
        fseek(f, 0, SEEK_END);

        strcpy(Buff.Tab[0].titre, titre);
        Buff.Tab[0].emprunte = 0;
        strcpy(Buff.Tab[0].ISBN, sauvc);

        int k;
        for (k = 1; k <= b - 1; k++)
            Buff.Tab[k].emprunte = 1;

        Buff.last_posi = 0;
        Buff.nbr = 1;
        fwrite(&Buff, sizeof(Buff), 1, f);
    }

    aff_entete(bibliotheque, 2, Entete(bibliotheque, 2) + 1);
    fclose(f);
}


