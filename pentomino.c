#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "pentomino.h"

void update_events(char* keys, int *quit)
{
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch (event.type) {
      /* close button clicked */
    case SDL_QUIT:
      *quit = 1;
      break;
    case SDL_KEYUP:
      keys[event.key.keysym.sym] = 0;
      break;
    /* handle the keyboard */
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
      case SDLK_q:
	*quit = 1;
	break;
      default:
	break;
      }
      keys[event.key.keysym.sym] = 1;
      break;
    }
  }
}

s_grille lire_fichier_grille(char *f)
{
  FILE* fichier = NULL;
  int i,j;
  char c;
  s_grille  g;
  g.ligne = 0;
  g.colonne = 0;
  g.nom = '1';
  fichier = fopen(f, "r");
  c=fgetc(fichier);
  if (fichier != NULL)
    {
      while (c != EOF) //tant qu'on est pas à la fin du fichier
	{
	  if(c == '#') //si c est un diese, on avanc d'un sur les colonns
	    {
	      g.colonne = g.colonne+1;
	    }

	  if(c == '\n') //si c est un retour à la ligne, on avance d'un sur les lignes
	    { 
	      g.ligne = g.ligne+1;
	      g.colonne = 0; //pour pas avoir trop de colonne
	    }
	  c=fgetc(fichier); //on avance sur le caractère d'après
	}
    }
  else
    printf("File didnt load\n");
  fclose(fichier);
  for (i=0;i<=g.ligne;i++) //je fait un test printf de la grille
    {
      for (j=0;j<g.colonne;j++)
	printf("#");
      printf("\n");
    }
  return g; //je retourne la grille, elle a un nom et un nombre de colonne et ligne mais pas de position
}

void lire_fichier_piece(char *f)
{
  FILE* fichier = NULL;
  int i,j,k,nb;
  char c;
  s_piece pieces[10];
  nb=0;
  i=0;
  j=0;
  k=0;
  fichier = fopen(f, "r");
  c=fgetc(fichier);
  pieces[0].hauteur=0;
  pieces[0].largeur=0;
  pieces[0].nbpiece=1;
  if (fichier != NULL)
    {
      while (c != EOF)
	{
	  if (c == '#') //si c'est un # on incrémente la largeur de la piece de 1 et on met la position de la piece à 1 et on passe à la position suivante
	    {
	      pieces[nb].largeur=pieces[nb].largeur+1;
	      pieces[nb].pos[i][j]=1;
	      printf("%d",pieces[nb].pos[i][j]);
	      j=j+1;
	    }
	  if (c == 'r') //si c'est un r on change de piece, on l'initialise et on reset les compteurs
	    {
	      nb=nb+1;
	      pieces[nb].largeur=0;
	      pieces[nb].hauteur=0;
	      i=0;
	      j=0;
	      pieces[nb].nbpiece=nb+1;
	    }
	  if (c == ' ') //si c'est un espace on incrémente la largeur de la piece de 1 et on met la position de la piece a 0 et on passe à la position suivante
	    {
	      pieces[nb].largeur=pieces[nb].largeur+1;
	      pieces[nb].pos[i][j]=0;
	      printf("%d",pieces[nb].pos[i][j]);
	      j=j+1;
	    }
	  if (c == '\n') //si c'est un retour à la ligne on reset la largeur, on incrémente la hauteur et on reset notre compteur de colonne
	    {
	      pieces[nb].hauteur=pieces[nb].hauteur+1;
	      i=i+1;
	      j=0;
	      pieces[nb].largeur=0;
	      printf("\n");
	    }
	  c=fgetc(fichier);
	}
    }
  else
    printf("File didn't load");
  fclose(fichier);
  for(i=0;i<=nb;i++) //ici je tente un printf mais ça marche pas
    {
    for(k=0;k<pieces[i].hauteur;k++)
      {
      for(j=0;j<pieces[i].largeur;j++)
	{
	  if(pieces[i].pos[k][j]==0)
	    printf(" ");
	  if(pieces[i].pos[k][j]==1)
	    printf("#");
	}
      printf("\n");
      }
    printf("\n");
    }
}

void rdroite(s_piece *p)
{

}

void rgauche(s_piece *p)
{

}

void deplacer(s_piece *p)
{

}
