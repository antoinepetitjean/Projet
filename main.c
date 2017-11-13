#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "pentomino.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 640
#define LIGNE_FOND 15

	    

int main(int argc, char *argv[])
{
  SDL_Surface *screen, *temp, *carresp;
  s_grille * grille;
  //s_piece * pieces = malloc(10 * sizeof(s_piece));
  //t_carre pentomino;
  SDL_Init(SDL_INIT_VIDEO);
  
  //t_piece * liste_des_pieces = malloc(sizeof(t_piece));

  SDL_WM_SetCaption("Pentomino", "LUL");

  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  temp = SDL_LoadBMP("carre.bmp");
  carresp = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  /*pentomino.pos.x = (SCREEN_WIDTH - 450) /2;
    pentomino.pos.y = (SCREEN_HEIGHT - 450) /2;
    pentomino.sprite.y = 0;
    pentomino.sprite.w = 450;
    pentomino.sprite.h = 450;
    pentomino.sprite.x = 0;*/
  
  int gameover = 0;
  char key[SDLK_LAST] = {0};
  grille=lire_fichier_grille("grille.txt");
  //afficher_grille(grille,);
  printf("\n");
 // lire_fichier_piece("pieces.txt");
  // affiche_fond();

  while (!gameover)
    {
      update_events(key, &gameover);
      afficher_grille(grille, screen, carresp);
      // SDL_BlitSurface(pentaminosp, &pentomino.sprite, screen, &pentomino.pos);
      SDL_UpdateRect(screen, 0, 0, 0, 0);
      SDL_ShowCursor(1);
    }
  //free(&liste_des_pieces);
  SDL_FreeSurface(carresp);
  SDL_Quit();
  //free(piece);
  return 0;
  
}
