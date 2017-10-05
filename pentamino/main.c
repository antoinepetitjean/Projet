#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "pentomino.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 640

int main(int argc, char *argv[])

{
  SDL_Surface *screen, *temp, *pentaminosp;
  t_carre pentomino;
  SDL_Init(SDL_INIT_VIDEO);

  SDL_WM_SetCaption("Pentamino", "LUL");

  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  temp = SDL_LoadBMP("Untitled-1.bmp");
  pentaminosp = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  pentomino.pos.x = (SCREEN_WIDTH - 450) /2;
  pentomino.pos.y = (SCREEN_HEIGHT - 450) /2;
  pentomino.sprite.y = 0;
  pentomino.sprite.w = 450;
  pentomino.sprite.h = 450;
  pentomino.sprite.x = 0;

  int gameover = 0;
  char key[SDLK_LAST] = {0};

  while (!gameover)
    {
      update_events(key, &gameover);
      SDL_BlitSurface(pentaminosp, &pentomino.sprite, screen, &pentomino.pos);
      SDL_UpdateRect(screen, 0, 0, 0, 0);
      SDL_ShowCursor(1);
    }

  SDL_FreeSurface(pentaminosp);
  SDL_Quit();


  return 0;
    
}
