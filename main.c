#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "pentomino.h"


int main(int argc, char *argv[])
{
  SDL_Surface *screen, *temp, *carresp, *grillesp, *menu, *chiffre;
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
  temp = SDL_LoadBMP("chiffrestest.bmp");
  chiffre = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  
  int gameover = 0;
  char key[SDLK_LAST] = {0};
  int lvl=0;
  /*grille->pos=malloc(0*sizeof(point2d));
  for(i=0; i<MAX_PIECE;i++)
  {
    pieces[i].pos=malloc(0*sizeof(point2d));
  }*/
  lire_fichier("lvl0.txt",grille,pieces);
  while(1)
  {
    SDL_BlitSurface(menu, NULL, screen, NULL);
    SDL_PollEvent(&event);
    if (event.key.keysym.sym==SDLK_SPACE) break;
    else if (event.key.keysym.sym==SDLK_q || event.type==SDL_QUIT)
    {
      gameover=1;
      break;
    }
    SDL_Flip(screen);
  }
  deb=clock();
  
  while (!gameover)
    {
      //SDL_BlitSurface(NULL, NULL, screen, NULL);
      update_events(key, &gameover, grille, pieces, &lvl, &deb);
      fin=clock();
      tot=(int)(fin-deb)/CLOCKS_PER_SEC;
      decompte=DUREE_MAX-tot;
      if(decompte<=0)gameover=1;
      SDL_ShowCursor(1);
      SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 150, 150, 150));
      afficher_grille(grille, screen, grillesp);
      afficher_piece(pieces, screen, carresp);
      afficher_temps(decompte, screen, chiffre);
      SDL_Flip(screen);
    }
  //free(grille);
  //free(pieces);
  SDL_FreeSurface(carresp);
  SDL_FreeSurface(grillesp);
  SDL_FreeSurface(menu);
  SDL_FreeSurface(chiffre);
  SDL_FreeSurface(screen);
  SDL_Quit();
  return 0;
  
}
