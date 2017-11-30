#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <time.h>
#include "pentomino.h"



	    

int main(int argc, char *argv[])
{
  SDL_Surface *screen, *temp, *carresp, *grillesp, *menu;
  s_grille * grille=malloc(sizeof(s_grille));
  s_piece * pieces=malloc((MAX_PIECE+1)*sizeof(s_piece));
  clock_t deb, fin, tot;
  SDL_Event event;
  int decompte;
  SDL_Init(SDL_INIT_VIDEO);

  SDL_WM_SetCaption("Pentomino", "LUL");

  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  temp = SDL_LoadBMP("carre.bmp");
  carresp = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("grille.bmp");
  grillesp = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("menubeta.bmp");
  menu = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  
  int gameover = 0;
  char key[SDLK_LAST] = {0};
  lire_fichier("pentomino.txt",grille,pieces);
  //afficher_piece(pieces, screen, carresp);
  //afficher_grille(grille, screen, carresp);
  printf("\n");
  
  SDL_BlitSurface(menu, NULL, screen, NULL);
  while(1)
  {
    SDL_PollEvent(&event);
    if (event.key.keysym.sym==SDLK_SPACE) break;
    else if (event.key.keysym.sym==SDLK_q)
    {
      gameover=1;
      break;
    }
  }
  deb=clock();
  
  while (!gameover)
    {
      //SDL_BlitSurface(NULL, NULL, screen, NULL);
      update_events(key, &gameover, grille, pieces);
      fin=clock();
      tot=(int)(fin-deb)/CLOCKS_PER_SEC;
      decompte=DUREE_MAX-tot;
      if(decompte<=0)gameover=1;
      SDL_ShowCursor(1);
      SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
      afficher_grille(grille, screen, grillesp);
      afficher_piece(pieces, screen, carresp);
      
      SDL_Flip(screen);
    }
  SDL_FreeSurface(carresp);
  SDL_FreeSurface(grillesp);
  SDL_FreeSurface(menu);
  SDL_Quit();
  return 0;
  
}
