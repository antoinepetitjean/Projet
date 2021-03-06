#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 640
#define MAX_PIECE 10
#define DUREE_MAX 60
#define NB_LVL 4

typedef struct point2d{
  int x;
  int y;
}point2d;

typedef struct piece{
  int nbpiece; //numéro de la piece
  int taille; //taille de la piece
  int select;
  int largeur;
  int hauteur;
  int orientation;
  int dlg; //vérifier si la piece est dans la grille
  int bdlg; //vérifier si la piece est à la bonne place dans la grille
  point2d * pos; //coordonnées de la piece, tableau 2 dim
}s_piece;

typedef struct grille{
  int taille;
  point2d * pos; //position de la grille pour sdl
}s_grille;

typedef struct sprite{ //structure qui va servir à afficher les petits carrés
  SDL_Surface *carre;
  SDL_Rect sprite;
  SDL_Rect pos;
}s_sprite; 

typedef struct hitbox{
  int minx;
  int maxx;
  int miny;
  int maxy;
}s_hitbox;

extern void rdroite(s_piece * p);
extern void rgauche(s_piece * p);
extern void deplacer(SDL_Event *event, s_piece * p);
extern void update_events(char*, int*, s_grille * g, s_piece * p, int *lvl, int *deb);
extern void lire_fichier(char*, s_grille *g, s_piece *pieces);
extern void lire_fichier_piece(FILE *fichier, s_piece *pieces);
extern void vider_grille(s_grille *g);
extern void vider_pieces(s_piece *p);
extern void centrer_grille(s_grille *g);
extern void afficher_grille(s_grille *g, SDL_Surface * screen, SDL_Surface * carresp);
extern void afficher_piece(s_piece *p, SDL_Surface * screen, SDL_Surface * carresp);
extern void afficher_temps(int decompte, SDL_Surface * screen, SDL_Surface * chiffre);
extern void select_piece(SDL_Event *event, s_piece *p);
extern void arrondir(s_piece *p);
extern void new_level (s_grille *g, s_piece *p, int *lvl);
extern int colision(s_piece *p);
extern s_hitbox hitbox_piece(point2d p);
extern int victoire(s_grille *g, s_piece *p);
extern int count_piece(s_piece *p);

