#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "pentomino.h"

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 640
#define LIGNE_FOND 15

	    

int main(int argc, char *argv[])
{
  SDL_Surface *screen, *temp, *carresp;
  s_grille * grille=malloc(sizeof(s_grille));
  s_piece * pieces=malloc(10*sizeof(s_piece));
  SDL_Init(SDL_INIT_VIDEO);
  

  SDL_WM_SetCaption("Pentomino", "LUL");

  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  temp = SDL_LoadBMP("carre.bmp");
  carresp = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  
  int gameover = 0;
  char key[SDLK_LAST] = {0};
  lire_fichier("pentomino.txt",grille,pieces);
  afficher_piece(pieces, screen, carresp);
  afficher_grille(grille, screen, carresp);
  printf("\n");


  while (!gameover)
    {
      SDL_BlitSurface(NULL, NULL, screen, NULL);
      update_events(key, &gameover, pieces);
      SDL_ShowCursor(1);
      afficher_grille(grille, screen, carresp);
      afficher_piece(pieces, screen, carresp);
      SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
  SDL_FreeSurface(carresp);
  SDL_Quit();
  return 0;
  
}
