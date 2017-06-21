#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define TAILLE 12

typedef enum {FALSE, TRUE} boolean;

void creerMatrice(FILE*, char[][TAILLE], int[][TAILLE]);
boolean gaucheDroite(char*, char[][TAILLE], int[][TAILLE], int, int);
boolean droiteGauche(char*, char[][TAILLE], int[][TAILLE], int, int);
boolean hautBas(char*, char[][TAILLE], int[][TAILLE], int, int);
boolean basHaut(char*, char[][TAILLE], int[][TAILLE], int, int);
void afficheSolution(char[][TAILLE], int[][TAILLE]);

int main (int argc, char** argv)
{
   FILE* fichier;
   char tableau[TAILLE][TAILLE];
   int solution[TAILLE][TAILLE];
   char mot[TAILLE + 1];
   boolean trouve;
   int i, j;
   
   if (argc != 2)
   {
      printf("Utilisation: ./tp1 <nom du fichier>\n");
      exit(1);
   }
   
   fichier = fopen(argv[1], "r");
   
   if (fichier == NULL)
   {
      printf("Erreur #%d lors de l'ouverture du fichier\n", errno);
      return 1;
   }
   
   creerMatrice(fichier, tableau, solution);
      
   while (fgets(mot, TAILLE + 1, fichier) != NULL)
   {
      trouve = FALSE;
      i = 0;
      j = 0;
      
      mot[strlen(mot) - 1] = '\0';
      
      while (trouve == FALSE && i < TAILLE)
      {
         while (trouve == FALSE && j < TAILLE)
         {
            if (*mot == tableau[i][j])
            {
               trouve  = gaucheDroite(mot, tableau, solution, i, j);

               if (trouve == FALSE)
               {
                  trouve  = droiteGauche(mot, tableau, solution, i, j);
               }

               if (trouve == FALSE)
               {
                  trouve  = hautBas(mot, tableau, solution, i, j);
               }

               if (trouve == FALSE)
               {
                  trouve = basHaut(mot, tableau, solution, i, j);
               }
            }
            j++;
         }
         i++;
         j = 0;
      }
   }
   
   afficheSolution(tableau, solution);
   
   if (fclose(fichier) == EOF)
   {
      printf("Erreur lors de la fermeture du fichier.\n");
      return 1;
   }
  
   return 0;
}

/*
 * @param mot: le mot à trouver dans la grille
 * @param tableau: la grille de lettres qui contient le mot
 * @param solution: la grille servant à solutionner le mot caché
 * @param x: la rangée où le début du mot à été trouvé
 * @param y: la colonne où le début du mot à été trouvé
 * @return: retourne TRUE si le mot à été trouvé ou FALSE si il faut continuer à chercher
 * 
 * Une fois que la première lettre du mot recherché à été trouvée, cette fonction vérifie
 * si les lettres suivantes sont bien celles du mot recherché en allant vers la droite dans
 * la grille. La recherche s'arrête si une lettre ne correspont pas ou si la limite de la grille
 * à été atteinte. Si le mot a été trouvé, remplace les zéros par des uns dans la grille solution
 * aux mêmes coordonnées que le mot dans la grille de lettres.
 */
boolean gaucheDroite(char* mot, char tableau[][TAILLE], int solution[][TAILLE], int x, int y)
{
   int longueurMot;
   int i;
   
   longueurMot = (int)strlen(mot);
   
   while (*mot != '\0')
   {
      if (y == TAILLE || *mot++ != tableau[x][y++])
      {
         return FALSE;
      }
   }
   
   for (i = 0; i < longueurMot; i++)
   {
      solution[x][--y] = 1;
   }
   
   return TRUE;
}

/*
 * @param mot: le mot à trouver dans la grille
 * @param tableau: la grille de lettres qui contient le mot
 * @param solution: la grille de 0 et de 1 servant à solutionner le mot caché
 * @param x: la rangée où le début du mot à été trouvé
 * @param y: la colonne où le début du mot à été trouvé
 * @return: retourne TRUE si le mot à été trouvé ou FALSE si il faut continuer à chercher
 * 
 * Une fois que la première lettre du mot recherché à été trouvée, cette fonction vérifie
 * si les lettres suivantes sont bien celles du mot recherché en allant vers la gauche dans
 * la grille. La recherche s'arrête si une lettre ne correspont pas ou si la limite de la grille
 * à été atteinte. Si le mot a été trouvé, remplace les zéros par des uns dans la grille solution
 * aux mêmes coordonnées que le mot dans la grille de lettres.
 */
boolean droiteGauche(char* mot, char tableau[][TAILLE], int solution[][TAILLE], int x, int y)
{
   int longueurMot;
   int i;
   
   longueurMot = (int)strlen(mot);
   
   while (*mot != '\0')
   {
      if (y < 0 || *mot++ != tableau[x][y--])
      {
         return FALSE;
      }
   }
   
   for (i = 0; i < longueurMot; i++)
   {
      solution[x][++y] = 1;
   }
   
   return TRUE;
}

/*
 * @param mot: le mot à trouver dans la grille
 * @param tableau: la grille de lettres qui contient le mot
 * @param solution: la grille de 0 et de 1 servant à solutionner le mot caché
 * @param x: la rangée où le début du mot à été trouvé
 * @param y: la colonne où le début du mot à été trouvé
 * @return: retourne TRUE si le mot à été trouvé ou FALSE si il faut continuer à chercher
 * 
 * Une fois que la première lettre du mot recherché à été trouvée, cette fonction vérifie
 * si les lettres suivantes sont bien celles du mot recherché en allant vers le bas dans
 * la grille. La recherche s'arrête si une lettre ne correspont pas ou si la limite de la grille
 * à été atteinte. Si le mot a été trouvé, remplace les zéros par des uns dans la grille solution
 * aux mêmes coordonnées que le mot dans la grille de lettres.
 */
boolean hautBas(char* mot, char tableau[][TAILLE], int solution[][TAILLE], int x, int y)
{
   int longueurMot;
   int i;
   
   longueurMot = (int)strlen(mot);
   
   while (*mot != '\0')
   {
      if (x == TAILLE || *mot++ != tableau[x++][y])
      {
         return FALSE;
      }
   }
   
   for (i = 0; i < longueurMot; i++)
   {
      solution[--x][y] = 1;
   }
   
   return TRUE;
}

/*
 * @param mot: le mot à trouver dans la grille
 * @param tableau: la grille de lettres qui contient le mot
 * @param solution: la grille de 0 et de 1 servant à solutionner le mot caché
 * @param x: la rangée où le début du mot à été trouvé
 * @param y: la colonne où le début du mot à été trouvé
 * @return: retourne TRUE si le mot à été trouvé ou FALSE si il faut continuer à chercher
 * 
 * Une fois que la première lettre du mot recherché à été trouvée, cette fonction vérifie
 * si les lettres suivantes sont bien celles du mot recherché en allant vers le haut dans
 * la grille. La recherche s'arrête si une lettre ne correspont pas ou si la limite de la grille
 * à été atteinte. Si le mot a été trouvé, remplace les zéros par des uns dans la grille solution
 * aux mêmes coordonnées que le mot dans la grille de lettres.
 */
boolean basHaut(char* mot, char tableau[][TAILLE], int solution[][TAILLE], int x, int y)
{
   int longueurMot;
   int i;
   
   longueurMot = (int)strlen(mot);
   
   while (*mot != '\0')
   {
      if (x < 0 || *mot++ != tableau[x--][y])
      {
         return FALSE;
      }
   }
   
   for (i = 0; i < longueurMot; i++)
   {
      solution[++x][y] = 1;
   }
   
   return TRUE;
}

/*
 * @param tableau: la grille de lettres qui contient le mot
 * @param solution: la grille de 0 et de 1 servant à solutionner le mot caché
 * 
 * Une fois tous les mots trouvés, cette fonction parcourt la grille solution
 * et recherche les zéros qui représentent les lettres non utilisées. Chaque fois
 * qu'elle rencontre un zéro, elle affiche à la console le caractère correspondant 
 * aux mêmes coordonnés dans la grille de lettres.
 */
void afficheSolution(char tableau[][TAILLE], int solution[][TAILLE])
{
   int i, j;
   
   for (i = 0; i < TAILLE;  i++)
   {
      for (j = 0; j < TAILLE; j++)
      {
         if (solution[i][j] == 0)
         {
            printf("%c", tableau[i][j]);
         }
      }
   }
   
   printf("\n");
}

/*
 * @param fichier: le fichier texte qui contient le mot caché à solutionner
 * @param tableau: la grille de lettres copiées du fichier texte
 * @param solution: la grille de 0 et de 1 servant à solutionner le mot caché
 * 
 * Cette fonction lit le contenu du fichier texte et créer une matrice en copiant
 * les lettres qui s'y trouve en excluant les '\n'. En même temps, elle crée une 
 * matrice du même format et l'initialise avec des zéros, cette matrice sert à
 * déterminer si une lettre à été utilisée ou pas et permet de solutionner le mot caché. 
 */
void creerMatrice(FILE* fichier, char tableau[][TAILLE], int solution[][TAILLE])
{
   int i, j;
   
   for (i = 0; i < TAILLE; i++)
   {
      for (j = 0; j< TAILLE; j++)
      {
         tableau[i][j] = fgetc(fichier);
         solution[i][j] = 0;
      }
      
      fgetc(fichier);
   }
   
   fgetc(fichier);
}