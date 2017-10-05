#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

typedef struct carre{
  SDL_Rect pos;
  SDL_Rect sprite;
  int deplacable;
}t_carre;

typedef struct piece{
  t_carre ** p;
}t_piece;

extern void rdroite(t_piece * p);
extern void rgauche(t_piece * p);
extern void deplacer(t_piece * p);
extern void update_events(char*, int*);
