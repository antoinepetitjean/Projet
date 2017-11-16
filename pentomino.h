#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>

typedef struct point2d{
  int x;
  int y;
}point2d;

typedef struct piece{
  int nbpiece; //numéro de la piece
  int taille; //taille de la piece
  int largeur;
  int hauteur;
  int orientation;
  int dlg; //vérifier si la piece est dans la grille
  int bdlg; //vérifier si la piece est à la bonne place dans la grille
  point2d * pos; //coordonnées de la piece, tableau 2 dim
}s_piece;

typedef struct grille{
  char nom;
  int taille;
  point2d * pos; //position de la grille pour sdl
  int remplie; //si la liste est remplie, remplie = 1
}s_grille;

typedef struct sprite{ //structure qui va servir à afficher les petits carrés
  SDL_Surface *carre;
  SDL_Rect sprite;
  SDL_Rect pos;
}s_sprite; 

extern void rdroite(s_piece * p);
extern void rgauche(s_piece * p);
extern void deplacer(s_piece * p);
extern void update_events(char*, int*);
extern void lire_fichier(char*, s_grille *g, s_piece *pieces);
extern void lire_fichier_piece(FILE *fichier, s_piece *pieces);
extern void afficher_grille(s_grille *g, SDL_Surface * screen, SDL_Surface * carresp);
extern void afficher_piece(s_piece *p, SDL_Surface * screen, SDL_Surface * carresp);
